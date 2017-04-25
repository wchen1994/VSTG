#pragma once

#include "GameObject.hpp"
#include <string>

class Bullet : public GameObject{
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	sf::Vector2<float> velocity;
	float radius;
public:
	Bullet(float x, float y);
	void Update(float dt);
	void FixedUpdate(const float& dt);
	std::string GetType(){ return "bullet"; }
	void OnCollisionEnter(std::shared_ptr<GameObject> other);
};
