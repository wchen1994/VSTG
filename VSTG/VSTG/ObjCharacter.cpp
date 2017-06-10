#include "ObjCharacter.h"
#include "SceneGame.hpp"

ObjCharacter::ObjCharacter():
	ObjCharacter(sf::Vector2f(0.0f,0.0f), sf::Vector2f(0.0f,0.0f), 0.0f, 0.0f)
{
}

ObjCharacter::ObjCharacter(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed):
	GameObject(pos),
	brdPos(0, 0),
	drawCollider(nullptr),
	drawSprite(nullptr),
	hp(100.0f),
	damage(30.0f),
	colliderSize(0.0f),
	velocity(vel),
	rotation(rot),
	rotSpeed(rotSpeed)
{
	speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);
}

void ObjCharacter::FixedUpdate(const float dt)
{
	if (!isDelete) {
		position += velocity * dt;
		rotation += rotSpeed * dt;

		brdPos = SceneGame::brd.UpdateObjectPos(shared_from_derived<ObjCharacter>());

		if (drawSprite) {
			drawSprite->setPosition(position);
			drawSprite->setRotation(rotation);
		}
		drawCollider->setPosition(position);
		drawCollider->setRotation(rotation);
	}
}

void ObjCharacter::Draw(sf::RenderTarget& gfx) {
	if (drawSprite) {
		gfx.draw(*drawSprite);
	}
	else if (drawCollider) {
		gfx.draw(*drawCollider);
	}
#ifdef _DEBUG_COLLIDER
	if (drawCollider) {
		gfx.draw(*drawCollider);
	}
#endif
}

void ObjCharacter::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther) {
}