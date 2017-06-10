#include "ObjBullet.hpp"
#include "ObjEnemy.hpp"
#include "SceneGame.hpp"

ObjBullet::ObjBullet(sf::Vector2f pos, sf::Vector2f vel) :
	ObjCharacter(pos, vel, 0.0f, 0.0f)
{
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(colliderSize);
	pSprite->setPosition(pos);
	pSprite->setOrigin(colliderSize, colliderSize);
	drawCollider = pSprite;

	type = GameObject::BULLET;
}

void ObjBullet::Update(const float dt)
{
	if (!Essential::inGamecanvas(position)) {
		SceneGame::layerDelete.insert(shared_from_derived<ObjBullet>());
	}
}

void ObjBullet::FixedUpdate(const float dt)
{
	position += velocity * dt;

	pSprite->setPosition(position);
}

void ObjBullet::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	if (pOther->GetType() == GameObject::ENEMY){
		pOther->OnCollisionEnter(shared_from_derived<ObjBullet>());
	}
}
