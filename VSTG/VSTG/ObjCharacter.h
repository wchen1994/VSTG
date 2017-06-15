#pragma once

#include "GameObject.hpp"
#include "Essential.hpp"
//#define _DEBUG_COLLIDER

class ObjCharacter : public GameObject {
public:
	ObjCharacter();
	ObjCharacter(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	void ObjCharacter::Draw(sf::RenderTarget& gfx);
	virtual void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
	virtual void FixedUpdate(const float dt);
	sf::Packet GetPacket();
	void ProcessPacket(sf::Packet &packet);
protected:
	std::shared_ptr<sf::Shape> drawCollider;
	std::shared_ptr<sf::Sprite> drawSprite;
	std::shared_ptr<sf::Texture> pTexture;
	float colliderSize;
	sf::Vector2i brdPos;
	float damage;
	float hp;
	sf::Vector2<float> velocity;
	float rotSpeed;
	float rotation;
	float speed;
public:
	sf::Vector2i GetBrdPos() const { return brdPos; }
	void SetBrdPos(const sf::Vector2i brdPos) { this->brdPos = brdPos; }

	std::shared_ptr<sf::Sprite> GetSprite() { return drawSprite; }
	void SetSprite(const std::shared_ptr<sf::Sprite> pSprite) { drawSprite = pSprite; }

	std::shared_ptr<sf::Texture> GetTexturePtr() const { return pTexture; }
	void SetTexturePtr(const std::shared_ptr<sf::Texture> pTex) { pTexture = pTex; }

	float GetDamage() const { return damage; }
	void SetDamage(const float damage) { this->damage = damage; }

	float GetHp() const { return hp; }
	void SetHp(const float hp) { this->hp = hp; }

	float GetRotation() const { return rotation; }
	void SetRotation(const float angle) { rotation = angle; }

	float GetRotationSpeed() const { return rotSpeed; }
	void SetRotationSpeed(const float speed) { rotSpeed = speed; }

	float GetColliderSize() const { return colliderSize; }
	void SetColliderSize(const float s) { colliderSize = s; }

	sf::Vector2f GetVelocity() const { return velocity; }
	void SetVelocity(const sf::Vector2f vel) {
		velocity = vel;
		speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);
	}

	float GetSpeed() const { return speed; }
	void SetSpeed(const float s) {
		velocity.x *= s / speed;
		velocity.y *= s / speed;
		speed = s;
	}
};