#include "Tank.h"

Tank::Tank(RenderWindow * window, std::list<std::unique_ptr<Missile>> * missiles, Vector2f position) :
	_screenDimensions{window->getSize()},
	_window{window},
	_spawnPosition{position},
	_velocity{Vector2f{0,0}},
	_direction{90},
	_pi{atan(1) * 4},
	_life{100.f},
	_missiles{missiles},
	_missileTimer{0}
{
	// Initialize the tank sprite
	_tankTexture.loadFromFile("assets/Tank.png");
	_SpriteTank.setTexture(_tankTexture, true);
	_SpriteTank.setOrigin(_SpriteTank.getGlobalBounds().width/2, _SpriteTank.getGlobalBounds().height/2);
	_SpriteTank.setScale(0.1, 0.1);

	// Get the member variables that define the size of the sprite object.
	FloatRect tempBound{_SpriteTank.getGlobalBounds()};
	_cornerAngle = tan(tempBound.height/tempBound.width) * 180 / _pi;
	_cornerDistance = sqrt(pow(tempBound.height/2, 2) + pow(tempBound.width/2,2));

	_SpriteTank.setPosition(position);
	_SpriteTank.rotate(_direction);
}

Tank::~Tank()
{

}

void Tank::respawn()
{
	_direction = 90;
	_life = 100;
	_SpriteTank.setPosition(_spawnPosition);

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

Vector2f Tank::frontLeft()
{
	// Calculate the location of the front left corner of the tank
	float xLocation = _SpriteTank.getPosition().x -
			_cornerDistance * cos((_direction - _cornerAngle) * _pi / 180);
	float yLocation = _SpriteTank.getPosition().y -
			_cornerDistance * sin((_direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::frontRight()
{
	// Calculate the location of the front right corner of the tank
	float xLocation = _SpriteTank.getPosition().x -
			_cornerDistance * cos((_direction + _cornerAngle) * _pi / 180);
	float yLocation = _SpriteTank.getPosition().y -
			_cornerDistance * sin((_direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backLeft()
{
	// Calculate the location of the back left corner of the tank
	float xLocation = _SpriteTank.getPosition().x -
			_cornerDistance * cos((180 + _direction + _cornerAngle) * _pi / 180);
	float yLocation = _SpriteTank.getPosition().y -
			_cornerDistance * sin((180 + _direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backRight()
{
	// Calculate the location of the back right corner of the tank
	float xLocation = _SpriteTank.getPosition().x -
			_cornerDistance * cos((180 + _direction - _cornerAngle) * _pi / 180);
	float yLocation = _SpriteTank.getPosition().y -
			_cornerDistance * sin((180 + _direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

void Tank::fireWeapon()
{
	// Fire a missile from the tank (Change to have multiple missile types?)
	if((clock() - _missileTimer) > 200)
	{
		Vector2f turret{(frontLeft().x + frontRight().x)/2, (frontRight().y + frontLeft().y)/2};
		std::unique_ptr<Missile> newMissile(new Missile{_window, _direction, turret});
		_missiles->push_back(std::move(newMissile));

		_missileTimer = clock();
	}
}

Vector2f Tank::getPosition()
{
	// Return the center of the tank.
	return _SpriteTank.getPosition();
}

void Tank::update()
{
	// Move the tank on the screen and rotate it.
	_SpriteTank.setRotation(_direction);
	_SpriteTank.move(_velocity);

	// Draw the tank on the screen
	_window->draw(_SpriteTank);
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
