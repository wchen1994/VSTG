#include "ObjCharacter.h"
#include "SceneGame.hpp"

ObjCharacter::ObjCharacter():
	ObjCharacter(sf::Vector2f(0.0f,0.0f), sf::Vector2f(0.0f,0.0f), 0.0f, 0.0f)
{
}

ObjCharacter::ObjCharacter(sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed):
	GameObject(pos),
	brdPos(-10, -10),
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

ObjCharacter::~ObjCharacter()
{
	
}

void ObjCharacter::FixedUpdate(const float dt)
{
	if (!isDelete) {
		position += velocity * dt;
		rotation += rotSpeed * dt;

//		brdPos = SceneGame::brd.UpdateObjectPos(shared_from_derived<ObjCharacter>());

		if (drawSprite) {
			drawSprite->setPosition(position);
			drawSprite->setRotation(rotation);
		}
		drawCollider->setPosition(position);
		drawCollider->setRotation(rotation);
	}
}

sf::Packet ObjCharacter::GetPacket() //Legacy
{
	sf::Packet packet_out;
	packet_out << int(type) << sf::Uint32(hashOID) << sf::Uint32(unique_id) << position.x << position.y << velocity.x << velocity.y << rotation << rotSpeed;
	return packet_out;
}

void ObjCharacter::ProcessPacket(sf::Packet & packet)
{
	packet << int(type) << sf::Uint32(hashOID) << sf::Uint32(unique_id) << position.x << position.y << velocity.x << velocity.y << rotation << rotSpeed;
}

void ObjCharacter::Draw(sf::RenderTarget& gfx) {
	if (drawSprite) {
		gfx.draw(*drawSprite);
	}
	else if (drawCollider) {
		gfx.draw(*drawCollider);
	}
#if defined(_DEBUG_COLLIDER) && defined(_DEBUG)
	if (drawCollider) {
		gfx.draw(*drawCollider);
	}
#endif
}

void ObjCharacter::OnCollisionEnter(std::shared_ptr<ObjCharacter> pOther) {
}