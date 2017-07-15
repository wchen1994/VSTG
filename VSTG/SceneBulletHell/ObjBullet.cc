#include "ObjBullet.hpp"
#include "ObjEnemy.hpp"
#include "SceneBulletHell.hpp"

ObjBullet::ObjBullet(sf::Vector2f pos, sf::Vector2f vel) :
	ObjCharacter(pos, vel, 0.0f, 0.0f)
{
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	colliderSize = 3.0f;
	pSprite->setRadius(colliderSize);
	pSprite->setPosition(pos);
	pSprite->setOrigin(colliderSize, colliderSize);
	drawCollider = pSprite;
	drawSprite = std::make_shared<sf::Sprite>(sf::Sprite());

	type = GameObject::BULLET;
	typeInteract = GameObject::ENEMY;
}

void ObjBullet::Update(const float dt)
{
	if (!Essential::inGamecanvas(position)) {
		SceneBulletHell::layerDelete.insert(shared_from_derived<ObjBullet>());
	}
}

void ObjBullet::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther){
	if (pOther->GetType() == GameObject::ENEMY){
		pOther->OnCollisionEnter(shared_from_derived<ObjBullet>());
	}
}
