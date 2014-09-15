#include "Missile.h"

Missile::Missile(float direction, Vector2f location) :
	_velocity{Vector2f{0,0}},
	_pi{atan(1) * 4},
	_direction{direction}
{
	// Initialize the missile object.
	_missile.setTexture(*_missileTexture, true);
	_missile.setOrigin(_missile.getGlobalBounds().width/2, _missile.getGlobalBounds().height/2);
	_missile.setScale(0.03,0.03);
	_missile.setPosition(location);
	_missile.setRotation(direction);

	_velocity.x = -12.f * cos(direction * _pi / 180);
	_velocity.y = -12.f * sin(direction * _pi / 180);
}

Missile::~Missile()
{
	// Display a destruction animation.
	Vector2f position{_missile.getPosition()};
	_missile.setTexture(*_explosionTexture, true);
	_missile.setOrigin(_missile.getLocalBounds().width/2, _missile.getLocalBounds().height/2);
	_missile.setScale(0.05, 0.05);
	_missile.setPosition(position);

	_window->draw(_missile);
}

void Missile::update()
{
	// Update the location of the missile and check if it leaves the bounds of the screen.
	_missile.move(_velocity);
	_window->draw(_missile);
}

Vector2f Missile::getPosition()
{
	// return the position of the missile.
	return _missile.getPosition();
}

float Missile::getDirection()
{
	return _direction;
}
