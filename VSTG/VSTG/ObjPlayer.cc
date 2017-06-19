#include "ObjPlayer.hpp"
#include "ObjBullet.hpp"
#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include "SceneGame.hpp"
#include "ObjCreator.h"

ObjPlayer::ObjPlayer() :
	ObjPlayer(sf::Vector2f(0.0f, 0.0f))
{
}

ObjPlayer::ObjPlayer(sf::Vector2f pos) :
	ObjCharacter(pos, sf::Vector2f(0.0f,0.0f), 0.0f, 0.0f)
{
	up = down = left = right = false;
	fire = false;
	moveSpeed = 180.0f;
	cooldown = 0;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(colliderSize);
	pSprite->setOrigin(colliderSize, colliderSize);
	pSprite->setPosition(position);
	drawCollider = pSprite;

	type = GameObject::PLAYER;
}

void ObjPlayer::Update(const float dt){
	velocity = { 0.0f,0.0f };
	if (up)
		velocity.y -= 1.0f;
	if (down)
		velocity.y += 1.0f;
	if (left)
		velocity.x -= 1.0f;
	if (right)
		velocity.x += 1.0f;

	// Player Movement
	const float sqlen = velocity.x*velocity.x + velocity.y*velocity.y;
	if (sqlen != 0) {
		const float len = sqrt(sqlen);
		velocity *= moveSpeed / len;
	}

	// Player Fire
	if (cooldown > 0) {
		cooldown -= dt;
	}
	else if (fire && !Essential::isClient) {
//		const std::shared_ptr<ObjBullet> pBullet = std::make_shared<ObjBullet>(ObjBullet(position));
		const std::shared_ptr<ObjBullet> pBullet1 = ObjCreator::CreateBullet(ObjCreator::BulletType::BLUE, position, 0.0f);
		SceneGame::layerDefault.insert(pBullet1);
		SceneGame::layerBullet.insert(pBullet1);
		const std::shared_ptr<ObjBullet> pBullet2 = ObjCreator::CreateBullet(ObjCreator::BulletType::GREEN, position, 30.0f);
		SceneGame::layerDefault.insert(pBullet2);
		SceneGame::layerBullet.insert(pBullet2);
		const std::shared_ptr<ObjBullet> pBullet3 = ObjCreator::CreateBullet(ObjCreator::BulletType::GREEN, position, -30.0f);
		SceneGame::layerDefault.insert(pBullet3);
		SceneGame::layerBullet.insert(pBullet3);
		cooldown = cooldownDuration;
	}
}

ObjPlayer::StructInput ObjPlayer::UpdateInput()
{	
	// Handle Input
	static StructInput input;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		up = true;
	}
	else {
		up = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		down = true;
	}
	else {
		down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		left = true;
	}
	else {
		left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		right = true;
	}
	else {
		right = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		fire = true;
	}
	else {
		fire = false;
	}

	input.isChange = false;
	if (input.up != up) {
		input.up = up;
		input.isChange = true;
	}
	if (input.left != left) {
		input.left = left;
		input.isChange = true;
	}
	if (input.down != down) {
		input.down = down;
		input.isChange = true;
	}
	if (input.right != right) {
		input.right = right;
		input.isChange = true;
	}
	if (input.fire != fire) {
		input.fire = fire;
		input.isChange = true;
	}

	return input;
}

void ObjPlayer::UpdateInput(StructInput & input)
{
	up = input.up;
	down = input.down;
	left = input.left;
	right = input.right;
	fire = input.fire;
}

void ObjPlayer::LateUpdate()
{
	static float boundary[] = {
		float(Essential::GameCanvas.left),
		float(Essential::GameCanvas.left + Essential::GameCanvas.width - 1),
		float(Essential::GameCanvas.top),
		float(Essential::GameCanvas.top + Essential::GameCanvas.height - 1),
	};

	if (position.x < boundary[0])
		position.x = boundary[0];
	if (position.x > boundary[1])
		position.x = boundary[1];
	if (position.y < boundary[2])
		position.y = boundary[2];
	if (position.y > boundary[3])
		position.y = boundary[3];

	drawCollider->setPosition(position);
	if (drawSprite)
		drawSprite->setPosition(position);
}

void ObjPlayer::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	GameObjectType type = pOther->GetType();
	if ( type == GameObject::ENEMY || type == GameObject::ENEMYNOTDEAD){
		SceneGame::layerDelete.insert(pOther);
		hp -= pOther->GetDamage();
		if (hp < 0) {
			SceneGame::layerDelete.insert(shared_from_derived<ObjPlayer>());
		}
	}
}
