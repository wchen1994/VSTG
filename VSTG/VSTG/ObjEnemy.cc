#include "ObjEnemy.hpp"
#include "ObjBullet.hpp"
#include "ObjPlayer.hpp"
#include "SceneGame.hpp"
#include <cmath>

ObjEnemy::ObjEnemy(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed) :
	ObjCharacter(pos, vel, rot, rotSpeed)
{
	pCollider = std::make_shared<sf::CircleShape>(sf::CircleShape());
	drawCollider = pCollider;
	drawSprite = std::make_shared<sf::Sprite>(sf::Sprite());

	type = GameObject::ENEMY;
}

void ObjEnemy::Update(const float dt){
	if (isDelete) {
		SceneGame::layerDelete.insert(shared_from_derived<ObjEnemy>());
	} else if (position.x < Essential::GameCanvas.left-radius || 
		position.x > Essential::GameCanvas.left + Essential::GameCanvas.width + radius || 
		position.y > Essential::GameCanvas.top + Essential::GameCanvas.height + radius) {
		SceneGame::layerDelete.insert(shared_from_derived<ObjEnemy>());
	}
}

void ObjEnemy::FixedUpdate(const float dt)
{
	if (!isDelete) {
		position += velocity * dt;
		rotation += rotSpeed * dt;

//		brdPos = SceneGame::brd.UpdateObjectPos(shared_from_derived<ObjEnemy>());
		SceneGame::brd.UpdateObjectPos(shared_from_derived<ObjEnemy>());

		pCollider->setPosition(position);
		drawSprite->setPosition(position);
		drawSprite->setRotation(rotation);
	}
}

void ObjEnemy::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	GameObjectType type = pOther->GetType();
	if (type == GameObject::BULLET){
		SceneGame::layerDelete.insert(pOther);
		hp -= pOther->GetDamage();
		if (hp < 0) {
			isDelete = true;
		}
	}
	else if (type == GameObject::PLAYER) {
		pOther->OnCollisionEnter(shared_from_derived<ObjEnemy>());
	}
}

