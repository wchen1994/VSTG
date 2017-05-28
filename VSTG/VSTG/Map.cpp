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

void Map::Update(const float dt)
{
	culTime += dt;
	if (!objQueue.empty()) {
		sf::Vector2f vec = objQueue.front()->getPosition();
		if (culTime > vec.y) {
			std::shared_ptr<GameObject> pObject = objQueue.front();
			objQueue.pop();
			vec.y = float(Essential::GameCanvas.top) - 10.0f;
			pObject->setPosition(vec);
			SceneGame::layerDefault.insert(pObject);
			SceneGame::brd.AddObject(pObject);
		}
	}
}

void Map::LoadFile(const std::string filepath)
{
	try {
		std::ifstream file;
		file.open(filepath);
		std::string line;
		std::regex rgx("(\\d*\\.\\d*),\\s*(-?\\d*\\.\\d*),\\s*(\\d*)");
		std::smatch match;
		while (std::getline(file, line)) {
			const std::string s(line);
			if (std::regex_search(s.begin(), s.end(), match, rgx)) {
				sf::Vector2f vec = { std::stof(match[1]), std::stof(match[2]) };
				ObjCreator::EnemyType OID = ObjCreator::EnemyType(std::stoul(match[3]));
				vec.x += float(Essential::GameCanvas.left);
				assert(OID < ObjCreator::EnemyType::COUNT);
				objQueue.push(ObjCreator::CreateEnemy(OID, sf::Vector2f(vec.x, vec.y)));
//				objQueue.push(std::make_shared<ObjEnemy>(ObjEnemy(vec.x, vec.y)));
			}
		}
		file.close();
	}
	catch (...) {
		assert(false);
	}
}
