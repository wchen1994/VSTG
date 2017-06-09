#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <set>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>

//#define _DEBUG_COLLIDER

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	enum GameObjectType{UNKONW, PLAYER, BULLET, ENEMY, ENEMYNOTDEAD, COUNT};
protected:
	sf::Vector2<float> position;
	std::shared_ptr<sf::Shape> drawCollider;
	std::shared_ptr<sf::Sprite> drawSprite;
	float colliderSize;
	sf::Vector2i brdPos;
	char objectID[128];
	size_t hashOID;
	float damage;
	float hp;
	bool isDelete;
	GameObjectType type;
private:
	std::hash<std::string> hashGen;
public:
	GameObject();
	sf::Vector2<float> getPosition() const { return position; }
	void setPosition(const sf::Vector2f &vec) { position = vec; }
	float getSize(){ return colliderSize; }
	virtual ~GameObject();
	virtual void Draw(sf::RenderTarget& gfx);
	virtual void Update(const float dt);
	virtual void FixedUpdate(const float dt);
	virtual void OnCollisionEnter(std::shared_ptr<GameObject> pOther);
	virtual GameObject* CLone() const;
public:
	std::string GetName() const { return objectID; }
	void SetName(const std::string id) { strcpy_s(objectID, id.c_str()); }
	size_t GetOID() const { return hashOID; }
	void SetOID(const uint32_t id) { hashOID = id; }
	sf::Vector2i GetBrdPos() const { return brdPos; }
	sf::Sprite& GetSprite() const { return *drawSprite; }

	float GetColliderSize() const { return colliderSize; }
	void SetColliderSize(const float s) { colliderSize = s; }

	float GetDamage() const { return damage; }
	void SetDamage(const float damage) { this->damage = damage; }

	float GetHp() const { return hp; }
	void SetHp(const float hp) { this->hp = hp; }

	GameObjectType GetType() const { return type; }
	void SetType(const GameObjectType type) { this->type = type; }
};
