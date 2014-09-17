#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
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
	// Update
	void update();
private:
	// Private member variables
	// Private member variables.
	Vector2f _velocity;
	Vector2f _position;
	RectSize _size;
	float _direction;
	float _pi;
};

#endif /* MISSILE_H_ */
