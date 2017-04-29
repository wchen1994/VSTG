#pragma once

#include "GameObject.hpp"
#include <string>

class Enemy : public GameObject{
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	sf::Vector2<float> velocity;
	static constexpr float speed = 120.0f;
	static constexpr float radius=10.0f;
public:
	Enemy(float x, float y);
	Enemy(float x, float y, float vx, float vy);
	void Update(const float& dt);
	void FixedUpdate(const float& dt);
	void OnCollisionEnter(std::shared_ptr<GameObject> other);
};