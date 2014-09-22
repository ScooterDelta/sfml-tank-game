#include "Explosion.h"

Explosion::Explosion(Vector2D position):
_position{position},
_explosionTimer{clock()}
{
	_size.Width = 0;
	_size.Height = 0;
}

Vector2D Explosion::getPosition(){
	return _position;
}

RectSize Explosion::getSize(){
	return _size;
}
//

clock_t Explosion::getExplosionTime(){
	return _explosionTimer;
}

