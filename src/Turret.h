#ifndef TURRET_H_
#define TURRET_H_

#include "DrawableObject.h"
#include <cmath>
#include <iostream>

class Turret : public DrawableObject
{
public:
	Turret(Vector2D position, Vector2D range);
	bool canFollowTarget(DrawableObject & target);
	void update();

	// Return the direction the object is facing.
	virtual float getDirection();
	// Return the position of the object.
	virtual Vector2D getPosition();
	// Return the size of the object
	virtual RectSize getSize();

	Vector2D getTopLeft();
	Vector2D getBottomRight();

	Vector2D getFirePosition();

private:
	// Private member variables
	Angle _direction;
	Vector2D _position;
	RectSize _size;
	Vector2D _range;
	const float _pi;
	bool _isClockwise;
};



#endif /* TURRET_H_ */
