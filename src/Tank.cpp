#include "Tank.h"

Tank::Tank(Vector2f position, Score::PLAYER player, Vector2f ScreenSize) :
	_position{position},
	_direction{90},
	_pi{atan(1) * 4},
	_velocityModifier{0},
	_angleModifier{0},
	_allowedMines{3},
	_spawnLocation{position},
	_screenDimensions{ScreenSize},
	_player{player}
{
	// Configure the tank object
	_size.Height = 41.65 * ScreenSize.y / 900.f;
	_size.Width = 41.65 * ScreenSize.x / 1600.f;

	_cornerDistance = sqrt(pow(_size.Height/2,2) + pow(_size.Width/2,2));
	_cornerAngle = atan(_size.Height/_size.Width) * 180 / _pi;
}

void Tank::setMovement(Movement movement, bool isHorizontal, float Magnitude)
{
	switch (movement)
	{
	case NONE:
		if(Magnitude == 0)
			_velocityModifier = 0;
		else
		{
			if(_velocityModifier < -0.4)
				_velocityModifier += 0.2;
			else if(_velocityModifier > 0.4)
				_velocityModifier -= 0.2;
			else
				_velocityModifier = 0;
			_position.x += -_velocityModifier * cos(_direction.getAngle() * _pi / 180);
			_position.y += -_velocityModifier * sin(_direction.getAngle() * _pi / 180);
		}
		break;
	case FORWARD:
		// Move in the current direction.
		if(Magnitude < 1)
		{
			_position.x += -Magnitude * cos(_direction.getAngle() * _pi / 180);
			_position.y += -Magnitude * sin(_direction.getAngle() * _pi / 180);
		}
		else
		{
			if(_velocityModifier < 0)
				_velocityModifier = 0;
			if(_velocityModifier < Magnitude)
				_velocityModifier += 0.2;
			_position.x += -_velocityModifier * cos(_direction.getAngle() * _pi / 180);
			_position.y += -_velocityModifier * sin(_direction.getAngle() * _pi / 180);
		}
		break;
	case BACKWARD:
		// Move in the reverse of the current direction.
		if(Magnitude < 1)
		{
			_position.x += Magnitude * cos(_direction.getAngle() * _pi / 180);
			_position.y += Magnitude * sin(_direction.getAngle() * _pi / 180);
		}
		else
		{
			if(_velocityModifier > 0)
				_velocityModifier = 0;
			if(_velocityModifier > -Magnitude)
				_velocityModifier -= 0.2;
			_position.x += -_velocityModifier * cos(_direction.getAngle() * _pi / 180);
			_position.y += -_velocityModifier * sin(_direction.getAngle() * _pi / 180);
		}
		break;
	case FORWARDOBSTACLE:
		if(isHorizontal == false)
			_position.y += -Magnitude / 2 * sin(_direction.getAngle() * _pi / 180);
		else
			_position.x += -Magnitude / 2 * cos(_direction.getAngle() * _pi / 180);
		break;
	case BACKWARDOBSTACLE:
		if(isHorizontal == false)
			_position.y += Magnitude / 2 * sin(_direction.getAngle() * _pi / 180);
		else
			_position.x += Magnitude / 2 * cos(_direction.getAngle() * _pi / 180);
		break;
	default:
		std::cerr << "Tank::setMovement - Oops something went wrong." << std::endl;
		break;
	}
}

void Tank::setMovement(Direction direction, float Magnitude)
{
	switch (direction)
	{
	case CLOCKWISE:
		// Rotate the sprite clockwise
		if(_angleModifier < 0)
			_angleModifier = 0;
		if(_angleModifier < Magnitude)
			_angleModifier += 0.4;
		_direction += _angleModifier;
		break;
	case ANTICLOCKWISE:
		// Rotate the sprite anticlockwise
		if(_angleModifier > 0)
			_angleModifier = 0;
		if(_angleModifier > -Magnitude)
			_angleModifier -= 0.4;
		_direction += _angleModifier;
		break;
	case STRAIGHT:
		_angleModifier = 0;
		break;
	}
}

Vector2f Tank::frontLeft()
{
	// Calculate the location of the front left corner of the tank
	float xLocation = _position.x -
			_cornerDistance * cos((_direction.getAngle() - _cornerAngle) * _pi / 180);
	float yLocation = _position.y -
			_cornerDistance * sin((_direction.getAngle() - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::frontRight()
{
	// Calculate the location of the front right corner of the tank
	float xLocation = _position.x -
			_cornerDistance * cos((_direction.getAngle() + _cornerAngle) * _pi / 180);
	float yLocation = _position.y -
			_cornerDistance * sin((_direction.getAngle() + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backLeft()
{
	// Calculate the location of the back left corner of the tank
	float xLocation = _position.x -
			_cornerDistance * cos((180 + _direction.getAngle() + _cornerAngle) * _pi / 180);
	float yLocation = _position.y -
			_cornerDistance * sin((180 + _direction.getAngle() + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backRight()
{
	// Calculate the location of the back right corner of the tank
	float xLocation = _position.x -
			_cornerDistance * cos((180 + _direction.getAngle() - _cornerAngle) * _pi / 180);
	float yLocation = _position.y -
			_cornerDistance * sin((180 + _direction.getAngle() - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::getPosition()
{
	// Return the center of the tank.
	return _position;
}

float Tank::getDirection()
{
	return _direction.getAngle();
}

RectSize Tank::getSize()
{
	return _size;
}

int Tank::getAllowedMines()
{
	return _allowedMines;
}

void Tank::plantMine()
{
	_allowedMines--;
}

Score::PLAYER Tank::getPlayer()
{
	return _player;
}

void Tank::respawn()
{
	_position = _spawnLocation;
	_direction = 90;
	_allowedMines = 3;
}
