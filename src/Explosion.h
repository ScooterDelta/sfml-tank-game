// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Explosion.h

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "DrawableObject.h"
#include <ctime>

class Explosion : public DrawableObject
{
public:
	// Overloading inherited functions.
	virtual ~Explosion() {}
	Explosion(Vector2D position);

	// get the explosion time, allowing for the explosions to be persistant.
	clock_t getExplosionTime();
private:
	// Private member variables
	clock_t _explosionTimer;
};

#endif /* EXPLOSION_H_ */
