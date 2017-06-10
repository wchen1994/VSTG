#include "ObjPlayer.hpp"
#include "ObjBullet.hpp"
#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include "SceneGame.hpp"

ObjPlayer::ObjPlayer() :
	ObjCharacter()
{
	up = down = left = right = false;
	fire = false; radius = 5;
	position.x = float(Essential::GameCanvas.left + Essential::GameCanvas.width/2);
	position.y = float(Essential::GameCanvas.top + Essential::GameCanvas.height * 4/5);
	velocity.x = 0;
	velocity.y = 0;
	speed = 180;
	cooldown = 0;
	originX = originY = radius;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setOrigin(originX, originY);
	pSprite->setPosition(position);
	drawCollider = pSprite;

	// Setup ID
	type = GameObject::PLAYER;
}

void ObjPlayer::Update(const float dt){
	// Handle Input
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


	velocity = { 0.0f,0.0f };
	if (up)
		velocity.y -= 1.0f;
	if (down)
		velocity.y += 1.0f;
	if (left)
		velocity.x -= 1.0f;
	if (right)
		velocity.x += 1.0f;
}

void ObjPlayer::FixedUpdate(const float dt)
{
	// Player Movement
	const float sqlen = velocity.x*velocity.x + velocity.y*velocity.y;
	static float boundary[] = { 
		float(Essential::GameCanvas.left),
		float(Essential::GameCanvas.left + Essential::GameCanvas.width - 1),
		float(Essential::GameCanvas.top),
		float(Essential::GameCanvas.top + Essential::GameCanvas.height - 1),
	};
	if (sqlen != 0) {
		const float len = sqrt(sqlen);
		position += velocity / len * speed * dt;
		if (position.x < boundary[0])
			position.x = boundary[0];
		if (position.x > boundary[1])
			position.x = boundary[1];
		if (position.y < boundary[2])
			position.y = boundary[2];
		if (position.y > boundary[3])
			position.y = boundary[3];
	}
	pSprite->setPosition(position);

	// Player Fire
	if (cooldown > 0) {
		cooldown -= dt;
	}
	else if (fire) {
		const std::shared_ptr<ObjBullet> pBullet = std::make_shared<ObjBullet>(ObjBullet(position));
		SceneGame::layerDefault.insert(pBullet);
		SceneGame::layerBullet.insert(pBullet);
		cooldown = cooldownDuration;
	}
}

void ObjPlayer::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	GameObjectType type = pOther->GetType();
	if ( type == GameObject::ENEMY || type == GameObject::ENEMYNOTDEAD){
		SceneGame::layerDelete.insert(pOther);
		hp -= pOther->GetDamage();
		if (hp < 0) {
			Essential::isGameOver = true;
		}
	}
}
