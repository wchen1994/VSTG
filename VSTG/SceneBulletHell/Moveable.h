#pragma once

#include "Angle.h"
#include "SFML/System.hpp"

class Moveable {
public:
	Moveable(const sf::Vector2f & pos = sf::Vector2f(), const CommResMeth::Angle & rot = 0.f) :
		position(pos), rotation(rot) {}
	const sf::Vector2f& getPosition() const { return position; }
	void setPosition(const sf::Vector2f & pos) { position = pos; }
protected:
	sf::Vector2f position;
	CommResMeth::Angle rotation;
};