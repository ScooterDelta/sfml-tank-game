#include "Missile.h"

Missile::Missile(Vector2f location, float direction) :
	_position{location},
	_direction{direction},
	_pi{atan(1) * 4}
{
	// Configure the missile object
	_size.Height = 16.56;
	_size.Width = 24.39;

	_velocity.x = -12.f * cos(direction * _pi / 180);
	_velocity.y = -12.f * sin(direction * _pi / 180);
}

Missile::~Missile()
{
	// Destructor
}

float Missile::getDirection()
{
	return _direction;
}

Vector2f Missile::getPosition()
{
	return _position;
}

RectSize Missile::getSize()
{
	return _size;
}

void Missile::update()
{
	_position.x += _velocity.x;
	_position.y += _velocity.y;
}
