#include "EnemyDuck.h"

#include "../SceneGame.hpp"

EnemyDuck::EnemyDuck(sf::Vector2f pos, sf::Vector2f vel, ObjCreator::EnemyBulletType bullet) :
	ObjEnemy(pos, vel, 0.0f, 0.0f),
	timer(0.0f),
	bullet(bullet)
{
}

void EnemyDuck::Update(const float dt)
{
	if (isDelete) {
		SceneGame::layerDelete.insert(shared_from_derived<ObjEnemy>());
	}
	else if (position.x < Essential::GameCanvas.left - colliderSize ||
		position.x > Essential::GameCanvas.left + Essential::GameCanvas.width + colliderSize ||
		position.y > Essential::GameCanvas.top + Essential::GameCanvas.height + colliderSize) {
		SceneGame::layerDelete.insert(shared_from_derived<ObjEnemy>());
	}
	else {
		if (timer > coolDown) {
			if (bullet == ObjCreator::EnemyBulletType::BROUND) {
				std::shared_ptr<ObjEnemyBullet> pBullet1;
				std::shared_ptr<ObjEnemyBullet> pBullet2;
				std::shared_ptr<ObjEnemyBullet> pBullet3;
				pBullet1 = ObjCreator::CreateEnemyBullet(ObjCreator::EnemyBulletType::BROUND, position, 180.0f);
				pBullet2 = ObjCreator::CreateEnemyBullet(ObjCreator::EnemyBulletType::BROUND, position, 150.0f);
				pBullet3 = ObjCreator::CreateEnemyBullet(ObjCreator::EnemyBulletType::BROUND, position, 210.0f);
				SceneGame::layerDefault.insert(pBullet1);
				SceneGame::layerDefault.insert(pBullet2);
				SceneGame::layerDefault.insert(pBullet3);
			}
			else {
				std::shared_ptr<ObjEnemyBullet> pBullet;
				for (int i = 0; i < Essential::totalNumbPlayer; i++) {
					if (SceneGame::layerPlayer[i] != NULL) {
						const sf::Vector2f playerPos = SceneGame::layerPlayer[i]->getPosition();
						const sf::Vector2f diffPos = playerPos - position;
						pBullet = ObjCreator::CreateEnemyBullet(ObjCreator::EnemyBulletType::BPOINTING, position, diffPos);
						SceneGame::layerDefault.insert(pBullet);
					}
				}
			}
			timer -= coolDown;
		}
		timer += dt;
	}
}
