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
#include "RectangleObject.h"

using namespace sf;

class Tank : public RectangleObject
{
public:
	// Enumerations for control.
	enum Movement{NONE = 0, FORWARD, BACKWARD};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	// Public access functions.
	Tank(std::list<std::unique_ptr<Missile>> * missiles, Vector2f position, Controller::Players player);
	// Destructor for the tank.
	virtual ~Tank() {}
	// Update the location of the tank on the screen and draw it.
	virtual void update();
	// Overloaded functions for moving the tank object
	void setMovement(Movement movement, float Magnitude = 6.f);
	void setMovement(Direction direction, float Magnitude = 3.f);
	// Fire the weapon (change for multiple weapon types?)
	void fireWeapon();
	// Deal damage to the tank.
	void takeDamage(float damage);
	// Reset the life and position of the tank to their starting values.
	void respawn();
	// Return the current life of the tank.
	float getLife() const;
	// Return the center of the tank object.
	virtual Vector2f getPosition();
	// return the location of the object.
	virtual Vector2f frontLeft();
	virtual Vector2f frontRight();
	virtual Vector2f backLeft();
	virtual Vector2f backRight();
	// return the direction of the object
	virtual float getDirection();
	// Function to initialize the static render window. Must be initialized for class to work.
	static void setRenderWindow(RenderWindow * window){
		_window = window;
	}
private:
	// Private member variables.
	Sprite _drawable;
	Texture _tankTexture;
	Vector2f _screenDimensions;
	static RenderWindow * _window;
	Vector2f _spawnPosition;
	Vector2f _velocity;
	float _direction;
	float _pi;
	float _cornerAngle;
	float _cornerDistance;
	float _life;
	Controller::Players _player;
	std::list<std::unique_ptr<Missile>> * _missiles;
	clock_t _missileTimer;
};

#endif /* TANK_H_ */
