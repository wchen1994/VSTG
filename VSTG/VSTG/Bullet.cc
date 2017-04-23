#include "Bullet.hpp"

Bullet::Bullet(float x, float y) :
	GameObject(),
	sprite()
{
	position.x = x;
	position.y = y;
	velocity.x = 0;
	velocity.y = -5;
	colliderSize = radius = 3;
	sprite.setRadius(radius);
	sprite.setPosition(x, y);
	sprite.setOrigin(radius, radius);
	drawing = &sprite;
}

void Bullet::Update(){
	if (position.y < 0){
		layerDelete.insert(this);
	} else {
		position += velocity;
	}
	sprite.setPosition(position);
}

void Bullet::OnCollisionEnter(GameObject *other){
	if (other->GetType() == "enemy"){
		layerDelete.insert(this);
	}
}
