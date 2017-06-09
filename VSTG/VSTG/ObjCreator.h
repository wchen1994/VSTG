#pragma once

#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include "Enemys/ObjEnemyBullet.h"
#include <memory>
#include <SFML/System.hpp>

namespace ObjCreator {
	enum EnemyType{ROCK_DOWN, ROCK_RAND, BROUND, BPOINTING,
		COUNT};
	template<class T>
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, ObjEnemyBullet::EBulletType type);

	std::shared_ptr<ObjEnemy> CreateEnemy(std::string ObjName, std::string texPath, sf::IntRect texRect, float size,
		sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	
	std::shared_ptr<ObjEnemy> CreateEnemy(std::string ObjName, std::string texPath, float size,
		sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	
	void ProcessEnemy(std::shared_ptr<ObjEnemy> pObject, std::string texPath);

	std::shared_ptr<GameObject> CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot=0.0f);
}