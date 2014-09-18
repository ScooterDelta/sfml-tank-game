#include "Missile.h"

Missile::Missile(Vector2f location, float direction) :
	_position{location},
	_direction{direction},
	_pi{atan(1) * 4},
	_collisions{1},
	_velocityModifier{-12.f}
{
	// Configure the missile object
	_size.Height = 11.07;
	_size.Width = 19.35;

	_velocity.x = _velocityModifier * cos(_direction.getAngle() * _pi / 180);
	_velocity.y = _velocityModifier * sin(_direction.getAngle() * _pi / 180);
}

Missile::~Missile()
{
	// Destructor
}

float Missile::getDirection()
{
	return _direction.getAngle();
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

bool Missile::isDestroyable(bool isHorizontal)
{
	// Returns true if the missile is out of bounces and can be destroyed.
	if(_collisions == 0)
		return true;
	else
	{
		_collisions--;
		if(isHorizontal)
		{
			_velocity.y *= -1;
			if(_direction.getAngle() >= 90 && _direction.getAngle() < 270)
				_direction = atan(_velocity.y/_velocity.x) * 180 / _pi + 180;
			else
				_direction = atan(_velocity.y/_velocity.x) * 180 / _pi;
		}
		else
		{
			_velocity.x *= -1;

			if(_direction.getAngle() > 90 && _direction.getAngle() <= 270)
				_direction = atan(_velocity.y/_velocity.x) * 180 / _pi;
			else
				_direction = atan(_velocity.y/_velocity.x) * 180 / _pi + 180;
		}

		return false;
	}
}
