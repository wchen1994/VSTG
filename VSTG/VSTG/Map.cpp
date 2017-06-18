#include "Map.h"
#include "SceneGame.hpp"
#include "ObjCreator.h"

#include <regex>

Map::Map(const std::string & filepath) : Map()
{
	LoadFile(filepath);
}

Map::~Map()
{
	while (!objQueue.empty()) {
		objQueue.pop();
	}
}

bool Map::Update(const float dt)
{
	culTime += dt;
	if (!objQueue.empty()) {
		sf::Vector2f vec = objQueue.front()->getPosition();
		if (culTime > vec.y) {
			std::shared_ptr<ObjEnemy> pObject = objQueue.front();
			objQueue.pop();
			vec.y = float(Essential::GameCanvas.top) - 10.0f;
			pObject->setPosition(vec);
			SceneGame::layerDefault.insert(pObject);
			SceneGame::layerEnemy.insert(pObject);
		}
		return true;
	}
	else {
		return false;
	}
}

bool Map::LoadFile(const std::string filepath)
{
	std::ifstream file;
	try {
		file.open(filepath, std::ifstream::in);
		if (!file.good())
			throw std::ferror;
		LoadFile(file);
	}
	catch (...) {
		file.close();
		return false;
	}
	file.close();
	return true;
}

void Map::LoadFile(std::ifstream & inFile)
{
	std::string line;
	std::regex rgx("(\\d*\\.\\d*),\\s*(-?\\d*\\.\\d*),\\s*(\\d*)");
	std::smatch match;
	while (std::getline(inFile, line)) {
		const std::string s(line);
		if (std::regex_search(s.begin(), s.end(), match, rgx)) {
			sf::Vector2f vec = { std::stof(match[1]), std::stof(match[2]) };
			ObjCreator::EnemyType OID = ObjCreator::EnemyType(std::stoul(match[3]));
			vec.x += float(Essential::GameCanvas.left);
			assert(OID < ObjCreator::EnemyType::COUNT);
			objQueue.push(ObjCreator::CreateEnemy(OID, sf::Vector2f(vec.x, vec.y)));
		}
	}
	culTime = 0;
}

bool Map::LoadFromSocket()
{
	assert(!Essential::isHost);
	assert(Essential::isClient);
	std::set<std::shared_ptr<ObjEnemy>, compare_map> sorted_set;
	int map_size = -1;
	while (true) {
		auto & qPackets = Essential::socket.GetPacket();
		bool isBreak = false;
		while (!qPackets.empty()) {
			sf::Packet & packet = qPackets.front();
			int packetType;
			packet >> packetType;
			if (packetType == int(Essential::PacketType::ADD)) {

			}
			else if (packetType == int(Essential::PacketType::SIGNAL)) {
				isBreak = true;
			}
			else if (packetType == int(Essential::PacketType::SIGNAL_SIZE)) {
				packet >> map_size;
			}
			else {
				assert(false);
				return false;
			}
			qPackets.pop();
		}

		if (isBreak && map_size == sorted_set.size()){
			break;
		}
		else {
			assert(false);
			return false;
		}
	}

	for (auto & pObject : sorted_set) {
		objQueue.push(pObject);
	}
	sorted_set.clear();
	culTime = 0;
	return true;
}

void Map::AddObjectByPacket(sf::Packet & packet_in, std::set<std::shared_ptr<ObjEnemy>, compare_map> & sorted_set_out)
{
	int type;
	packet_in >> type;
	
	// Packet can have enemy and player
	if (type == GameObject::ENEMY) {

	}
	else if (type == GameObject::PLAYER) {
		
	}
	else {
		assert(false);
	}
}
