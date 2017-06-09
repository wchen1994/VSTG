#pragma once
#include "../ObjEnemy.hpp"
#include "../ObjPlayer.hpp"
#include "../Essential.hpp"

class ObjEnemyBullet : public ObjEnemy {
public:
	enum EBulletType{ROUND, POINTING, COUNT};
public:
	ObjEnemyBullet(float x, float y, float vx, float vy, EBulletType type);
	void OnCollisionEnter(std::shared_ptr<GameObject> pOther);
};