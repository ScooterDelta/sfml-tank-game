#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

using namespace sf;

class Missile
{
public:
	// Constructor
	Missile(RenderWindow * window, float direction, Vector2f location);
	~Missile();
	// Return the position of the missile.
	Vector2f getPosition();
	// Update the missile, returns true if the missile leaves the screen.
	bool updateIsDestroyed();
private:
	// Private member variables
	CircleShape _missile;
	RenderWindow * _window;
	Vector2f _velocity;
	float _pi;
};

#endif /* MISSILE_H_ */
