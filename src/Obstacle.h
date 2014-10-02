// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Obstacle.h

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "AxisAligned.h"

class Obstacle : public AxisAligned
{
public:
	// Overloaded inherited functions and constructor.
	enum TEXTURE{BRICK = 0, BOX};
	Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture);
	virtual ~Obstacle() {}

	// Functions for which texture to display in display class.
	int remainingHits();
	bool isDestroyable();
	TEXTURE getTexture();

	// Overload inherited functions.
	virtual Vector2D getTopLeft();
	virtual Vector2D getBottomRight();

private:
	// Private member variables
	int _remainingHits;
	TEXTURE _texture;
};



#endif /* OBSTACLE_H_ */
