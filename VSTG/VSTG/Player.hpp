#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"

class Player : public GameObject{
private:
	sf::CircleShape sprite;
	sf::Vector2<float> velocity;
	float originX, originY;
	float radius;
	float speed;
	bool up, down, left, right;
	bool fire;
	int cooldown;
public:
	Player();
	void Update();
	void OnKeyPressed(sf::Event::KeyEvent key);
	void OnKeyReleased(sf::Event::KeyEvent key);
	std::string GetType(){ return "player"; }
	void OnCollisionEnter(GameObject *other);
};
