#pragma once

#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include "ObjEnemyBullet.h"
#include <memory>
#include <SFML/System.hpp>

namespace ObjCreator {
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath);
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath, sf::IntRect texRect);

	enum EnemyType{ROCK_DOWN, ROCK_RAND, COUNT};
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<ObjEnemy> CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot=0.0f);


	enum EnemyBulletType{ BROUND, BPOINTING, BCOUNT};
	std::shared_ptr<ObjEnemyBullet> _CreateEnemyBullet(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, ObjEnemyBullet::EBulletType type);
	std::shared_ptr<ObjEnemyBullet> CreateEnemyBullet(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot = 0.0f);

}