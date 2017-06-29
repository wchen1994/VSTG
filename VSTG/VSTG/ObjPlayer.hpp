#pragma once


#include <SFML/Graphics.hpp>
#include <cmath>

#include "ObjCharacter.h"

class ObjPlayer : public ObjCharacter{
public:
	struct StructInput {
		bool isChange;
		bool up, down, left, right;
		bool fire;
	};
private:
	std::shared_ptr<sf::CircleShape> pSprite;
	float moveSpeed;
	bool up, down, left, right;
	bool fire;
	float cooldown;
	int playerNumb;
	static constexpr float cooldownDuration = 0.05f;
public:
	ObjPlayer(sf::Vector2f pos, int playerNumb);
	void Update(const float dt);
	StructInput UpdateInput();
	void UpdateInput(StructInput & input);
	void FixedUpdateInv(const float dt);
	void LateUpdate();
	void OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther);
};
