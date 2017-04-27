#include "Enemy.hpp"
#include "Game.hpp"
#include <cmath>

Enemy::Enemy(float x, float y=0) :
	GameObject()
{
	Enemy(x, y, 0, speed);
}

Enemy::Enemy(float x, float y, float vx, float vy) :
	GameObject()
{
	position.x = x;
	position.y = y;
	brdPos.x = int(x / Game::tileWidth);
	brdPos.y = int(y / Game::tileHeight);
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
}

void Enemy::Update(const float& dt){
	if (position.x < -radius || position.x > 800 + radius || position.y > 600) {
		Game::layerDelete.insert(shared_from_this());
	}
}

void Enemy::FixedUpdate(const float & dt)
{
	position += velocity * dt;
	const sf::Vector2i newBrdPos(int(position.x / Game::tileWidth), int(position.y / Game::tileHeight));
	if (brdPos.x != newBrdPos.x || brdPos.y != newBrdPos.y) {
		Game::brd.RemoveObject(brdPos, shared_from_this());
		Game::brd.AddObject(newBrdPos, shared_from_this());
	}
	brdPos = newBrdPos;

	pSprite->setPosition(position);
}

void Enemy::OnCollisionEnter(std::shared_ptr<GameObject> other){
	std::string type = other->GetType();
	if (type == "bullet"){
		Game::layerDelete.insert(shared_from_this());
		Game::layerDelete.insert(other);
	}
	else if (type == "player") {
		Game::layerDelete.insert(other);
		Essential::isGameOver = true;
	}
}
