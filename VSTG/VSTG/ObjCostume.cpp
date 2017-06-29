#include "ObjCostume.h"
#include "SceneGame.hpp"

ObjCostume::ObjCostume(sf::Vector2f pos, ExitCondition condition)
{
}

void ObjCostume::update(float dt)
{
	if (nextMode == nullptr)
		return;
	if (condition & ExitCondition::HP && hp < exitStatus.minHp) {
		spornNext();
	}
	if (condition & ExitCondition::TIME) {
		if (duration > exitStatus.maxTime) {
			spornNext();
		}
		else {
			duration += dt;
		}
	}
	if (condition & ExitCondition::POS_X && 
		position.x < exitStatus.minX && position.x > exitStatus.maxX) {
		spornNext();
	}
	if (condition & ExitCondition::POS_Y &&
		position.y < exitStatus.minY && position.y > exitStatus.maxY) {
		spornNext();
	}
	if (condition & ExitCondition::DIST) {
		for (auto pPlayer : SceneGame::layerPlayer) {
			if (pPlayer) {
				const sf::Vector2f & posPlayer = pPlayer->getPosition();
				const sf::Vector2f diffpos = position - posPlayer;
				if (diffpos.x * diffpos.x + diffpos.y * diffpos.y < exitStatus.dist * exitStatus.dist) {
					spornNext();
				}
			}
		}
	}
}

void ObjCostume::spornNext()
{
}

void ObjCostume::spornBy(ObjCharacter & parent)
{
}
