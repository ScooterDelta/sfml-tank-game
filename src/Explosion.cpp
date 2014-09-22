// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Explosion.cpp

#include "Explosion.h"

// Constructor:
Explosion::Explosion(Vector2D position):
_position{position},
_explosionTimer{clock()}
{
	_size.Width = 0;
	_size.Height = 0;
}

// Return the position of the explostion.
Vector2D Explosion::getPosition(){
	return _position;
}

RectSize Explosion::getSize(){
	return _size;
}

// Return the time of the explosion.
clock_t Explosion::getExplosionTime(){
	return _explosionTimer;
}

