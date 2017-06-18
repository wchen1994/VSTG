#include "ObjCreator.h"

void ObjCreator::AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath)
{
	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	std::shared_ptr<sf::Sprite> sprite = pObject->GetSprite();
	if (!sprite) {
		sprite = std::make_shared<sf::Sprite>(sf::Sprite());
		sf::Vector2u texSize = pTexture->getSize();
		sprite->setTexture(*pTexture);
		sprite->setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
		float scale = 2 * pObject->GetColliderSize() / ((texSize.x + texSize.y) / 2.0f);
		sprite->setScale(sf::Vector2f(scale, scale));
		pObject->SetTexturePtr(pTexture);
		pObject->SetSprite(sprite);
	}
	else {
		sf::Vector2u texSize = pTexture->getSize();
		sprite->setTexture(*pTexture);
		sprite->setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
		float scale = 2 * pObject->GetColliderSize() / ((texSize.x + texSize.y) / 2.0f);
		sprite->setScale(sf::Vector2f(scale, scale));
		pObject->SetTexturePtr(pTexture);
	}
}

void ObjCreator::AssignTexture(std::shared_ptr<ObjCharacter> pObject, std::string texPath, sf::IntRect texRect)
{
	std::shared_ptr<sf::Texture> pTexture = Essential::assetManager.GetTexture(texPath);
	std::shared_ptr<sf::Sprite> sprite = pObject->GetSprite();
	if (!sprite) {
		sprite = std::make_shared<sf::Sprite>(sf::Sprite());
		sprite->setTexture(*pTexture);
		sprite->setTextureRect(texRect);
		sprite->setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
		float scale = 2 * pObject->GetColliderSize() / ((texRect.width + texRect.height) / 2.0f);
		sprite->setScale(sf::Vector2f(scale, scale));
		pObject->SetSprite(sprite);
	}
	else {
		sprite->setTexture(*pTexture);
		sprite->setTextureRect(texRect);
		sprite->setOrigin(texRect.width / 2.0f, texRect.height / 2.0f);
		float scale = 2 * pObject->GetColliderSize() / ((texRect.width + texRect.height) / 2.0f);
		sprite->setScale(sf::Vector2f(scale, scale));
	}
}

void ObjCreator::SendPacket(std::shared_ptr<ObjCharacter> pObject)
{
	assert(Essential::isHost);
	assert(!Essential::isClient);
	sf::Packet packet;
	packet << int(Essential::PacketType::ADD);
	pObject->ProcessPacket(packet);
	Essential::socket.SendPacket(packet);
}

std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	std::shared_ptr<ObjEnemy> pObj = std::make_shared<ObjEnemy>(ObjEnemy(pos, vel, rot, rotSpeed));
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

std::shared_ptr<ObjEnemy> ObjCreator::_CreateEnemy2(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, EnemyBulletType bullet)
{
	std::shared_ptr<EnemyDuck> pObj = std::make_shared<EnemyDuck>(EnemyDuck(pos, vel, bullet));
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
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
			sf::Vector2f(60.0f * (Essential::normalizedDist(Essential::rng) - 0.5f), 60.0f + 60.0f * Essential::normalizedDist(Essential::rng)),
			Essential::angleDist(Essential::rng), Essential::angleDist(Essential::rng));
		AssignTexture(pObject, "Resources/Textures/rock1.png");
		pObject->SetOID(EnemyType::ROCK_RAND);
		break;
	case EnemyType::DUCK_RED:
		pObject = _CreateEnemy2("Duck Red t 1", 30.0f, pos,
			sf::Vector2f(0.0f, 30.0f), EnemyBulletType::BROUND);
		AssignTexture(pObject, "Resources/Textures/Enemy02.png");
		pObject->SetHp(800.0f);
		pObject->SetOID(EnemyType::DUCK_RED);
		break;
	case EnemyType::DUCK_BLUE:
		pObject = _CreateEnemy2("Duck Blue t 1", 30.0f, pos,
			sf::Vector2f(60.0f * (Essential::normalizedDist(Essential::rng) - 0.5f), 30.0f), EnemyBulletType::BPOINTING);
		AssignTexture(pObject, "Resources/Textures/Enemy03.png");
		pObject->SetHp(500.0f);
		pObject->SetOID(EnemyType::DUCK_BLUE);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}

// For Online version
std::shared_ptr<ObjEnemy> ObjCreator::CreateEnemyX(EnemyType type, sf::Vector2f pos, sf::Vector2f vel, float rot, float rotSpeed)
{
	assert(Essential::isClient);

	std::shared_ptr<ObjEnemy> pObject = nullptr;
	switch (type) {
	case EnemyType::ROCK_DOWN:
		pObject = _CreateEnemy("Stupid Rock", 20.0f, pos, vel, rot, rotSpeed);
		AssignTexture(pObject, "Resources/Textures/rock0.png");
		pObject->SetOID(EnemyType::ROCK_DOWN);
		break;
	case EnemyType::ROCK_RAND:
		pObject = _CreateEnemy("Insane Rock", 20.0f, pos, vel, rot, rotSpeed);
		AssignTexture(pObject, "Resources/Textures/rock1.png");
		pObject->SetOID(EnemyType::ROCK_RAND);
		break;
	case EnemyType::DUCK_RED:
		pObject = _CreateEnemy2("Duck Red t 1", 30.0f, pos, vel, EnemyBulletType::BROUND);
		AssignTexture(pObject, "Resources/Textures/Enemy02.png");
		pObject->SetHp(800.0f);
		pObject->SetOID(EnemyType::DUCK_RED);
		break;
	case EnemyType::DUCK_BLUE:
		pObject = _CreateEnemy2("Duck Blue t 1", 30.0f, pos, vel, EnemyBulletType::BPOINTING);
		AssignTexture(pObject, "Resources/Textures/Enemy03.png");
		pObject->SetHp(500.0f);
		pObject->SetOID(EnemyType::DUCK_BLUE);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}

std::shared_ptr<ObjEnemyBullet> ObjCreator::_CreateEnemyBullet(std::string ObjName, float radius, sf::Vector2f pos, sf::Vector2f vel, float rot)
{
	std::shared_ptr<ObjEnemyBullet> pObj = std::make_shared<ObjEnemyBullet>(ObjEnemyBullet(pos, vel));
	pObj->SetRotation(rot);
	pObj->SetColliderSize(0.8f * radius);
	pObj->SetName(ObjName);
	return pObj;
}

std::shared_ptr<ObjEnemyBullet> ObjCreator::CreateEnemyBullet(EnemyBulletType type, sf::Vector2f pos, sf::Vector2f vel)
{
	std::shared_ptr<ObjEnemyBullet> pObject = nullptr;
	float rot = 0.0f;
	switch (type) {
	case EnemyBulletType::BROUND:
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, 0.0f);
		AssignTexture(pObject, "Resources/Textures/Bullet00.png");
		pObject->SetOID(EnemyBulletType::BROUND);
		pObject->SetDamage(40.0f);
		pObject->SetSpeed(100.0f);
		break;
	case EnemyBulletType::BPOINTING:
		if (vel.y != 0.0f)
			rot = float(180 - atan(vel.x / vel.y) * 180 / std::_Pi);
		else if (vel.x > 0) {
			rot = 90.0f;
		}
		else {
			rot = 270.0f;
		}
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, rot);
		AssignTexture(pObject, "Resources/Textures/Bullet01.png");
		pObject->SetOID(EnemyBulletType::BPOINTING);
		pObject->SetDamage(60.0f);
		pObject->SetSpeed(200.0f);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}

std::shared_ptr<ObjEnemyBullet> ObjCreator::CreateEnemyBullet(EnemyBulletType type, sf::Vector2f pos, float speed, float rot)
{
	std::shared_ptr<ObjEnemyBullet> pObject = nullptr;
	sf::Vector2f vel = { float(sin(rot * std::_Pi / 180.0f)), float(-cos(rot * std::_Pi / 180.0f)) };
	vel *= speed;
	switch (type) {
	case EnemyBulletType::BROUND:
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, 0.0f);
		AssignTexture(pObject, "Resources/Textures/Bullet00.png");
		pObject->SetOID(EnemyBulletType::BROUND);
		pObject->SetDamage(40.0f);
		break;
	case EnemyBulletType::BPOINTING:
		pObject = _CreateEnemyBullet("Bullet Round", 12.0f, pos, vel, rot);
		AssignTexture(pObject, "Resources/Textures/Bullet01.png");
		pObject->SetOID(EnemyBulletType::BPOINTING);
		pObject->SetDamage(60.0f);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}

std::shared_ptr<ObjPlayer> ObjCreator::_CreatePlayer(std::string ObjName, float radius, sf::Vector2f pos)
{
	std::shared_ptr<ObjPlayer> pObject = std::make_shared<ObjPlayer>(ObjPlayer(pos));
	pObject->SetColliderSize(radius);
	return pObject;
}

std::shared_ptr<ObjPlayer> ObjCreator::CreatePlayer(PlayerType type, sf::Vector2f pos)
{
	std::shared_ptr<ObjPlayer> pObject = nullptr;
	switch (type) {
	case PlayerType::HULUWA:
		pObject = _CreatePlayer("HuLuWa", 20.0f, pos);
		AssignTexture(pObject, "Resources/Textures/Player00.png");
		pObject->SetColliderSize(5.0f);
		pObject->SetOID(PlayerType::HULUWA);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}

std::shared_ptr<ObjBullet> ObjCreator::_CreateBullet(std::string Objname, float radius, sf::Vector2f pos, float speed, float rot)
{
	sf::Vector2f vel = { float(sin(rot * std::_Pi / 180.0f)), float(-cos(rot * std::_Pi / 180.0f)) };
	vel *= speed;
	std::shared_ptr<ObjBullet> pObject = std::make_shared<ObjBullet>(ObjBullet(pos, vel));
	pObject->SetColliderSize(radius);
	return pObject;
}

std::shared_ptr<ObjBullet> ObjCreator::CreateBullet(BulletType type, sf::Vector2f pos, float rot)
{
	std::shared_ptr<ObjBullet> pObject = nullptr;
	switch (type) {
	case BulletType::BLUE:
		pObject = _CreateBullet("Bullet Blue", 6.0f, pos, 500.0f, rot);
		AssignTexture(pObject, "Resources/Textures/BulletPlayer.png", sf::IntRect(150, 0, 100, 400));
		pObject->SetRotation(rot);
		pObject->SetOID(BulletType::BLUE);
		break;
	case BulletType::GREEN:
		pObject = _CreateBullet("Bullet Blue", 6.0f, pos, 500.0f, rot);
		AssignTexture(pObject, "Resources/Textures/BulletPlayer02.png", sf::IntRect(150, 0, 100, 400));
		pObject->SetRotation(rot);
		break;
	default:
		pObject = nullptr;
	}

	if (Essential::isHost) {
		SendPacket(pObject);
	}

	return pObject;
}
