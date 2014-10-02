#include "Turret.h"

Turret::Turret(Vector2D position, Vector2D range) :
	_direction{(range.x + range.y) / 2},
	_position{position},
	_size{40.f, 40.f},
	_range{range},
	_pi{atan(1) * 4},
	_isClockwise{true}
{}

bool Turret::canFollowTarget(DrawableObject & target)
{
	float distance = sqrt(pow(target.getPosition().x - _position.x,2) +
			pow(target.getPosition().y - _position.y, 2));
	Angle direction = atan2(_position.y - target.getPosition().y,
			_position.x - target.getPosition().x) / _pi * 180 ;

	if(distance < 500 && (direction.getAngle() - _direction.getAngle() < 5
			&& direction.getAngle() - _direction.getAngle() > -5)
			&& (direction > _range.x && direction < _range.y))
	{
		_direction = direction;
		return true;
	}
	else
		return false;
}

void Turret::update()
{
	if(_direction.getAngle() >= _range.y)
		_isClockwise = false;
	else if (_direction.getAngle() <= _range.x)
		_isClockwise = true;

	if(_isClockwise)
		_direction += 0.5;
	else if(!_isClockwise)
		_direction -= 0.5;
}

Vector2D Turret::getTopLeft()
{
	Vector2D tempVect{_position.x - _size.Width/2, _position.y - _size.Height/2};
	return tempVect;
}

Vector2D Turret::getBottomRight()
{
	Vector2D tempVect{_position.x + _size.Width/2, _position.y + _size.Height/2};
	return tempVect;
}

// Return the direction the object is facing.
float Turret::getDirection()
{
	return _direction.getAngle();
}

// Return the position of the object.
Vector2D Turret::getPosition()
{
	return _position;
}

Vector2D Turret::getFirePosition()
{
	float cornerDist = sqrt(pow(_size.Height/2,2) + pow(_size.Width/2,2));
	Vector2D firePosition{_position};

	firePosition.x -= cornerDist * (cos(_direction.getAngleRadians()));
	firePosition.y -= cornerDist * (sin(_direction.getAngleRadians()));

	return firePosition;
}

// Return the size of the object
RectSize Turret::getSize()
{
	return _size;
}
