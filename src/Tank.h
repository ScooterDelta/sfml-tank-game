// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Tank.h

#ifndef TANK_H_
#define TANK_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <ctime>
#include "DrawableObject.h"
#include "Score.h"
#include "Angle.h"
#include "Vector2D.h"

using namespace sf;

class Tank : public DrawableObject
{
public:
	// Enumerations for control.
	enum Movement{NONE = 0, FORWARD, BACKWARD, FORWARDOBSTACLE, BACKWARDOBSTACLE};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	// Public access functions.
	Tank(Vector2D position, Score::PLAYER player, Vector2D ScreenSize = {1600.f, 900.f});
	// Virtual functions from Drawable
	virtual float getDirection();
	virtual Vector2D getPosition();
	virtual RectSize getSize();
	// Destructor for the tank.
	virtual ~Tank() {}
	// Overloaded functions for moving the tank object
	void setMovement(Movement movement, bool isHorizontal = false, float Magnitude = 6.f);
	void setMovement(Direction direction, float Magnitude = 4.f);
	// Return number of mines remaining.
	int getAllowedMines();
	// Decrement mines since one is planted
	void plantMine();
	// Vertexes of tank.
	Vector2D frontLeft();
	Vector2D frontRight();
	Vector2D backLeft();
	Vector2D backRight();
	// Respawn the tank in the starting location
	void respawn();
	// Return the player of the tank.
	Score::PLAYER getPlayer();
private:
	// Private member variables.
	Vector2D _position;
	RectSize _size;
	Angle _direction;
	float _pi;
	float _cornerAngle;
	float _cornerDistance;
	float _velocityModifier;
	float _angleModifier;
	int _allowedMines;
	Vector2D _spawnLocation;
	Vector2D _screenDimensions;
	Score::PLAYER _player;
};

#endif /* TANK_H_ */
