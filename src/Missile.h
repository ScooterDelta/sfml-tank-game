// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Missile.h

#ifndef MISSILE_H_
#define MISSILE_H_

#include <cmath>
#include "DrawableObject.h"
#include "Score.h"

using namespace sf;

//! Missile utility class, inherits from DrawableObject.
/*!
 * This class is used to store the location and direction of the missile,
 * and handle it's movement accross the screen.
 */
class Missile : public DrawableObject
{
public:
	// Constructor
	// Missile constructor.
	/*!
	 * The missile is initialized in a particular position with a direction, it is scaled with the window size.
	 * \param location The location the missile is fired from.
	 * \param direction The direction that the missile is fired in.
	 * \param player The player who fired the missile.
	 * \param windowSize The size of the game window (sf::RenderWindow).
	 */
	Missile(Vector2D location, float direction, Score::PLAYER player);
	//! Destructor.
	virtual ~Missile();
	// Update missile object
	//! Update the missile object.
	/*!
	 * The update function will update the location of the missile by moving it forward,
	 * in the direction specified in the constructor.
	 */
	void update();
	// Check if missile is Destroyable.
	//! Check if the missile is destroyable.
	/*!
	 * Call this function when the missile hits another object, it will return
	 * if the missile has bounced enough to be destroyed, if not its bounces will be
	 * decreased.
	 */
	bool isDestroyable(bool isHorizontal);
	// Check which player the missile was fired from
	//! Check which player the missile belongs do.
	Score::PLAYER getPlayer();
private:
	// Private member variables
	//! The velocity that the missile moves in.
	/*!
	 * The velocity is stored as a Vector2D,
	 * defining the x and y parameters of it's movement.
	 */
	Vector2D _velocity;
	//! Value of pi for calculations.
	const float _pi;
	//! The number of collisions remaining for the missile.
	float _collisions;
	//! The magnitude of the velocity vector.
	float _velocityModifier;
	//! The PLAYER that the missile belongs to.
	Score::PLAYER _player;

	// Private helper functions
	//! Check if the missile is inside a destroyable cone.
	/*!
	 * This checks if the missile was fired directly at a wall,
	 * if so the missile will not down and will be instantly destroyed.
	 */
	bool isDestroyCone(bool isHorizontal, float cone = 3);
};

#endif /* MISSILE_H_ */
