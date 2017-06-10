#pragma once


#include <SFML/Graphics.hpp>
#include <cmath>

#include "ObjCharacter.h"

class ObjPlayer : public ObjCharacter{
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	float moveSpeed;
	bool up, down, left, right;
	bool fire;
	float cooldown;
	static constexpr float cooldownDuration = 0.05f;
public:
	ObjPlayer();
	ObjPlayer(sf::Vector2f pos);
	void Update(const float dt);
	void LateUpdate();
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
};
