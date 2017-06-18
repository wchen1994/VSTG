#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "GameObject.hpp"
#include "ObjEnemy.hpp"

class Map {
public:
	struct compare_map {
		bool operator()(const std::shared_ptr<ObjCharacter> first, const std::shared_ptr<ObjCharacter> second) {
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
	void AddObjectByPacket(sf::Packet & packet_in, std::set<std::shared_ptr<ObjEnemy>, compare_map> & sorted_set_out);
	float getCulTime() const { return culTime; }
private:
	float culTime;
	std::queue<std::shared_ptr<ObjEnemy>> objQueue;
};