#include "Tank.h"

Tank::Tank(Vector2f position) :
	_position{position},
	_direction{90},
	_pi{atan(1) * 4},
	_allowedMines{3}
{
	// Configure the tank object
	_size.Height = 32;
	_size.Width = 56;

	_cornerDistance = sqrt(pow(_size.Height/2,2) + pow(_size.Width/2,2));
	_cornerAngle = atan(_size.Height/_size.Width) * 180 / _pi;
}

void Tank::setMovement(Movement movement, float Magnitude)
{
	switch (movement)
	{
	case NONE:
		// No movement
		break;
	case FORWARD:
		// Move in the current direction.
		_position.x += -Magnitude * cos(_direction.getAngle() * _pi / 180);
		_position.y += -Magnitude * sin(_direction.getAngle() * _pi / 180);
		break;
	case BACKWARD:
		// Move in the reverse of the current direction.
		_position.x += Magnitude * cos(_direction.getAngle() * _pi / 180);
		_position.y += Magnitude * sin(_direction.getAngle() * _pi / 180);
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
		_direction += Magnitude;
		break;
	case ANTICLOCKWISE:
		// Rotate the sprite anticlockwise
		_direction -= Magnitude;
		break;
	case STRAIGHT:
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
