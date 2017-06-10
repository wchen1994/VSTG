#pragma once

#include "ObjCharacter.h"
#include <string>
#include <random>

class ObjEnemy : public ObjCharacter{
private:
	std::shared_ptr<sf::CircleShape> pCollider;
	static constexpr float radius=10.0f;
public:
	ObjEnemy(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	void Update(const float dt);
	void FixedUpdate(const float dt);
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
public:
};