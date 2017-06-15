#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "GameObject.hpp"
#include "ObjEnemy.hpp"

class Map {
public:
	class compare_map {
		bool operator()(std::shared_ptr<ObjCharacter> first, std::shared_ptr<ObjCharacter> second) {
			if (first->getPosition().y < second->getPosition().y) { 
				return true; }
			return false;
		}
	};
public:
	Map() : culTime(0.0f){}
	Map(const std::string &filepath);
	~Map();
	bool Update(const float dt);
	bool LoadFile(const std::string filepath);
	void LoadFile(std::ifstream& inFile);
	bool LoadFromSocket();
	float getCulTime() const { return culTime; }
private:
	float culTime;
	std::queue<std::shared_ptr<ObjEnemy>> objQueue;
};