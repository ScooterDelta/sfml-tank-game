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
	// Enumerations for control.
	enum Movement{NONE = 0, FORWARD, BACKWARD};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	// Public access functions.
	Tank(std::list<std::unique_ptr<Missile>> * missiles, Vector2f position, Controller::Players player);
	// Destructor for the tank.
	~Tank();
	// Update the location of the tank on the screen and draw it.
	void update();
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
	// Functions to return the corners of the tank object.
	Vector2f frontLeft();
	Vector2f frontRight();
	Vector2f backLeft();
	Vector2f backRight();
	// Return the center of the tank object.
	Vector2f getPosition();
	// Function to initialize the static render window.
	static void setRenderWindow(RenderWindow * window){
		_window = window;
	}
private:
	// Private member variables.
	Sprite _SpriteTank;
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
