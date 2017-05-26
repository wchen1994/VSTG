#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"

class ObjPlayer : public GameObject{
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	sf::Vector2f velocity;
	float originX, originY;
	float radius;
	float speed;
	bool up, down, left, right;
	bool fire;
	float cooldown;
	static constexpr float cooldownDuration = 0.05f;
public:
	ObjPlayer();
	void Update(const float dt);
	void FixedUpdate(const float dt);
	void OnCollisionEnter(std::shared_ptr<GameObject> pOther);
};
