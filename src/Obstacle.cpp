#include "Obstacle.h"

Obstacle::Obstacle(Rect<float> ObstacleSize, float direction) :
	_pi{atan(1) * 4},
	_direction{direction}
{
	_drawable.setSize({ObstacleSize.width, ObstacleSize.height});
	_drawable.setOrigin({ObstacleSize.width/2.f, ObstacleSize.height/2.f});
	_drawable.setPosition(ObstacleSize.left, ObstacleSize.top);
	_drawable.setFillColor(Color::Cyan);

	_cornerAngle = tan(ObstacleSize.height/ObstacleSize.width) * 180 / _pi;
	_cornerDistance = sqrt(pow(ObstacleSize.height/2, 2) + pow(ObstacleSize.width/2,2));

	_drawable.setRotation(direction);
}

// Update the object (Draw on the screen)
void Obstacle::update()
{
	_window->draw(_drawable);
}

float Obstacle::getDirection()
{
	return _direction;
}

Vector2f Obstacle::frontLeft()
{
	// Calculate the location of the front left corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((_direction - _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((_direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Obstacle::frontRight()
{
	// Calculate the location of the front right corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((_direction + _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((_direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Obstacle::backLeft()
{
	// Calculate the location of the back left corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((180 + _direction + _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((180 + _direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Obstacle::backRight()
{
	// Calculate the location of the back right corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((180 + _direction - _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((180 + _direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Obstacle::getPosition()
{
	return _drawable.getPosition();
}
