#pragma once

#include "ObjCharacter.h"

class ObjCostume : public ObjCharacter {
public:
	struct Behaviour {
		enum Type {
			NONE,
			BOUNCE,
			TO_POS,
			SET_VEL,
		} type;
		union {
			sf::Vector2f vel;
			sf::Vector2f pos;
		} u = {sf::Vector2f(0.0f, 0.0f)};
	};
	struct ExitInfo {
		enum Condition : int {
			HP = 0,
			TIME = 1 < 0,
			POS_X = 1 < 1,
			POS_Y = 1 < 2,
			DIST = 1 < 3,
		} condition;
		struct {
			float minHp;
			float maxTime;
			float minX;
			float maxX;
			float minY;
			float maxY;
			float dist;
		} status;
		bool isKill;
	};
	struct File {
		char objName[128];
		char textureName[128];
		ExitInfo exitInfo;
		Behaviour behaviour;
	};
public:
	ObjCostume(const ObjCostume & parent, const Behaviour & behaviour, const ExitInfo & exitInfo, std::string nextObjName);
	ObjCostume(const sf::Vector2f & pos, const sf::Vector2f & vel, const float rot, const float rotSp, 
		const Behaviour & behaviour, const ExitInfo & exitInfo, std::string nextObjName);
	void Inherit(const ObjCostume &parent, ExitInfo::Condition exitState);
	void Update(const float dt) override;
	void Exit();
private:
	std::shared_ptr<ObjCostume> nextObj;
	const ExitInfo & exitInfo;
	float duration;
	ExitInfo::Condition exitState;
	Behaviour behaviour;
};