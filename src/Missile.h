#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Angle.h"
#include "DrawableObject.h"

using namespace sf;

class Missile : public DrawableObject
{
public:
	// Constructor
	Missile(Vector2f location, float direction);
	virtual ~Missile();
	// Functions inherited from Drawable
	virtual float getDirection();
	virtual Vector2f getPosition();
	virtual RectSize getSize();
	// Update missile object
	void update();
	// Check if missile is Destroyable.
	bool isDestroyable(bool isHorizontal);
private:
	// Private member variables
	// Private member variables.
	Vector2f _velocity;
	Vector2f _position;
	RectSize _size;
	Angle _direction;
	float _pi;
	float _collisions;
	float _velocityModifier;

	// Private helper functions
	bool isDestroyCone(float cone = 5);
};

#endif /* MISSILE_H_ */
