#pragma once

#include "GameObject.hpp"
#include <string>

class Enemy : public GameObject{
private:
	sf::CircleShape sprite;
	sf::Vector2<float> velocity;
	float radius;
public:
	Enemy(float x, float y);
	Enemy(float x, float y, float vx, float vy);
	void Update();
	void OnCollisionEnter(GameObject *other);
	std::string GetType(){ return "enemy"; }
};