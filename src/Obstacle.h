// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Obstacle.h

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "DrawableObject.h"

class Obstacle : public DrawableObject
{
public:
	// Overloaded inherited functions and constructor.
	enum TEXTURE{BRICK = 0, BOX};
	Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture);
	virtual ~Obstacle() {}
	virtual float getDirection();
	virtual Vector2D getPosition();
	virtual RectSize getSize();

	// Functions for which texture to display in display class.
	int remainingHits();
	bool isDestroyable();
	TEXTURE getTexture();

	// Return the dimensions of the obstacle.
	Vector2D topLeft();
	Vector2D topRight();
	Vector2D bottomLeft();
	Vector2D bottomRight();

private:
	// Private member variables
	float _direction;
	Vector2D _position;
	RectSize _size;
	int _remainingHits;
	TEXTURE _texture;
};



#endif /* OBSTACLE_H_ */
