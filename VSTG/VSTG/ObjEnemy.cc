#include "ObjEnemy.hpp"
#include "ObjBullet.hpp"
#include "ObjPlayer.hpp"
#include "SceneGame.hpp"
#include <cmath>

ObjEnemy::ObjEnemy(float x, float y=0) :
	ObjEnemy(x, y, 0, speed)
{
}

ObjEnemy::ObjEnemy(float x, float y, float vx, float vy) :
	GameObject()
{
	position.x = x;
	position.y = y;
	brdPos.x = int(x / SceneGame::tileWidth);
	brdPos.y = int(y / SceneGame::tileHeight);
	if (vy <= 0)
		vy = 1;
	const float len = sqrt(vx*vx + vy*vy);
	velocity.x = vx * speed / len;
	velocity.y = vy * speed / len;
	colliderSize = radius;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setPosition(position);
	pSprite->setOrigin(radius, radius);
	drawing = pSprite;

	// Setup ID
	strcpy_s(objectID, "Enemy0");
	std::hash<std::string> hashGen;
	hashID = hashGen(objectID);
}

void ObjEnemy::Update(const float dt){
	if (position.x < Essential::GameCanvas.left-radius || 
		position.x > Essential::GameCanvas.left + Essential::GameCanvas.width + radius || 
		position.y > Essential::GameCanvas.top + Essential::GameCanvas.height + radius) {
		SceneGame::layerDelete.insert(shared_from_this());
	}
}

void ObjEnemy::FixedUpdate(const float dt)
{
	position += velocity * dt;

	brdPos = SceneGame::brd.UpdateObjectPos(shared_from_this());

	pSprite->setPosition(position);
}

void ObjEnemy::OnCollisionEnter(std::shared_ptr<GameObject> pOther){
	size_t hash = pOther->GetHash();
	if (hash == ObjBullet::hashID){
		SceneGame::layerDelete.insert(shared_from_this());
		SceneGame::layerDelete.insert(pOther);
	}
	else if (hash == ObjPlayer::hashID) {
		SceneGame::layerDelete.insert(pOther);
		Essential::isGameOver = true;
	}
}
