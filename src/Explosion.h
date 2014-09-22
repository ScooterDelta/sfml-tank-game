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

	virtual Vector2D getPosition();
	virtual RectSize getSize();
	// get the explosion time, allowing for the explosions to be persistant.
	clock_t getExplosionTime();
private:
	// Private member variables
	Vector2D _position;
	RectSize _size;
	clock_t _explosionTimer;
};

#endif /* EXPLOSION_H_ */
