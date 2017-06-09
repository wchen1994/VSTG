#pragma once

#include "GameObject.hpp"
#include <string>
#include <random>

class ObjEnemy : public GameObject{
private:
	std::shared_ptr<sf::CircleShape> pCollider;
	std::shared_ptr<sf::Texture> pTexture;
	sf::Vector2<float> velocity;
	float rotSpeed;
	float rotation;
	float speed;
	static constexpr float radius=10.0f;
public:
	ObjEnemy(float x, float y);
	ObjEnemy(float x, float y, float vx, float vy);
	void Update(const float dt);
	void FixedUpdate(const float dt);
	void OnCollisionEnter(std::shared_ptr<GameObject> pOther);
	virtual ObjEnemy* Clone() const;
public:
	float GetRotation() const { return rotation; }
	void SetRotation(const float angle) { rotation = angle; }
	
	float GetRotationSpeed() const { return rotSpeed; }
	void SetRotationSpeed(const float speed) { rotSpeed = speed; }
	
	sf::Vector2f GetVelocity() const { return velocity; }
	void SetVelocity(const sf::Vector2f vel) { velocity = vel; }
	
	std::shared_ptr<sf::Texture> GetTexturePtr() const { return pTexture; }
	void SetTexturePtr(const std::shared_ptr<sf::Texture> pTex) { pTexture = pTex; }

	float GetColliderSize() const { return colliderSize; }
	void SetColliderSize(const float s) { colliderSize = s; pCollider->setRadius(s); pCollider->setOrigin(s, s); }

	float GetSpeed() const { return speed; }
	void SetSpeed(const float s) { 
		velocity.x *= s / speed;
		velocity.y *= s / speed; 
		speed = s;
	}
};