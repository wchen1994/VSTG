#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <set>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include <assert.h>
#include <climits>

//#define _DEBUG_COLLIDER

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	enum GameObjectType : int {UNKONW, PLAYER, BULLET, ENEMY, ENEMYNOTDEAD, COUNT};
protected:
	template <typename Derived>
	std::shared_ptr<Derived> shared_from_derived()
	{
		return std::static_pointer_cast<Derived>(shared_from_this());
	}
protected:
	sf::Vector2f position;
	char objectID[128];
	uint32_t hashOID;
	bool isDelete;
	GameObjectType type;
	uint32_t unique_id;
private:
	static uint32_t uniqueIdCounter;
public:
	GameObject();
	GameObject(sf::Vector2f pos);
	virtual ~GameObject();
	virtual void Draw(sf::RenderTarget& gfx);
	virtual void Update(const float dt);
	virtual void FixedUpdate(const float dt);
	virtual void LateUpdate();
	virtual GameObject* CLone() const;
public:
	sf::Vector2<float> getPosition() const { return position; }
	void setPosition(const sf::Vector2f &vec) { position = vec; }

	std::string GetName() const { return objectID; }
	void SetName(const std::string id) { strcpy_s(objectID, id.c_str()); }
	
	uint32_t GetOID() const { return hashOID; }
	void SetOID(const uint32_t id) { hashOID = id; }

	GameObjectType GetType() const { return type; }
	void SetType(const GameObjectType type) { this->type = type; }

	const unsigned int GetUniId() const { return unique_id; }
};
