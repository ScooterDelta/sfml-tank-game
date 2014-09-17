#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "DrawableObject.h"

class Obstacle : public DrawableObject
{
public:
	Obstacle(Vector2f position, RectSize size);
	virtual ~Obstacle() {}
	virtual float getDirection();
	virtual Vector2f getPosition();
	virtual RectSize getSize();

	Vector2f topLeft();
	Vector2f topRight();
	Vector2f bottomLeft();
	Vector2f bottomRight();

private:
	// Private member variables
	float _direction;
	Vector2f _position;
	RectSize _size;
};



#endif /* OBSTACLE_H_ */
