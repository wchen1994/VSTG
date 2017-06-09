#include "ObjEnemyBullet.h"

ObjEnemyBullet::ObjEnemyBullet(float x, float y, float vx, float vy, EBulletType bType) :
	ObjEnemy(x, y, vx, vy)
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

void ObjEnemyBullet::OnCollisionEnter(std::shared_ptr<GameObject> pOther)
{
	if (pOther->GetType() == GameObject::PLAYER) {
		pOther->OnCollisionEnter(shared_from_this());
	}
}
