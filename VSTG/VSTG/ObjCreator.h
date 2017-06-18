#pragma once

#include "ObjEnemy.hpp"
#include "Enemys/EnemyDuck.h"
#include "Essential.hpp"
#include "ObjEnemyBullet.h"
#include <memory>
#include <SFML/System.hpp>

namespace ObjCreator {
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath);
	void AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath, sf::IntRect texRect);

	void SendPacket(std::shared_ptr<ObjCharacter> pObject);

	enum EnemyBulletType : uint32_t { BROUND, BPOINTING };
	std::shared_ptr<ObjEnemyBullet> _CreateEnemyBullet(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot);
	std::shared_ptr<ObjEnemyBullet> CreateEnemyBullet(EnemyBulletType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f });
	std::shared_ptr<ObjEnemyBullet> CreateEnemyBullet(EnemyBulletType type, sf::Vector2f pos, float speed, float rot);

	enum EnemyType : uint32_t {ROCK_DOWN, ROCK_RAND, DUCK_RED, DUCK_BLUE, COUNT};
	std::shared_ptr<ObjEnemy> _CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);
	std::shared_ptr<ObjEnemy> _CreateEnemy2(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, EnemyBulletType bullet);
	std::shared_ptr<ObjEnemy> CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel = { 0.0f,1.0f }, float rot=0.0f);
	std::shared_ptr<ObjEnemy> CreateEnemyX(EnemyType type, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed);

	enum PlayerType : uint32_t {HULUWA};
	std::shared_ptr<ObjPlayer> _CreatePlayer(std::string ObjName, float radius, sf::Vector2f pos);
	std::shared_ptr<ObjPlayer> CreatePlayer(PlayerType type, sf::Vector2f pos);

	enum BulletType : uint32_t {BLUE, GREEN};
	std::shared_ptr<ObjBullet> _CreateBullet(std::string Objname, float radius, sf::Vector2f pos, float speed, float rot);
	std::shared_ptr<ObjBullet> CreateBullet(BulletType type, sf::Vector2f pos, float rot);
}