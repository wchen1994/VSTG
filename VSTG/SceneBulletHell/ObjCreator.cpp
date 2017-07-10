#include "ObjCreator.h"

const double PI = 3.141592653589793238463;

namespace ObjCreator {
	std::shared_ptr<Character> ObjCreator::Character::Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board * brd)
	{
		std::shared_ptr<Character> pCharacter = std::make_shared<Character>(pos, pTex, brd);
		layerDefault[pCharacter->unique_id] = pCharacter;
		return pCharacter;
	}

	Character::Character(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board * brd) :
		Moveable(pos),
		GameObject(nullptr, pos, 0.f, "unname"),
		Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), sf::Vector2f(0.1f, 0.1f)),
		BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
		Collider(ColliderType::Circle, ColliderProperities(5.f)),
		BehaviourController(CreatePlayerTree()),
		velocity(sf::Vector2f()), speed(10.f)
	{
	}

	void Character::setVelocity(const sf::Vector2f & vel)
	{
		velocity = vel;
	}

	std::shared_ptr<Player> Player::Create(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board * brd)
	{
		std::shared_ptr<Player> pCharacter = std::make_shared<Player>(pos, pTex, brd);
		layerDefault[pCharacter->unique_id] = pCharacter;
		return pCharacter;
	}

	Player::Player(sf::Vector2f pos, std::shared_ptr<sf::Texture> pTex, Board * brd):
		Moveable(pos),
		GameObject(nullptr, pos, 0.f, "unname"),
		Renderer(pTex, sf::Vector2f(pTex->getSize().x / 2.f, pTex->getSize().y / 2.f), sf::Vector2f(0.1f, 0.1f)),
		BoardObj(brd, ColliderType::Circle, ColliderProperities(5.f)),
		Collider(ColliderType::Circle, ColliderProperities(5.f)),
		BehaviourController(CreatePlayerTree()),
		Character(pos, pTex, brd),
		counter(0.f)
	{
	}

	void Player::onFire(const float dt)
	{
		counter += dt;
		if (counter > coolDown) {
			// fires
			counter = 0.f;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			pPlayer->onFire(dt);
		return TREE_GOTO_HEAD;
	});

	return playerTree;
}
