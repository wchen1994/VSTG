#pragma once

#include <queue>

#include "Moveable.h"

typedef uint32_t FLAG_TYPE;
#define COLLI_FLAG_NOTHING			static_cast<FLAG_TYPE>( 0		) // All bits to 0
#define COLLI_FLAG_EVERYTHING		static_cast<FLAG_TYPE>( -1		) // All bits to 1
#define COLLI_FLAG_0				static_cast<FLAG_TYPE>( 1 << 0	)
#define COLLI_FLAG_1				static_cast<FLAG_TYPE>( 1 << 1	)
#define COLLI_FLAG_2				static_cast<FLAG_TYPE>( 1 << 2	)
#define COLLI_FLAG_3				static_cast<FLAG_TYPE>( 1 << 3	)
#define COLLI_FLAG_4				static_cast<FLAG_TYPE>( 1 << 4	)

class Collider : public virtual Moveable
{
public: // Defines
	enum ColliderType : char {
		Circle, Rectangle
	};

	union ColliderProperities {
		struct CilcleCollider {
			float radius;
		} circle;
		struct RectangleCollider {
			float width;
			float height;
		} rectangle;
	};

public:
	Collider(ColliderType type, const ColliderProperities & propertites, 
		FLAG_TYPE selfFlag = COLLI_FLAG_EVERYTHING, FLAG_TYPE interactFlag = COLLI_FLAG_EVERYTHING,
		const sf::Vector2f & pos = sf::Vector2f(), const CommResMeth::Angle & rot = 0.f);
	~Collider();
	bool processCollision(Collider* const other);

public:
	virtual void OnCollisionEnter(Collider* const other) {}

public: // Variables
	ColliderType colliderType;
	FLAG_TYPE colliderFlag;
	FLAG_TYPE interactFlag;
	ColliderProperities colliderProperities;
	bool isTriger;

private:
	bool isCollideCircleCircle(const Collider* const other) const;
	bool isCollideRectangleCircle(const Collider* const other) const;
	bool isCollideRectangleRectangle(const Collider* const other) const;
};

