#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <set>
#include <iostream>
#include <string>
#include <memory>

class GameObject{
protected:
	sf::Vector2<float> position;
	std::shared_ptr<sf::Drawable> drawing;
	float colliderSize;
public:
	GameObject();
	sf::Vector2<float> getPosition(){ return position; }
	float getSize(){ return colliderSize; }
	virtual ~GameObject();
	virtual void Draw(sf::RenderWindow& wnd);
	virtual void Update();
	virtual void OnKeyPressed(sf::Event::KeyEvent key);
	virtual void OnKeyReleased(sf::Event::KeyEvent key);
	virtual void OnCollisionEnter(GameObject *other);
	virtual std::string GetType() { return ""; }
};
