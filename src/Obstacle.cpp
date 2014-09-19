#include "Obstacle.h"

Obstacle::Obstacle(Vector2f position, Vector2f windowSize) :
	_direction{0},
	_position{position},
	_remainingHits{1}
{
	_size.Width = windowSize.x/32;
	_size.Height = windowSize.y/18;
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
	return _position;
}

Vector2f Obstacle::topRight()
{
	return Vector2f{_position.x + _size.Width, _position.y};
}
Vector2f Obstacle::bottomLeft()
{
	return Vector2f{_position.x, _position.y + _size.Height};
}
Vector2f Obstacle::bottomRight()
{
	return Vector2f{_position.x + _size.Width, _position.y + _size.Height};
}

int Obstacle::remainingHits()
{
	return _remainingHits;
}

bool Obstacle::isDestroyable()
{
	_remainingHits--;
	return _remainingHits < 0;
}
