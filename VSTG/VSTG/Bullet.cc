#include "Bullet.hpp"
#include "Game.hpp"

Bullet::Bullet(float x, float y) :
	GameObject()
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = -300;
	colliderSize = radius = 3;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setPosition(x, y);
	pSprite->setOrigin(radius, radius);
	drawing = pSprite;
}

void Bullet::Update(const float& dt)
{
	if (position.y < 0) {
		Game::layerDelete.insert(shared_from_this());
	}
}

void Bullet::FixedUpdate(const float& dt)
{
	position += velocity * dt;

	pSprite->setPosition(position);
}

void Bullet::OnCollisionEnter(std::shared_ptr<GameObject> other){
	if (other->GetType() == "enemy"){
		Game::layerDelete.insert(shared_from_this());
	}
}
