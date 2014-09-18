#include "Mine.h"

Mine::Mine(Vector2f position):
	_position{position}
{}

// Return the direction the object is facing.
float Mine::getDirection()
{
	return _direction.getAngle();
}

// Return the position of the object.
Vector2f Mine::getPosition()
{
	return _position;
}

// Return the size of the object
RectSize Mine::getSize()
{
	return _size;
}
