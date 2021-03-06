#pragma once

#include "ObjCharacter.h"
#include <string>

class ObjBullet : public ObjCharacter{
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	sf::Vector2<float> velocity;
	float rotation;
public:
	ObjBullet(sf::Vector2f pos, sf::Vector2f vel = sf::Vector2f(0.0f, -300.0f));
	void Update(const float dt);
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
};
