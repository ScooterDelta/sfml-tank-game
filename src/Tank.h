#ifndef TANK_H_
#define TANK_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <ctime>
#include "Missile.h"
#include "Controller.h"

using namespace sf;

class Tank
{
public:
	enum Movement{NONE = 0, FORWARD, BACKWARD};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	Tank(RenderWindow * window, std::list<std::unique_ptr<Missile>> * missiles, Vector2f position);
	void update();
	void setMovement(Movement movement, float Magnitude = 6.f);
	void setMovement(Direction direction, float Magnitude = 3.f);
	void fireWeapon();
	void takeDamage(float damage);
	void respawn();
	float getLife() const;
	Vector2f frontLeft();
	Vector2f frontRight();
	Vector2f backLeft();
	Vector2f backRight();
	Vector2f getPosition();
private:
	RectangleShape _rectTank;
	Texture _tankTexture;
	Vector2f _screenDimensions;
	RenderWindow * _window;
	Vector2f _spawnPosition;
	Vector2f _velocity;
	float _direction;
	float _pi;
	float _cornerAngle;
	float _cornerDistance;
	float _life;
	std::list<std::unique_ptr<Missile>> * _missiles;
	clock_t _missileTimer;
};

#endif /* TANK_H_ */
