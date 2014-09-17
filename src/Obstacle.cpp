#include "Obstacle.h"

Obstacle::Obstacle(Vector2f position, RectSize size) :
	_direction{0},
	_position{position}
{
	_size.Width = size.Width;
	_size.Height = size.Height;
}

float Obstacle::getDirection()
{
	return _direction;
}

Vector2f Obstacle::getPosition()
{
	return _position;
}

RectSize Obstacle::getSize()
{
	return _size;
}

Vector2f Obstacle::topLeft()
{
	return Vector2f{_position.x - _size.Width/2, _position.y - _size.Height/2};
}

Vector2f Obstacle::topRight()
{
	return Vector2f{_position.x + _size.Width/2, _position.y - _size.Height/2};
}
Vector2f Obstacle::bottomLeft()
{
	return Vector2f{_position.x - _size.Width/2, _position.y + _size.Height/2};
}
Vector2f Obstacle::bottomRight()
{
	return Vector2f{_position.x + _size.Width/2, _position.y + _size.Height/2};
}
