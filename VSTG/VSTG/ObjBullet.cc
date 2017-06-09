#include "ObjBullet.hpp"
#include "ObjEnemy.hpp"
#include "SceneGame.hpp"

ObjBullet::ObjBullet(float x, float y) :
	GameObject()
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = -300;
	colliderSize = radius = 3;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setPosition(x, y);
	pSprite->setOrigin(radius, radius);
	drawCollider = pSprite;

	type = GameObject::BULLET;
}

void ObjBullet::Update(const float dt)
{
	if (!Essential::inGamecanvas(position)) {
		SceneGame::layerDelete.insert(shared_from_this());
	}
//	if (position.y < 0) {
//		SceneGame::layerDelete.insert(shared_from_this());
//	}
}

void ObjBullet::FixedUpdate(const float dt)
{
	position += velocity * dt;

	pSprite->setPosition(position);
}

void ObjBullet::OnCollisionEnter(std::shared_ptr<GameObject> pOther){
	if (pOther->GetType() == GameObject::ENEMY){
		pOther->OnCollisionEnter(shared_from_this());
	}
}
