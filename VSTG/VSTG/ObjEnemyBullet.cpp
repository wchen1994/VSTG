#include "ObjEnemyBullet.h"

ObjEnemyBullet::ObjEnemyBullet(sf::Vector2f pos, sf::Vector2f vel, EBulletType bType) :
	ObjBullet(pos, vel)
{
	type = GameObject::ENEMYNOTDEAD;
	switch (bType) {
	case ROUND:
		SetSpeed(100.0f);
		break;
	case POINTING:
	default:
		SetSpeed(400.0f);
		break;
	}
}

void ObjEnemyBullet::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther)
{
	if (pOther->GetType() == GameObject::PLAYER) {
		pOther->OnCollisionEnter(shared_from_derived<ObjEnemyBullet>());
	}
}
