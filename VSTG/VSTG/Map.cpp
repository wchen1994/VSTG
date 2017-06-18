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

	if (Essential::isHost) {
		sf::Packet packet_out;
		packet_out << int(Essential::PacketType::SIGNAL_SIZE) << int(objQueue.size());
		Essential::socket.SendPacket(packet_out);


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
				AddObjectByPacket(packet, sorted_set);
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

		if (map_size == sorted_set.size()) {
			break;
		}
		else if (map_size == -1) {
			// Continue loop Wait for the SIZE Signal
		}
		else {
			// Size is not match
			// Resynch the map
			assert(false);
		}
	}

	for (auto & pObject : sorted_set) {
		objQueue.push(pObject);
	}
	sorted_set.clear();

//	//Signal for ready to start and wait for the signal from server
//	sf::Packet packet_out;
//	packet_out << int(Essential::PacketType::SIGNAL);
//	Essential::socket.SendPacket(packet_out);
//	while (true) {
//		auto & vPackets = Essential::socket.GetPacket();
//		while (!vPackets.empty()) {
//			sf::Packet & packet_in = vPackets.front();
//			int type;
//			packet_in >> type;
//			if (type == int(Essential::PacketType::SIGNAL))
//				break;
//			else
//				assert(false);
//			vPackets.pop();
//		}
//	}

	culTime = 0;
	return true;
}

void Map::AddObjectByPacket(sf::Packet & packet_in, std::set<std::shared_ptr<ObjEnemy>, compare_map> & sorted_set_out)
{
	int type;
	unsigned int unique_id;
	uint32_t OID;
	sf::Vector2f pos;
	sf::Vector2f vel;
	float rotation;
	float rotSpeed;
	packet_in >> type >> OID >> unique_id >> pos.x >> pos.y >> vel.x >> vel.y >> rotation >> rotSpeed;
	
	// Packet can have enemy and player
	if (type == GameObject::ENEMY) {
		sorted_set_out.insert(ObjCreator::CreateEnemy(ObjCreator::EnemyType(OID), pos, vel, rotation));
	}
	else if (type == GameObject::PLAYER) {
		SceneGame::layerPlayer.push_back(ObjCreator::CreatePlayer(ObjCreator::PlayerType(OID), pos));
	}
	else {
		assert(false);
	}
}
