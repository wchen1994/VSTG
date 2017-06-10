#pragma once
#include "ObjEnemy.hpp"
#include "ObjPlayer.hpp"
#include "ObjBullet.hpp"
#include "Essential.hpp"

class ObjEnemyBullet : public ObjBullet {
public:
	enum EBulletType{ROUND, POINTING, COUNT};
public:
	ObjEnemyBullet(sf::Vector2f pos, sf::Vector2f vel, EBulletType type);
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
};