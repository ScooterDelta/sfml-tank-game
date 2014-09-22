// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Obstacle.cpp

#include "Obstacle.h"

// Constructor
Obstacle::Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture) :
	_direction{0},
	_position{position},
	_remainingHits{3},
	_texture{texture}
{
	_size.Width = windowSize.x/32;
	_size.Height = windowSize.y/18;
}

// Overloaded inherited functions.
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

// Return corners of the obstacle.
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

// Return number of remaining hits.
int Obstacle::remainingHits()
{
	return _remainingHits;
}

// Check if the obstacle is destroyable and decrement remaining hits if it is.
bool Obstacle::isDestroyable()
{
	_remainingHits--;
	return _remainingHits < 0;
}

// Return which texture to use for display.
Obstacle::TEXTURE Obstacle::getTexture()
{
	return _texture;
}
