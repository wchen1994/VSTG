#include "Player.hpp"
#include "Bullet.hpp"
#include "Essential.hpp"

Player::Player(sf::RenderWindow *wnd) :
	GameObject(wnd),
	sprite()
{
	this->wnd = wnd;
	up = down = left = right = false;
	fire = false; radius = 5;
	position.x = 400;
	position.y = 300;
	velocity.x = 0;
	velocity.y = 0;
	speed = 3;
	cooldown = 0;
	originX = originY = radius;
	sprite.setRadius(radius);
	sprite.setOrigin(originX, originY);
	sprite.setPosition(position);
	drawing = &sprite;
}

void Player::Update(){
	velocity.x = 0;
	velocity.y = 0;
	if (up)
		velocity.y -= 100;
	if (down)
		velocity.y += 100;
	if (left)
		velocity.x -= 100;
	if (right)
		velocity.x += 100;

	if (cooldown > 0){
		cooldown--;
	}else if (fire){
		layerDefault.insert(new Bullet(wnd, position.x, position.y));
		cooldown = 10;
	}
	float sqlen = velocity.x*velocity.x + velocity.y*velocity.y;
	
	if (sqlen != 0){
		sqlen = sqrt(sqlen);
		position += velocity/sqlen * speed;
		if (position.x < 0)
			position.x = 0;
		if (position.x > 800)
			position.x = 800;
		if (position.y < 0)
			position.y = 0;
		if (position.y > 600)
			position.y = 600;
	}

	sprite.setPosition(position);
}

void Player::OnKeyPressed(sf::Event::KeyEvent key){
	sf::Keyboard::Key keycode = key.code;
	switch (keycode){
		case sf::Keyboard::Up:
			up = true;
			break;
		case sf::Keyboard::Down:
			down = true;
			break;
		case sf::Keyboard::Left:
			left = true;
			break;
		case sf::Keyboard::Right:
			right = true;
			break;
		case sf::Keyboard::Z:
			fire = true;
			break;
		default:
			break;
	}
}

void Player::OnKeyReleased(sf::Event::KeyEvent key){
	sf::Keyboard::Key keycode = key.code;
	switch (keycode){
		case sf::Keyboard::Up:
			up = false;
			break;
		case sf::Keyboard::Down:
			down = false;
			break;
		case sf::Keyboard::Left:
			left = false;
			break;
		case sf::Keyboard::Right:
			right = false;
			break;
		case sf::Keyboard::Z:
			fire = false;
			break;
		default:
			break;
	}

}

void Player::OnCollisionEnter(GameObject *other){
	if (other->GetType() == "enemy"){
		GameObject::layerDelete.insert(this);
		Essential::isGameOver = true;
	}
}
