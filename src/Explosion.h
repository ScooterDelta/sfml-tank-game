// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Explosion.h

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "DrawableObject.h"
#include <ctime>

//! Explosion class, inherits from DrawableObject.
/*!
 * The explosion function is used for drawing explosions on the screen,
 * they have a timed life.
 */
class Explosion : public DrawableObject
{
public:
	// Overloading inherited functions.
	//! Explosion destructor.
	virtual ~Explosion() {}
	//! Explosion constructor.
	/*!
	 * Takes the position that the explosion occurs as a Vector2D.
	 * \param position The location that the explosion occurs.
	 */
	Explosion(Vector2D position);

	// get the explosion time, allowing for the explosions to be persistent.
	//! The time since the explosion occurred.
	/*!
	 * Returns the time since the explosion occurred, this can be used
	 * to ensure the explosion has a timed life.
	 */
	clock_t getExplosionTime();
private:
	// Private member variables
	//! Timer for the life of the explosion.
	clock_t _explosionTimer;
};

#endif /* EXPLOSION_H_ */
