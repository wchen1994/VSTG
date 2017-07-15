#include "ObjEnemy.hpp"
#include "ObjBullet.hpp"
#include "ObjPlayer.hpp"
#include "SceneBulletHell.hpp"
#include <cmath>

ObjEnemy::ObjEnemy(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed) :
	ObjCharacter(pos, vel, rot, rotSpeed)
{
	pCollider = std::make_shared<sf::CircleShape>(sf::CircleShape());
	drawCollider = pCollider;

	type = GameObject::ENEMY;
	typeInteract = GameObject::GameObjectType(GameObject::BULLET | GameObject::PLAYER);
}

void ObjEnemy::Update(const float dt){
	if (isDelete) {
		SceneBulletHell::layerDelete.insert(shared_from_derived<ObjEnemy>());
	} else if (position.x < CommResMeth::GameCanvas.left-colliderSize || 
		position.x > CommResMeth::GameCanvas.left + CommResMeth::GameCanvas.width + colliderSize || 
		position.y > CommResMeth::GameCanvas.top + CommResMeth::GameCanvas.height + colliderSize) {
		SceneBulletHell::layerDelete.insert(shared_from_derived<ObjEnemy>());
	}
}

void ObjEnemy::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	GameObjectType type = pOther->GetType();
	if (type == GameObject::BULLET){
		SceneBulletHell::layerDelete.insert(pOther);
		hp -= pOther->GetDamage();
		if (hp < 0) {
			isDelete = true;
		}
	}
	else if (type == GameObject::PLAYER) {
		pOther->OnCollisionEnter(shared_from_derived<ObjEnemy>());
	}
}

