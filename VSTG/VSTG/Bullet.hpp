#pragma once

#include "GameObject.hpp"
#include <string>

class Bullet : public GameObject{
private:
	sf::RenderWindow *wnd;
	sf::CircleShape sprite;
	sf::Vector2<float> velocity;
	float radius;
public:
	Bullet(sf::RenderWindow *wnd, float x, float y);
	void Update();
	std::string GetType(){ return "bullet"; }
	void OnCollisionEnter(GameObject *other);
};
