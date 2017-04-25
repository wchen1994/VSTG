#include "Enemy.hpp"
#include "Game.hpp"
#include <cmath>

Enemy::Enemy(float x, float y=0) :
	GameObject()
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = speed;
	colliderSize = radius;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setPosition(position);
	pSprite->setOrigin(radius, radius);
	drawing = pSprite;
}

Enemy::Enemy(float x, float y, float vx, float vy) :
	GameObject()
{
	position.x = x;
	position.y = y;
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
	if (position.x < 0 || position.x > 800 || position.y > 600) {
		Game::layerDelete.insert(shared_from_this());
	}
}

void Enemy::FixedUpdate(const float & dt)
{
	position += velocity * dt;
	pSprite->setPosition(position);
}

void Enemy::OnCollisionEnter(std::shared_ptr<GameObject> other){
	std::string type = other->GetType();
	if (type == "bullet"){
		Game::layerDelete.insert(shared_from_this());
	}
}
