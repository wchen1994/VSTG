#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y=0) :
	GameObject(),
	sprite()
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = 2;
	colliderSize = radius = 10;
	sprite.setRadius(radius);
	sprite.setPosition(position);
	sprite.setOrigin(radius, radius);
	drawing = &sprite;
}

Enemy::Enemy(float x, float y, float vx, float vy) :
	GameObject(),
	sprite()
{
	position.x = x;
	position.y = y;
	if (vy <= 0)
		vy = 1;
	float len = sqrt(vx*vx + vy*vy);
	velocity.x = vx * 2 / len;
	velocity.y = vy * 2 / len;
	colliderSize = radius = 10;
	sprite.setRadius(radius);
	sprite.setPosition(position);
	sprite.setOrigin(radius, radius);
	drawing = &sprite;
}

void Enemy::Update(){
	position += velocity;

	if (position.x < 0 || position.x > 800 || position.y > 600){
		GameObject::layerDelete.insert(this);	
	}

	sprite.setPosition(position);
}

void Enemy::OnCollisionEnter(GameObject *other){
	std::string type = other->GetType();
	if (type == "bullet"){
		GameObject::layerDelete.insert(this);
	}
}
