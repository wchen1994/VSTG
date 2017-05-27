#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <set>
#include <iostream>
#include <string>
#include <memory>

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
	sf::Vector2<float> position;
	std::shared_ptr<sf::Drawable> drawCollider;
	std::shared_ptr<sf::Sprite> drawSprite;
	float colliderSize;
	sf::Vector2i brdPos;
	static char objectID[128];
	static size_t hashID;
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
	virtual std::string GetType() const { return objectID; }
	virtual size_t GetHash() const { return hashID; }
	sf::Vector2i GetBrdPos() const { return brdPos; }
};
