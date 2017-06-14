#pragma once

#include "../ObjEnemy.hpp"
#include "../ObjCreator.h"
#include "../ObjEnemyBullet.h"

//Forward Declare
namespace ObjCreator {
	enum EnemyBulletType :int;
}

class EnemyDuck : public ObjEnemy {
public:
	EnemyDuck(sf::Vector2f pos, sf::Vector2f vel, ObjCreator::EnemyBulletType bullet);
	void Update(const float dt);
private:
	float timer;
	ObjCreator::EnemyBulletType bullet;
	static constexpr float coolDown = 1.0f;
};