#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "DrawableObject.h"
#include <ctime>

class Explosion : public DrawableObject
{
public:
	virtual ~Explosion() {}
	Explosion(Vector2f position);

	virtual Vector2f getPosition();
	virtual RectSize getSize();
	//
	clock_t getExplosionTime();
private:
	// Private member variables
	Vector2f _position;
	RectSize _size;
	clock_t _explosionTimer;
};

#endif /* EXPLOSION_H_ */
