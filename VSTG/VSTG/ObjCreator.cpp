#include "ObjCreator.h"

std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy(float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = std::make_shared<ObjEnemy>(ObjEnemy(pos.x, pos.y, vel.x, vel.y));
	pObj->SetRotation(rot);
	pObj->SetRotationSpeed(rotSpeed);
	pObj->SetColliderSize(0.8f * radius);
	return pObj;
}

std::shared_ptr<GameObject> ObjCreator::CreateEnemy(std::string texPath, sf::IntRect texRect,
	float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = _CreateEnemy(radius, pos, vel, rot, rotSpeed);
	
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

std::shared_ptr<GameObject> ObjCreator::CreateEnemy(std::string texPath, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = _CreateEnemy(radius, pos, vel, rot, rotSpeed);
	
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

std::shared_ptr<GameObject> ObjCreator::CreateEnemy(EnemyType type, sf::Vector2f pos)
{
	switch (type) {
	case EnemyType::ROCK_DOWN:
		return CreateEnemy("Resources/Textures/rock.png", 20, pos, sf::Vector2f(0.0f, 120.0f), 
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		break;
	case EnemyType::ROCK_RAND:
		return CreateEnemy("Resources/Textures/rock.png", 20, pos, 
			sf::Vector2f(Essential::normalizedDist(Essential::rng) - 0.5f, Essential::normalizedDist(Essential::rng)),
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		break;
	default:
		return nullptr;
	}
	return nullptr;
}
