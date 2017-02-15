// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Tank.h

#ifndef TANK_H_
#define TANK_H_

#include <ctime>
#include "NonAxisAligned.h"
#include "Score.h"

using namespace sf;

//! Tank class, inherits from nonAxisAligned.
/*!
 * This class stores the location and utility functions for the
 * tank objects.
 */
class Tank : public NonAxisAligned
{
public:
	// Enumerations for control.
	//! Enum defining the possible movements for the tank.
	enum Movement{
		NONE = 0,	//!< Make no movement.
		FORWARD,	//!< Make a forward movement.
		BACKWARD,	//!< Make a backward movement.
		FORWARDOBSTACLE,	//!< Calling movement into obstacle (used to make tank move along tank).
		BACKWARDOBSTACLE	//!< Calling movement into obstacle (used to make tank move along tank).
	};
	//! Enum defining the possible directions for the tank.
	enum Direction{
		STRAIGHT = 0,	//!< Dont rotate the tank.
		CLOCKWISE,		//!< Rotate the tank clockwise.
		ANTICLOCKWISE	//!< Rotate the tank anticlockwise.
	};
	// Public access functions.
	//! Tank constructor.
	/*!
	 * Initializes the location and player that the tank belongs to, by default the tank spawns
	 * facing upwards. The location is stored so that the tank will respawn in that position.
	 * \param position The location that the tank will spawn.
	 * \param player The PLAYER that the tank belongs to.
	 * \param ScreenSize The size of the screen, used to scale the hit box based on screen size.
	 */
	Tank(Vector2D position, Score::PLAYER player, Vector2D ScreenSize = {1600.f, 900.f});
	// Destructor for the tank.
	//! Destructor.
	virtual ~Tank() {}
	// Overloaded functions for moving the tank object
	//! Move the tank in a direction.
	/*!
	 * The tank will accelerate in the movement specified, up to a maximum speed of Magnitude,
	 * if the collision functions are called then isHorizontal is used to determine what
	 * motion is allowed.
	 * \param movement Type of Movement the tank should make.
	 * \param isHorizontal If the tank is colliding with an object is it horizontal or not.
	 * \param Magnitude The maximum velocity the tank can accelerate to.
	 */
	void setMovement(Movement movement, bool isHorizontal = false, float Magnitude = 6.f);
	//! Rotate the tank in a particular direciton.
	/*
	 * The tank will rotate with an angular acceleration in the Direction specified,
	 * up to a maximum angular velocity of Magnitude.
	 * \param direction The Direction that the tank will rotate in.
	 * \param Magnitude The maximum angular velocity that the tank can rotate at.
	 */
	void setMovement(Direction direction, float Magnitude = 4.f);

    // Return number of mines remaining.
	//! Return the number of mines the tank is allowed to place.
	int getAllowedMines();
	// Decrement mines since one is planted
	//! Call the function if the tank plants a mine.
	/*!
	 * This function will decrease the number of mines the tank
	 * is still allowed to place.
	 */
	void plantMine();
	// Respawn the tank in the starting location
	//! Respawn the tank, reseting it's ammo, and reseting its position and direction.
	/*!
	 * The default values for the position and direction can be changed with
	 * setSpawn(Vector2D location, float direction = 90).
	 * \sa setSpawn(Vector2D location, float direction = 90)
	 */
	void respawn();
	// Return the player of the tank.
	//! Return the player that the tank belongs to.
	Score::PLAYER getPlayer();
	// Turn the tank invisible
	//! Turn the tank invisible.
	void turnInvisible();
	// Check if the tank is invisible
	//! Check if the tank is invisible.
	bool isInvisible();
private:
	// Private member variables.
	//! Value of pi for calculations.
	const float _pi;
	//! Value of the magnitude of velocity.
	float _velocityModifier;
	//! Value of the magnitude of angular rotation.
	float _angleModifier;
	//! Number of mines the tank is allowed to place.
	int _allowedMines;
	//! Check if the tank is still allowed to turn invisible.
	int _allowedInvis;
	//! The direction that the tank will respawn in.
	float _spawnDirection;
	//! The location that the tank will respawn in.
	Vector2D _spawnLocation;
	//! The PLAYER that the Tank belongs to.
	Score::PLAYER _player;
	//! Time how long the tank can be invisible for.
	clock_t _invisibilityTimer;
};

#endif /* TANK_H_ */
