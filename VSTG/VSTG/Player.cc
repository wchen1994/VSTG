#include "Player.hpp"
#include "Bullet.hpp"
#include "Essential.hpp"
#include "Game.hpp"

Player::Player() :
	GameObject()
{
	up = down = left = right = false;
	fire = false; radius = 5;
	position.x = 400;
	position.y = 300;
	velocity.x = 0;
	velocity.y = 0;
	speed = 180;
	cooldown = 0;
	originX = originY = radius;
	pSprite = std::make_shared<sf::CircleShape>(sf::CircleShape());
	pSprite->setRadius(radius);
	pSprite->setOrigin(originX, originY);
	pSprite->setPosition(position);
	drawing = pSprite;
}

void Player::Update(const float& dt){
	velocity = { 0.0f,0.0f };
	if (up)
		velocity.y -= 1.0f;
	if (down)
		velocity.y += 1.0f;
	if (left)
		velocity.x -= 1.0f;
	if (right)
		velocity.x += 1.0f;
}

void Player::FixedUpdate(const float & dt)
{
	// Player Movement
	const float sqlen = velocity.x*velocity.x + velocity.y*velocity.y;
	if (sqlen != 0) {
		const float len = sqrt(sqlen);
		position += velocity / len * speed * dt;
		if (position.x < 0)
			position.x = 0;
		if (position.x > 800)
			position.x = 800;
		if (position.y < 0)
			position.y = 0;
		if (position.y > 600)
			position.y = 600;
	}
	pSprite->setPosition(position);

	// Player Fire
	if (cooldown > 0) {
		cooldown -= dt;
	}
	else if (fire) {
		Game::layerDefault.insert(std::make_shared<Bullet>(Bullet(position.x, position.y)));
		cooldown = cooldownDuration;
	}
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

void Player::OnCollisionEnter(std::shared_ptr<GameObject> other){
	if (other->GetType() == "enemy"){
		Game::layerDelete.insert(shared_from_this());
		Essential::isGameOver = true;
	}
}
