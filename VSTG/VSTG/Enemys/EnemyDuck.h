#pragma once

#include "../ObjEnemy.hpp"
#include "../ObjCreator.h"
#include "../ObjEnemyBullet.h"

class EnemyDuck : public ObjEnemy {
public:
	EnemyDuck(sf::Vector2f pos, sf::Vector2f vel, ObjEnemyBullet::EBulletType type);
	void Update(const float dt);
private:
	float timer;
	ObjEnemyBullet::EBulletType bullet;
	static constexpr float coolDown = 1.0f;
};