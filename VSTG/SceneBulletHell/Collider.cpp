#include "Collider.h"

Collider::Collider(ColliderType type, const ColliderProperities & propertites,
	FLAG_TYPE selfFlag, FLAG_TYPE interactFlag,
	const sf::Vector2f & pos, const CommResMeth::Angle & rot) 
	:
	Moveable(pos, rot), colliderType(type), colliderProperities(propertites), 
	colliderFlag(selfFlag), interactFlag(interactFlag)
{
}

Collider::~Collider()
{
}

bool Collider::processCollision(Collider * const other)
{
	if (interactFlag & other->colliderFlag) {
		bool isCollided = false;
		switch (colliderType) {
		case Circle:
			switch (other->colliderType) {
			case Circle:
				isCollided = isCollideCircleCircle(other);
				break;
			case Rectangle:
				isCollided = other->isCollideRectangleCircle(this);
				break;
			}
			break;
		case Rectangle:
			switch (other->colliderType) {
			case Circle:
				isCollided = isCollideRectangleCircle(other);
				break;
			case Rectangle:
				isCollided = isCollideRectangleRectangle(other) &&
					other->isCollideRectangleRectangle(this);
				break;
			}
			break;
			break;
		}

		if (isCollided) {
			OnCollisionEnter(other);
			other->OnCollisionEnter(this);
			return true;
		}
		return false;
	}
	return false;
}

bool Collider::isCollideCircleCircle(const Collider * const other) const
{
	sf::Vector2f diffPos = position - other->position;
	float diffx = diffPos.x;
	float diffy = diffPos.y;
	float sumOfRadius = colliderProperities.circle.radius + other->colliderProperities.circle.radius;
	if (diffx * diffx + diffy * diffy < sumOfRadius * sumOfRadius) {
		return true;
	}
	return false;
}

bool Collider::isCollideRectangleCircle(const Collider * const other) const
{
	float rot = rotation.rad();
	sf::Vector2f diffPos = other->position - position;
	float newX = diffPos.x * cos(rot) - diffPos.y * sin(rot);
	float newY = diffPos.x * sin(rot) + diffPos.y * cos(rot);

	float halfWidth = colliderProperities.rectangle.width / 2.f;
	float halfHeight = colliderProperities.rectangle.height / 2.f;
	float dx, dy;
	if (newX >= 0) {
		dx = -halfWidth;
		if (newY >= 0) {
			dy = -halfHeight;
		}
		else {
			dy = +halfHeight;
		}
	}
	else {
		dx = halfWidth;
		if (newY >= 0) {
			dy = -halfHeight;
		}
		else {
			dy = +halfHeight;
		}
	}

	float diffx = newX + dx;
	float diffy = newY + dy;
	float radius = other->colliderProperities.circle.radius;
	if (diffx * diffx + diffy * diffy < radius * radius) {
		return true;
	}

	return false;
}

bool Collider::isCollideRectangleRectangle(const Collider * const other) const
{
	float rot = rotation.rad();
	float diffRot = CommResMeth::Angle(other->rotation - rotation).rad();
	sf::Vector2f diffPos = other->position - position;
	float newX = diffPos.x * cos(rot) - diffPos.y * sin(rot);
	float newY = diffPos.x * sin(rot) + diffPos.y * cos(rot);
	
	float halfWidth = colliderProperities.rectangle.width / 2.f;
	float halfHeight = colliderProperities.rectangle.height / 2.f;
	float otherHalfWidth = other->colliderProperities.rectangle.width / 2.f;
	float otherHalfHeight = other->colliderProperities.rectangle.height / 2.f;

	float diffX = otherHalfWidth * cos(diffRot) + otherHalfHeight * sin(diffRot);
	float diffY = -otherHalfWidth * sin(diffRot) + otherHalfHeight * cos(diffRot);

	if (newX + diffX > -halfWidth && newX - diffX < halfWidth / 2.f &&
		newY + diffY > -halfHeight && newY - diffY < halfHeight / 2.f) {
		return true;
	}

	return false;
}

