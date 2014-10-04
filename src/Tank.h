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
#include "nonAxisAligned.h"
#include "Score.h"
#include "Angle.h"
#include "Vector2D.h"

using namespace sf;

class Tank : public nonAxisAligned
{
public:
	// Enumerations for control.
	enum Movement{NONE = 0, FORWARD, BACKWARD, FORWARDOBSTACLE, BACKWARDOBSTACLE};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	// Public access functions.
	Tank(Vector2D position, Score::PLAYER player, Vector2D ScreenSize = {1600.f, 900.f});
	// Virtual functions from Drawable
	// Destructor for the tank.
	virtual ~Tank() {}
	// Overloaded functions for moving the tank object
	void setMovement(Movement movement, bool isHorizontal = false, float Magnitude = 6.f);
	void setMovement(Direction direction, float Magnitude = 4.f);
	// Return number of mines remaining.
	int getAllowedMines();
	// Decrement mines since one is planted
	void plantMine();
	// Respawn the tank in the starting location
	void respawn();
	// Return the player of the tank.
	Score::PLAYER getPlayer();
	// Turn the tank invisible
	void turnInvisible();
	// Check if the tank is invisible
	bool isInvisible();
private:
	// Private member variables.
	const float _pi;
	float _velocityModifier;
	float _angleModifier;
	int _allowedMines;
	int _allowedInvis;
	Vector2D _spawnLocation;
	Vector2D _screenDimensions;
	Score::PLAYER _player;
	clock_t _invisibilityTimer;
};

#endif /* TANK_H_ */
