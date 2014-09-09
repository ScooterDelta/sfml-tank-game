#include "Tank.h"

constexpr float rectTankSizeX = 60;
constexpr float rectTankSizeY = 30;

Tank::Tank(RenderWindow * window, std::list<std::unique_ptr<Missile>> * missiles, Vector2f position) :
	_screenDimensions{window->getSize()},
	_window{window},
	_spawnPosition{position},
	_velocity{Vector2f{0,0}},
	_direction{90},
	_pi{atan(1) * 4},
	_cornerAngle{atan(rectTankSizeY/rectTankSizeX) * 180 / (atan(1) * 4)},
	_cornerDistance{sqrt(pow(rectTankSizeX / 2, 2) + pow(rectTankSizeY / 2, 2))},
	_life{100.f},
	_missiles{missiles},
	_missileTimer{0}
{
	_tankTexture.loadFromFile("Tank.png");
	_rectTank.setSize(Vector2f{rectTankSizeX,rectTankSizeY});
	_rectTank.setOrigin(Vector2f{rectTankSizeX/2,rectTankSizeY/2});
	_rectTank.setOutlineColor(Color::Blue);
	_rectTank.setOutlineThickness(1);
	_rectTank.setTexture(&_tankTexture);
	_rectTank.setPosition(position);
	_rectTank.rotate(_direction);
}

void Tank::respawn()
{
	_direction = 90;
	_life = 100;
	_rectTank.setPosition(_spawnPosition);

	Tank::update();
}

void Tank::setMovement(Movement movement, float Magnitude)
{
	switch (movement)
	{
	case NONE:
		_velocity.x = 0.f;
		_velocity.y = 0.f;
		break;
	case FORWARD:
		_velocity.x = -Magnitude * cos(_direction * _pi / 180);
		_velocity.y = -Magnitude * sin(_direction * _pi / 180);
		break;
	case BACKWARD:
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
		_direction += Magnitude;
		break;
	case ANTICLOCKWISE:
		_direction -= Magnitude;
		break;
	case STRAIGHT:
		break;
	}
}

Vector2f Tank::frontLeft()
{
	float xLocation = _rectTank.getPosition().x -
			_cornerDistance * cos((_direction - _cornerAngle) * _pi / 180);
	float yLocation = _rectTank.getPosition().y -
			_cornerDistance * sin((_direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::frontRight()
{
	float xLocation = _rectTank.getPosition().x -
			_cornerDistance * cos((_direction + _cornerAngle) * _pi / 180);
	float yLocation = _rectTank.getPosition().y -
			_cornerDistance * sin((_direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backLeft()
{
	float xLocation = _rectTank.getPosition().x -
			_cornerDistance * cos((180 + _direction + _cornerAngle) * _pi / 180);
	float yLocation = _rectTank.getPosition().y -
			_cornerDistance * sin((180 + _direction + _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

Vector2f Tank::backRight()
{
	float xLocation = _rectTank.getPosition().x -
			_cornerDistance * cos((180 + _direction - _cornerAngle) * _pi / 180);
	float yLocation = _rectTank.getPosition().y -
			_cornerDistance * sin((180 + _direction - _cornerAngle) * _pi / 180);
	return Vector2f{xLocation, yLocation};
}

void Tank::fireWeapon()
{
	if((clock() - _missileTimer) > 100)
	{
		Vector2f turret{(frontLeft().x + frontRight().x)/2, (frontRight().y + frontLeft().y)/2};
		std::unique_ptr<Missile> newMissile(new Missile{_window, _direction, turret});
		_missiles->push_back(std::move(newMissile));

		_missileTimer = clock();
	}
}

Vector2f Tank::getPosition()
{
	return _rectTank.getPosition();
}

void Tank::update()
{
	_rectTank.setRotation(_direction);
	_rectTank.move(_velocity);

	_window->draw(_rectTank);
}

void Tank::takeDamage(float damage)
{
	_life -= damage;
}

float Tank::getLife() const
{
	return _life;
}
