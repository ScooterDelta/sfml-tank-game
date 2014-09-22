#include "Obstacle.h"

Obstacle::Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture) :
	_direction{0},
	_position{position},
	_remainingHits{3},
	_texture{texture}
{
	_size.Width = windowSize.x/32;
	_size.Height = windowSize.y/18;
}

float Obstacle::getDirection()
{
	return _direction;
}

Vector2D Obstacle::getPosition()
{
	return _position;
}

RectSize Obstacle::getSize()
{
	return _size;
}

Vector2D Obstacle::topLeft()
{
	return _position;
}

Vector2D Obstacle::topRight()
{
	return Vector2D{_position.x + _size.Width, _position.y};
}
Vector2D Obstacle::bottomLeft()
{
	return Vector2D{_position.x, _position.y + _size.Height};
}
Vector2D Obstacle::bottomRight()
{
	return Vector2D{_position.x + _size.Width, _position.y + _size.Height};
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

Obstacle::TEXTURE Obstacle::getTexture()
{
	return _texture;
}
