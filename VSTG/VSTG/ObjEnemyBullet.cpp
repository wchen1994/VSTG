#include "ObjEnemyBullet.h"

ObjEnemyBullet::ObjEnemyBullet(sf::Vector2f pos, sf::Vector2f vel) :
	ObjBullet(pos, vel)
{
}

void ObjEnemyBullet::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther)
{
	if (pOther->GetType() == GameObject::PLAYER) {
		pOther->OnCollisionEnter(shared_from_derived<ObjEnemyBullet>());
	}
}
