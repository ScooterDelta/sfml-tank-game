// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Missile.cpp

#include "Missile.h"

Missile::Missile(Vector2D location, float direction, Score::PLAYER player, Vector2D windowSize) :
	DrawableObject{location, direction, {0,0}},
	_pi{atan(1) * 4},
	_collisions{1},
	_velocityModifier{-12.f},
	_player{player}
{
	_velocity.x = _velocityModifier * cos(_direction.getAngle() * _pi / 180);
	_velocity.y = _velocityModifier * sin(_direction.getAngle() * _pi / 180);
}

Missile::~Missile()
{
	// Destructor
}

void Missile::update()
{
	DrawableObject::_position.x += _velocity.x;
	DrawableObject::_position.y += _velocity.y;
}

bool Missile::isDestroyable(bool isHorizontal)
{
	// Returns true if the missile is out of bounces and can be destroyed.
	if(_collisions == 0 || isDestroyCone())
		return true;
	else
	{
		_collisions--;
		if(isHorizontal)
		{
			_velocity.y *= -1;

			if(DrawableObject::_direction.getAngle() >= 90 && DrawableObject::_direction.getAngle() < 270)
				DrawableObject::_direction = atan(_velocity.y/_velocity.x) * 180 / _pi + 180;
			else
				DrawableObject::_direction = atan(_velocity.y/_velocity.x) * 180 / _pi;
		}
		else
		{
			_velocity.x *= -1;

			if(DrawableObject::_direction.getAngle() > 90 && DrawableObject::_direction.getAngle() <= 270)
				DrawableObject::_direction = atan(_velocity.y/_velocity.x) * 180 / _pi;
			else
				DrawableObject::_direction = atan(_velocity.y/_velocity.x) * 180 / _pi + 180;
		}

		return false;
	}
}

// Check if the missile is hitting the wall within a small angle,
// if so the missile can be destroyed.
bool Missile::isDestroyCone(float cone)
{
	if (DrawableObject::_direction.getAngle() < (90 + cone) && DrawableObject::_direction.getAngle() > (90 - cone))
		return true;
	else if ((DrawableObject::_direction.getAngle() < cone && DrawableObject::_direction.getAngle() >= 0) ||
			(DrawableObject::_direction.getAngle() > (360 - cone) && DrawableObject::_direction.getAngle() < 360))
		return true;
	else if (DrawableObject::_direction.getAngle() < (180 + cone) && DrawableObject::_direction.getAngle() > (180 - cone))
		return true;
	else if (DrawableObject::_direction.getAngle() < (270 + cone) && DrawableObject::_direction.getAngle() > (270 - cone))
		return true;
	else return false;
}

Score::PLAYER Missile::getPlayer()
{
	return _player;
}
