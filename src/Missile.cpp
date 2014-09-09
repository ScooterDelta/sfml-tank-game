#include "Missile.h"

Missile::Missile(RenderWindow * window, float direction, Vector2f location) :
	_window{window},
	_velocity{Vector2f{0,0}},
	_pi{atan(1) * 4}
{
	// Initialize the missile object.
	_missile.setRadius(4);
	_missile.setOrigin(Vector2f{2,2});
	_missile.setFillColor(Color::Red);
	_missile.setPosition(location);

	_velocity.x = -12.f * cos(direction * _pi / 180);
	_velocity.y = -12.f * sin(direction * _pi / 180);
}

Missile::~Missile()
{
	// Display a destruction animation.
	_missile.setOrigin(Vector2f{7, 7});
	_missile.setRadius(14);
	_missile.setFillColor(Color::Green);
	_window->draw(_missile);
}

bool Missile::updateIsDestroyed()
{
	// Update the location of the missile and check if it leaves the bounds of the screen.
	_missile.move(_velocity);
	_window->draw(_missile);
	if(_missile.getPosition().x < 0 || _missile.getPosition().y < 0 ||
			_missile.getPosition().x > (_window->getSize().x - 10) ||
			_missile.getPosition().y > (_window->getSize().y - 10))
		return true;
	else
		return false;
}

Vector2f Missile::getPosition()
{
	// return the position of the missile.
	return _missile.getPosition();
}
