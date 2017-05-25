#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Essential.hpp"
#include "Game.hpp"

Player::Player() :
	GameObject()
{
	up = down = left = right = false;
	fire = false; radius = 5;
	position.x = float(Essential::GameCanvas.left + Essential::GameCanvas.width/2);
	position.y = float(Essential::GameCanvas.top + Essential::GameCanvas.height * 4/5);
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

	// Setup ID
	strcpy_s(objectID, "Player0");
	std::hash<std::string> hashGen;
	hasdID = hashGen(objectID);
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
	static float boundary[] = { 
		float(Essential::GameCanvas.left),
		float(Essential::GameCanvas.left + Essential::GameCanvas.width - 1),
		float(Essential::GameCanvas.top),
		float(Essential::GameCanvas.top + Essential::GameCanvas.height - 1),
	};
	if (sqlen != 0) {
		const float len = sqrt(sqlen);
		position += velocity / len * speed * dt;
		if (position.x < boundary[0])
			position.x = boundary[0];
		if (position.x > boundary[1])
			position.x = boundary[1];
		if (position.y < boundary[2])
			position.y = boundary[2];
		if (position.y > boundary[3])
			position.y = boundary[3];
	}
	pSprite->setPosition(position);

	// Player Fire
	if (cooldown > 0) {
		cooldown -= dt;
	}
	else if (fire) {
		const std::shared_ptr<Bullet> pBullet = std::make_shared<Bullet>(Bullet(position.x, position.y));
		Game::layerDefault.insert(pBullet);
		Game::layerBullet.insert(pBullet); // Something went wrong
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
	if (other->GetHash() == Enemy::hasdID){
		Game::layerDelete.insert(shared_from_this());
		Essential::isGameOver = true;
	}
}
