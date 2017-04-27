#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"

class Player : public GameObject{
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
	Player();
	void Update(const float& dt);
	void FixedUpdate(const float& dt);
	void OnKeyPressed(sf::Event::KeyEvent key);
	void OnKeyReleased(sf::Event::KeyEvent key);
	std::string GetType() const { return "player"; }
	void OnCollisionEnter(std::shared_ptr<GameObject> other);
};
