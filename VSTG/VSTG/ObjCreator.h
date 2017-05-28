#pragma once

#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include <memory>
#include <SFML/System.hpp>

namespace ObjCreator {
	enum EnemyType{ROCK_DOWN, ROCK_RAND,
		COUNT};
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float size, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<GameObject> CreateEnemy(std::string ObjName, std::string texPath, sf::IntRect texRect, float size,
		sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<GameObject> CreateEnemy(std::string ObjName, std::string texPath, float size,
		sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<GameObject> CreateEnemy(EnemyType type, sf::Vector2f pos);
}