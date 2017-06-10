#pragma once

#include "ObjEnemy.hpp"
#include "Essential.hpp"
#include "ObjEnemyBullet.h"
#include <memory>
#include <SFML/System.hpp>

namespace ObjCreator {
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath);
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath, sf::IntRect texRect);

	enum EnemyType{ROCK_DOWN, ROCK_RAND, DUCK_RED, DUCK_BLUE, COUNT};
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<ObjEnemy> CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot=0.0f);

	enum EnemyBulletType{ BROUND, BPOINTING};
	std::shared_ptr<ObjEnemyBullet> _CreateEnemyBullet(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, ObjEnemyBullet::EBulletType type);
	std::shared_ptr<ObjEnemyBullet> CreateEnemyBullet(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot = 0.0f);

	enum PlayerType{HULUWA};
	std::shared_ptr<ObjPlayer> _CreatePlayer(std::string ObjName, float radius, sf::Vector2f pos);
	std::shared_ptr<ObjPlayer> CreatePlayer(PlayerType type, sf::Vector2f pos);

	enum BulletType{BLUE, GREEN};
	std::shared_ptr<ObjBullet> _CreateBullet(std::string Objname, float radius, sf::Vector2f pos, float speed, float rot);
	std::shared_ptr<ObjBullet> CreateBullet(BulletType type, sf::Vector2f pos, float rot);
}