#include "Turret.h"

Turret::Turret(Vector2D position, Vector2D range, Vector2D screenSize) :
	AxisAligned{position, (range.x + range.y) / 2, {40.f * screenSize.x/1600.f, 40.f * screenSize.y/900.f}},
	_range{range},
	_pi{atan(1) * 4},
	_isClockwise{true},
	_fireTime{clock() - 500},
	_lockDistance{500 * screenSize.x / 1600}
{}

bool Turret::canFollowTarget(DrawableObject & target, bool TargetInvisible)
{
	float distance = sqrt(pow(target.getPosition().x - _position.x,2) +
			pow(target.getPosition().y - _position.y, 2));
	Angle direction = atan2(_position.y - target.getPosition().y,
			_position.x - target.getPosition().x) / _pi * 180 ;

	if(distance < _lockDistance && (direction.getAngle() - DrawableObject::_direction.getAngle() < 5
			&& direction.getAngle() - DrawableObject::_direction.getAngle() > -5)
			&& (direction > _range.x && direction < _range.y)
			&& !TargetInvisible)
	{
		DrawableObject::_direction = direction;
		return true;
	}
	else
		return false;
}

bool Turret::canFireMissile()
{
	if(clock() - _fireTime > 500)
	{
		_fireTime = clock();
		return true;
	}
	else return false;
}

void Turret::update()
{
	if(DrawableObject::_direction.getAngle() >= _range.y)
		_isClockwise = false;
	else if (DrawableObject::_direction.getAngle() <= _range.x)
		_isClockwise = true;

	if(_isClockwise)
		DrawableObject::_direction += 0.5;
	else if(!_isClockwise)
		DrawableObject::_direction -= 0.5;
}

Vector2D Turret::getFirePosition()
{
	float cornerDist = sqrt(pow(_size.Height/2,2) + pow(_size.Width/2,2));
	Vector2D firePosition{_position};

	firePosition.x -= cornerDist * (cos(DrawableObject::_direction.getAngleRadians()));
	firePosition.y -= cornerDist * (sin(DrawableObject::_direction.getAngleRadians()));

	return firePosition;
}
