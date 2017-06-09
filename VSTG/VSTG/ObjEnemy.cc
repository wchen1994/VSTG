#include "ObjEnemy.hpp"
#include "ObjBullet.hpp"
#include "ObjPlayer.hpp"
#include "SceneGame.hpp"
#include <cmath>


ObjEnemy::ObjEnemy(float x, float y=0) :
	ObjEnemy(x, y, 0, 120.0f)
{
}

ObjEnemy::ObjEnemy(float x, float y, float vx, float vy) :
	GameObject(),
	speed(120.0f)
{
	position.x = x;
	position.y = y;
	brdPos.x = int(x / SceneGame::tileWidth);
	brdPos.y = int(y / SceneGame::tileHeight);

	const float len = sqrt(vx*vx + vy*vy);
	velocity.x = vx * speed / len;
	velocity.y = vy * speed / len;
//	colliderSize = radius;
	pCollider = std::make_shared<sf::CircleShape>(sf::CircleShape());
//	pCollider->setRadius(radius);
//	pCollider->setPosition(position);
//	pCollider->setOrigin(radius, radius);
	drawCollider = pCollider;

//	pTexture = Essential::assetManager.GetTexture("Resources/Textures/rock.png");
	drawSprite = std::make_shared<sf::Sprite>(sf::Sprite());
//	drawSprite->setTexture(*pTexture);
//	drawSprite->setOrigin(200.0f, 200.0f);
//	drawSprite->setScale(sf::Vector2f(0.1f, 0.1f));
//	drawSprite->setPosition(position);

//	std::uniform_real_distribution<float> aDist(0, 180);
//	std::uniform_real_distribution<float> wDist(-100, 100);
//	rotation = aDist(Essential::rng);
//	rotSpeed = wDist(Essential::rng);
	
	// Setup ID
	strcpy_s(classID, "Enemy");
	std::hash<std::string> hashGen;
	hashCID = hashGen("Enemy");
}

void ObjEnemy::Update(const float dt){
	if (isDelete) {
		SceneGame::layerDelete.insert(shared_from_this());
	} else if (position.x < Essential::GameCanvas.left-radius || 
		position.x > Essential::GameCanvas.left + Essential::GameCanvas.width + radius || 
		position.y > Essential::GameCanvas.top + Essential::GameCanvas.height + radius) {
		SceneGame::layerDelete.insert(shared_from_this());
	}
}

void ObjEnemy::FixedUpdate(const float dt)
{
	if (!isDelete) {
		position += velocity * dt;
		rotation += rotSpeed * dt;

		brdPos = SceneGame::brd.UpdateObjectPos(shared_from_this());

		pCollider->setPosition(position);
		drawSprite->setPosition(position);
		drawSprite->setRotation(rotation);
	}
}

void ObjEnemy::OnCollisionEnter(std::shared_ptr<GameObject> pOther){
	size_t hash = pOther->GetCID();
	if (hash == ObjBullet::hashCID){
//		SceneGame::layerDelete.insert(shared_from_this());
		SceneGame::layerDelete.insert(pOther);
		hp -= pOther->GetDamage();
		if (hp < 0) {
			isDelete = true;
		}
	}
	else if (hash == ObjPlayer::hashCID) {
//		SceneGame::layerDelete.insert(pOther);
//		Essential::isGameOver = true;
		pOther->OnCollisionEnter(shared_from_this());
	}
}

ObjEnemy* ObjEnemy::Clone() const
{
	ObjEnemy *pOther = new ObjEnemy(0.0f, 0.0f);
	*pOther = *this;
	*pOther->drawSprite = *this->drawSprite;
	*pOther->pCollider = *this->pCollider;
	pOther->drawCollider = pOther->pCollider;
	return pOther;
}
