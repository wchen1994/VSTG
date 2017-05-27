#pragma once

#include "GameObject.hpp"
#include <string>

class ObjEnemy : public GameObject{
private:
	std::shared_ptr<sf::CircleShape> pCollider;
	std::shared_ptr<sf::Texture> pTexture;
	sf::Vector2<float> velocity;
	static constexpr float speed = 120.0f;
	static constexpr float radius=10.0f;
public:
	ObjEnemy(float x, float y);
	ObjEnemy(float x, float y, float vx, float vy);
	void Update(const float dt);
	void FixedUpdate(const float dt);
	void OnCollisionEnter(std::shared_ptr<GameObject> pOther);
};