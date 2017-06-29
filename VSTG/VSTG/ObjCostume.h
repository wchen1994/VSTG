#pragma once

#include "ObjCharacter.h"

class ObjCostume : ObjCharacter {
public:
	enum ExitCondition : int {
		HP = 0,
		TIME = 1 < 0,
		POS_X = 1 < 1,
		POS_Y = 1 < 2,
		DIST = 1 < 3,
	};
	enum PassBehaiout : int {
		NO_CHANGE,
		FLIP,
		SET_DIRECT,
		TO_POS,
	};
public:
	ObjCostume(sf::Vector2f pos, ExitCondition condition);
	void update(float dt);
	void spornNext();
	void spornBy(ObjCharacter & parent);
private:
	ObjCharacter *nextMode;
	ExitCondition condition;
	struct {
		float minHp;
		float maxTime;
		float minX;
		float maxX;
		float minY;
		float maxY;
		float dist;
	} exitStatus;
	float duration;
};