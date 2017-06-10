#include "ObjCreator.h"

std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = std::make_shared<ObjEnemy>(ObjEnemy(pos, vel, rot, rotSpeed));
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

void ObjCreator::AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath)
{
	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	sf::Sprite& sprite = pObject->GetSprite();
	sf::Vector2u texSize = pTexture->getSize();
	sprite.setTexture(*pTexture);
	sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	float scale = 2 * pObject->GetColliderSize() / ((texSize.x + texSize.y) / 2.0f);
	sprite.setScale(sf::Vector2f(scale, scale));

}

void ObjCreator::AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath, sf::IntRect texRect)
{
	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	sf::Sprite& sprite = pObject->GetSprite();
	sprite.setTexture(*pTexture);
	sprite.setTextureRect(texRect);
	sprite.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
	float scale = 2 * pObject->GetColliderSize() / ((texRect.width + texRect.height) / 2.0f);
	sprite.setScale(sf::Vector2f(scale, scale));
}

std::shared_ptr<ObjEnemy> ObjCreator::CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel, float rot)
{
	std::shared_ptr<ObjEnemy> pObject = nullptr;
	switch (type) {
	case EnemyType::ROCK_DOWN:
		 pObject = _CreateEnemy("Stupid Rock", 20.0f, pos, sf::Vector2f(0.0f, 120.0f), 
			 Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		 AssignTexture(pObject, "Resources/Textures/rock0.png");
		pObject->SetOID(EnemyType::ROCK_DOWN);
		break;
	case EnemyType::ROCK_RAND:
		pObject = _CreateEnemy("Insane Rock", 20.0f, pos, 
			sf::Vector2f(120.0f * (Essential::normalizedDist(Essential::rng) - 60.0f), 120.0f * Essential::normalizedDist(Essential::rng)),
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		AssignTexture(pObject, "Resources/Textures/rock1.png");
		pObject->SetOID(EnemyType::ROCK_RAND);
		break;
	default:
		pObject = nullptr;
	}
	return pObject;
}

std::shared_ptr<ObjEnemyBullet> ObjCreator::_CreateEnemyBullet(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, ObjEnemyBullet::EBulletType type)
{
	std::shared_ptr<ObjEnemyBullet> pObj = std::make_shared<ObjEnemyBullet>(ObjEnemyBullet(pos, vel, type));
	pObj->SetRotation(rot);
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

std::shared_ptr<ObjEnemyBullet> ObjCreator::CreateEnemyBullet(EnemyType type, sf::Vector2f pos, sf::Vector2f vel, float rot)
{
	std::shared_ptr<ObjEnemyBullet> pObject = nullptr;
	switch (type) {
	case EnemyBulletType::BROUND:
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, 0.0f, ObjEnemyBullet::ROUND);
		AssignTexture(pObject, "Resources/Textures/Bullet00.png");
		pObject->SetOID(EnemyBulletType::BROUND);
		pObject->SetDamage(40.0f);
		break;
	case EnemyBulletType::BPOINTING:
		if (vel.y != 0.0f)
			rot = (float)180 - atan(vel.x / vel.y) * 180 / std::_Pi;
		else if (vel.x > 0) {
			rot = 90.0f;
		}
		else {
			rot = 270.0f;
		}
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, rot, ObjEnemyBullet::POINTING);
		AssignTexture(pObject, "Resources/Textures/Bullet01.png");
		pObject->SetOID(EnemyBulletType::BPOINTING);
		pObject->SetDamage(60.0f);
		break;
	default:
		pObject = nullptr;
	}
	return pObject;
}
