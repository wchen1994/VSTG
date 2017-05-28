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
protected:
	sf::Vector2<float> position;
	std::shared_ptr<sf::Shape> drawCollider;
	std::shared_ptr<sf::Sprite> drawSprite;
	float colliderSize;
	sf::Vector2i brdPos;
	static char classID[128];
	static size_t hashCID;
	char objectID[128];
	size_t hashOID;
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
	size_t GetCID() const { return hashCID; }
	size_t GetOID() const { return hashOID; }
	void SetOID(const uint32_t id) { hashOID = id; }
	sf::Vector2i GetBrdPos() const { return brdPos; }
	sf::Sprite& GetSprite() const { return *drawSprite; }

	float GetColliderSize() const { return colliderSize; }
	void SetColliderSize(const float s) { colliderSize = s; }
};
