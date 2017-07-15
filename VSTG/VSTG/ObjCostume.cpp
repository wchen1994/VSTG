#include "ObjCostume.h"
#include "SceneGame.hpp"

ObjCostume::ObjCostume(const ObjCostume & parent, const Behaviour & behaviour, const ExitInfo & exitInfo, std::string nextObjName) : 
	ObjCostume(parent.position, parent.velocity, parent.rotation, parent.rotSpeed, behaviour, exitInfo, nextObjName)
{
}

ObjCostume::ObjCostume(const sf::Vector2f & pos, const sf::Vector2f & vel, const float rot, const float rotSp, 
	const Behaviour & behaviour, const ExitInfo & exitInfo, std::string nextObjName) :
	ObjCharacter(),
	exitInfo(exitInfo),
	behaviour(behaviour)
{
	position = pos;
	velocity = vel;
	rotation = rot;
	rotSpeed = rotSp;
	duration = 0.0f;
}

void ObjCostume::Inherit(const ObjCostume & parent, ExitInfo::Condition exitState)
{
	position = parent.position;
	velocity = parent.velocity;
	rotation = parent.rotation;
	rotSpeed = parent.rotSpeed;

	switch (behaviour.type)
	{
	case Behaviour::SET_VEL: {
		velocity = behaviour.u.vel;
		break;
	}
	default:
		break;
	}
}

void ObjCostume::Update(float dt)
{
	switch (behaviour.type)
	{
	case Behaviour::BOUNCE:
	{
		break;
	}
	case Behaviour::TO_POS:
	{
		const sf::Vector2f diffPos = behaviour.u.pos - position;
		if (diffPos.x + diffPos.y < 2) {
			velocity = { 0.0f, 0.0f };
		}
		else {
			velocity = Essential::normalize(diffPos) * speed;
		}
		break;
	}
	case Behaviour::SET_VEL: {
		break;
	}
	default:
		break;
	}

	// Check Exit
	if (exitInfo.condition & ExitInfo::Condition::HP && hp < exitInfo.status.minHp)
		Exit();
	if (exitInfo.condition & ExitInfo::Condition::TIME) {
		if (duration > exitInfo.status.maxTime)
			Exit();
		duration += dt;
	}
	if (exitInfo.condition & ExitInfo::Condition::POS_X && (position.x < exitInfo.status.minX || position.x > exitInfo.status.maxX))
		Exit();
	if (exitInfo.condition & ExitInfo::Condition::POS_Y && (position.y < exitInfo.status.minY || position.y > exitInfo.status.maxY))
		Exit();
	if (exitInfo.condition & ExitInfo::Condition::DIST) {
		// Use board to check
	}
}

void ObjCostume::Exit()
{
//	if (nextObj) {
//		nextObj->Inherit(*this, exitState);
//		SceneGame::layerDefault.insert(nextObj);
//	}
	if (exitInfo.isKill)
		SceneGame::layerDelete.insert(shared_from_derived<ObjCharacter>());
}

