#pragma once
#include "ObjEnemy.hpp"
#include "ObjPlayer.hpp"
#include "ObjBullet.hpp"
#include "Essential.hpp"

class ObjEnemyBullet : public ObjBullet {
public:
	ObjEnemyBullet(sf::Vector2f pos, sf::Vector2f vel);
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
};