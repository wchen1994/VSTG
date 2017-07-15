#include "ObjCreator.h"

const double PI = 3.141592653589793238463;

#define COLLI_FLAG_PLAYER COLLI_FLAG_1
#define COLLI_FLAG_ENEMY COLLI_FLAG_2
#define COLLI_FLAG_BULLET COLLI_FLAG_3

namespace ObjCreator {
	std::shared_ptr<Character> ObjCreator::Character::Create(
		const sf::Vector2f & pos, const sf::Vector2f & vel, float speed, std::shared_ptr<sf::Texture> pTex, Board * brd)
	{
		std::shared_ptr<Character> pCharacter = std::make_shared<Character>(pos, vel, speed, pTex, brd);
		layerDefault[pCharacter->unique_id] = pCharacter;
		return pCharacter;
	}

	Character::Character(const sf::Vector2f & pos,const sf::Vector2f & vel, float speed, std::shared_ptr<sf::Texture> pTex, Board * brd) :
		Moveable(pos),
		GameObject(nullptr, pos, 0.f, "unname"),
		Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), sf::Vector2f(0.1f, 0.1f), 0.f),
		BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
		Collider(ColliderType::Circle, ColliderProperities(5.f)),
		BehaviourController(CreatePlayerTree()),
		velocity(vel), speed(speed)
	{
	}

	void Character::setVelocity(const sf::Vector2f & vel)
	{
		velocity = vel;
	}

	std::shared_ptr<Player> Player::Create(const sf::Vector2f & pos, std::shared_ptr<sf::Texture> pTex, Board * brd)
	{
		std::shared_ptr<Player> pCharacter = std::make_shared<Player>(pos, pTex, brd);
		layerDefault[pCharacter->unique_id] = pCharacter;
		return pCharacter;
	}

	Player::Player(const sf::Vector2f & pos, std::shared_ptr<sf::Texture> pTex, Board * brd):
		Moveable(pos),
		GameObject(nullptr, pos, 0.f, "Player"),
		Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), sf::Vector2f(0.1f, 0.1f), 0.f),
		BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
		Collider(ColliderType::Circle, ColliderProperities(5.f), COLLI_FLAG_PLAYER, COLLI_FLAG_ENEMY),
		BehaviourController(CreatePlayerTree()),
		Character(pos, sf::Vector2f(), 20.f, pTex, brd),
		counter(0.f)
	{
	}

	void Player::PostUpdate()
	{
		if (position.x < 0)
			position.x = 0;
		if (position.x > 500)
			position.x = 500;
		if (position.y < 0)
			position.y = 0;
		if (position.y > 550)
			position.y = 550;
	}

	void Player::onFire(const float dt)
	{
		counter += dt;
		if (counter > coolDown) {
			PlayerBullet::Create(position, 0.f, 30.f, CommResMeth::AssetManager::GetTexture("Resources/Textures/BulletPlayer.png"), sf::Vector2f(.05f,.05f), brd);
			PlayerBullet::Create(position, 15.f, 30.f, CommResMeth::AssetManager::GetTexture("Resources/Textures/BulletPlayer.png"), sf::Vector2f(.05f,.05f), brd);
			PlayerBullet::Create(position, -15.f, 30.f, CommResMeth::AssetManager::GetTexture("Resources/Textures/BulletPlayer.png"), sf::Vector2f(.05f,.05f), brd);
			PlayerBullet::Create(position, 30.f, 30.f, CommResMeth::AssetManager::GetTexture("Resources/Textures/BulletPlayer.png"), sf::Vector2f(.05f,.05f), brd);
			PlayerBullet::Create(position, -30.f, 30.f, CommResMeth::AssetManager::GetTexture("Resources/Textures/BulletPlayer.png"), sf::Vector2f(.05f,.05f), brd);
			counter = 0.f;
		}
	}

	std::shared_ptr<PlayerBullet> PlayerBullet::Create(
		const sf::Vector2f & pos, const CommResMeth::Angle & angle, float speed, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale, Board * brd)
	{
		std::shared_ptr<PlayerBullet> pBullet = std::make_shared<PlayerBullet>(pos, angle, speed, pTex, scale, brd);
		layerDefault[pBullet->unique_id] = pBullet;
		return pBullet;
	}

	PlayerBullet::PlayerBullet(const sf::Vector2f & pos, const CommResMeth::Angle & angle, float speed, std::shared_ptr<sf::Texture> pTex, const sf::Vector2f & scale, Board * brd) :
		Moveable(pos, angle),
		GameObject(nullptr, pos, angle, "Bullet"),
		Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), scale, angle),
		BoardObj(brd, ColliderType::Circle, ColliderProperities((float)pTex->getSize().x)),
		Collider(ColliderType::Circle, ColliderProperities((float)pTex->getSize().x), COLLI_FLAG_BULLET, COLLI_FLAG_ENEMY),
		BehaviourController(nullptr),
		Character(pos, speed * sf::Vector2f(sin(angle.rad()), cos(angle.rad())), speed, pTex, brd)
	{
	}

	void PlayerBullet::PostUpdate()
	{
		if (position.x < 0 || position.x > 500 || position.y > 550 || position.y < 0) {
			GameObject::delObject(unique_id);
		}
	}

};

BinTree * CreatePlayerTree()
{
	BinTree *playerTree = BinTree::CreateTree([](GameObject* const pObj, const float dt)->int {
		ObjCreator::Character *pChar = dynamic_cast<ObjCreator::Character*>(pObj);
		sf::Vector2f ctrl = { 0.f,0.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ctrl.x -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ctrl.x += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ctrl.y += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ctrl.y -= 1.f;
		ctrl = CommResMeth::normalize(ctrl);
		pChar->setVelocity(ctrl * pChar->getSpeed());

		return TREE_GOTO_RIGHT;
	});

	playerTree->head->right = BinTree::CreateNode([](GameObject* const pObj, const float dt)->int {
		ObjCreator::Player *pPlayer = dynamic_cast<ObjCreator::Player*>(pObj);
		if (pPlayer && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) // unknown why sometime pPlayer is null
			pPlayer->onFire(dt);
		return TREE_GOTO_HEAD;
	});

	return playerTree;
}
