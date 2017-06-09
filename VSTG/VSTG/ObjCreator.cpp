#include "ObjCreator.h"

template<class T>
std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = std::make_shared<T>(T(pos.x, pos.y, vel.x, vel.y));
	pObj->SetRotation(rot);
	pObj->SetRotationSpeed(rotSpeed);
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, ObjEnemyBullet::EBulletType type)
{
	std::shared_ptr<ObjEnemy> pObj = std::make_shared<ObjEnemyBullet>(ObjEnemyBullet(pos.x, pos.y, vel.x, vel.y,
		type));
	pObj->SetRotation(rot);
	pObj->SetRotationSpeed(0.0f);
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

std::shared_ptr<ObjEnemy> ObjCreator::CreateEnemy(std::string ObjName, std::string texPath, sf::IntRect texRect,
	float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = _CreateEnemy<ObjEnemy>(ObjName, radius, pos, vel, rot, rotSpeed);

	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	pObj->SetTexturePtr(pTexture);
	sf::Sprite& sprite = pObj->GetSprite();
	sprite.setTexture(*pTexture);
	sprite.setTextureRect(texRect);
	sprite.setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
	float scale = 2 * radius / ((texRect.width + texRect.height) / 2.0f);
	sprite.setScale(sf::Vector2f(scale, scale));
	
	return pObj;
}

std::shared_ptr<ObjEnemy> ObjCreator::CreateEnemy(std::string ObjName, std::string texPath, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = _CreateEnemy<ObjEnemy>(ObjName, radius, pos, vel, rot, rotSpeed);

	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	pObj->SetTexturePtr(pTexture);
	sf::Sprite& sprite = pObj->GetSprite();
	sf::Vector2u texSize = pTexture->getSize();
	sprite.setTexture(*pTexture);
	sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	float scale = 2 * radius / ((texSize.x + texSize.y) / 2.0f);
	sprite.setScale(sf::Vector2f(scale, scale));
	
	return pObj;
}

void ObjCreator::ProcessEnemy(std::shared_ptr<ObjEnemy> pObject, std::string texPath)
{
	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	pObject->SetTexturePtr(pTexture);
	sf::Sprite& sprite = pObject->GetSprite();
	sf::Vector2u texSize = pTexture->getSize();
	sprite.setTexture(*pTexture);
	sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
	float scale = 2 * pObject->GetColliderSize() / ((texSize.x + texSize.y) / 2.0f);
	sprite.setScale(sf::Vector2f(scale, scale));

}

std::shared_ptr<GameObject> ObjCreator::CreateEnemy(EnemyType type, sf::Vector2f pos, sf::Vector2f vel, float rot)
{
	std::shared_ptr<ObjEnemy> pObject = nullptr;
	switch (type) {
	case EnemyType::ROCK_DOWN:
		 pObject = CreateEnemy("Stupid Rock", "Resources/Textures/rock0.png",
			20, pos, sf::Vector2f(0.0f, 120.0f),
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		pObject->SetOID(EnemyType::ROCK_DOWN);
		break;
	case EnemyType::ROCK_RAND:
		pObject = CreateEnemy("Insane Rock", "Resources/Textures/rock1.png", 20, pos,
			sf::Vector2f(0.5f * (Essential::normalizedDist(Essential::rng) - 0.5f), Essential::normalizedDist(Essential::rng)),
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		pObject->SetOID(EnemyType::ROCK_RAND);
		break;
	case EnemyType::BROUND:
		pObject = _CreateEnemy("Bullet Round", 8.0f, pos, vel, 0.0f, ObjEnemyBullet::ROUND);
		ProcessEnemy(pObject, "Resources/Textures/Bullet00.png");
		pObject->SetOID(EnemyType::BROUND);
		break;
	case EnemyType::BPOINTING:
		pObject = _CreateEnemy("Bullet Round", 8.0f, pos, vel, rot, ObjEnemyBullet::POINTING);
		ProcessEnemy(pObject, "Resources/Textures/Bullet01.png");
		pObject->SetOID(EnemyType::BPOINTING);
		break;
	default:
		pObject = nullptr;
	}
	return pObject;
}
