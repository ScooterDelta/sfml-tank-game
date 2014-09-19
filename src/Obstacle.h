#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "DrawableObject.h"

class Obstacle : public DrawableObject
{
public:
	Obstacle(Vector2f position, Vector2f windowSize);
	virtual ~Obstacle() {}
	virtual float getDirection();
	virtual Vector2f getPosition();
	virtual RectSize getSize();

	int remainingHits();
	bool isDestroyable();

	Vector2f topLeft();
	Vector2f topRight();
	Vector2f bottomLeft();
	Vector2f bottomRight();

private:
	// Private member variables
	float _direction;
	Vector2f _position;
	RectSize _size;
	int _remainingHits;
};



#endif /* OBSTACLE_H_ */
