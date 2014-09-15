#include "Tank.h"

Tank::Tank(std::list<std::unique_ptr<Missile>> * missiles, Vector2f position, Controller::Players player) :
	_screenDimensions{_window->getSize()},
	_spawnPosition{position},
	_velocity{Vector2f{0,0}},
	_direction{90},
	_pi{atan(1) * 4},
	_life{100.f},
	_player{player},
	_missiles{missiles},
	_missileTimer{0}
{
	// Initialize the tank sprite
	if(player == Controller::Player1)
		_tankTexture.loadFromFile("assets/tank1.png");
	if(player == Controller::Player2)
		_tankTexture.loadFromFile("assets/tank2.png");

	// Set up the sprite object
	_drawable.setTexture(_tankTexture, true);
	_drawable.setOrigin(_drawable.getGlobalBounds().width/2, _drawable.getGlobalBounds().height/2);
	_drawable.setScale(0.07, 0.06);

	// Get the member variables that define the size of the sprite object.
	FloatRect tempBound{_drawable.getGlobalBounds()};
	_cornerAngle = tan(tempBound.height/tempBound.width) * 180 / _pi;
	_cornerDistance = sqrt(pow(tempBound.height/2, 2) + pow(tempBound.width/2,2));

	_drawable.setPosition(position);
	_drawable.rotate(_direction);
}

void Tank::respawn()
{
	_direction = 90;
	_life = 100;
	_drawable.setPosition(_spawnPosition);

	Tank::update();
}

void Tank::setMovement(Movement movement, float Magnitude)
{
	switch (movement)
	{
	case NONE:
		// No movement
		_velocity.x = 0.f;
		_velocity.y = 0.f;
		break;
	case FORWARD:
		// Move in the current direction.
		_velocity.x = -Magnitude * cos(_direction * _pi / 180);
		_velocity.y = -Magnitude * sin(_direction * _pi / 180);
		break;
	case BACKWARD:
		// Move in the reverse of the current direction.
		_velocity.x = Magnitude * cos(_direction * _pi / 180);
		_velocity.y = Magnitude * sin(_direction * _pi / 180);
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

float Tank::getDirection()
{
	return _direction;
}

Vector2f Tank::frontLeft()
{
	// Calculate the location of the front left corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((_direction - _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((_direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::frontRight()
{
	// Calculate the location of the front right corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((_direction + _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((_direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backLeft()
{
	// Calculate the location of the back left corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((180 + _direction + _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((180 + _direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backRight()
{
	// Calculate the location of the back right corner of the tank
	float xLocation = _drawable.getPosition().x -
			_cornerDistance * cos((180 + _direction - _cornerAngle) * _pi / 180);
	float yLocation = _drawable.getPosition().y -
			_cornerDistance * sin((180 + _direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

void Tank::fireWeapon()
{
	// Fire a missile from the tank (Change to have multiple missile types?)
	if((clock() - _missileTimer) > 500)
	{
		Vector2f turret{(frontLeft().x + frontRight().x)/2, (frontRight().y + frontLeft().y)/2};
		std::unique_ptr<Missile> newMissile(new Missile{_direction, turret});
		_missiles->push_back(std::move(newMissile));

		_missileTimer = clock();
	}
}

Vector2f Tank::getPosition()
{
	// Return the center of the tank.
	return _drawable.getPosition();
}

void Tank::update()
{
	// Move the tank on the screen and rotate it.
	_drawable.setRotation(_direction);
	_drawable.move(_velocity);

	// Draw the tank on the screen
	_window->draw(_drawable);
}

void Tank::takeDamage(float damage)
{
	// Reduce the tanks life by so much damage
	_life -= damage;
}

float Tank::getLife() const
{
	// Return the remaining life of the tank.
	return _life;
}
