#include "ObjEnemyBullet.h"

ObjEnemyBullet::ObjEnemyBullet(float x, float y, float vx, float vy, EBulletType type) :
	ObjEnemy(x, y, vx, vy)
{
	switch (type) {
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
	if (pOther->GetCID() == ObjPlayer::hashCID) {
		pOther->OnCollisionEnter(shared_from_this());
	}
}
