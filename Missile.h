#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

using namespace sf;

class Missile
{
public:
	Missile(RenderWindow * window, float direction, Vector2f location);
	~Missile();
	Vector2f getPosition();
	bool updateIsDestroyed();
private:
	CircleShape _missile;
	RenderWindow * _window;
	Vector2f _velocity;
	float _pi;
};

#endif /* MISSILE_H_ */
