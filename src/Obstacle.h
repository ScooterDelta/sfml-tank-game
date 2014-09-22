#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "DrawableObject.h"

class Obstacle : public DrawableObject
{
public:
	enum TEXTURE{BRICK = 0, BOX};
	Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture);
	virtual ~Obstacle() {}
	virtual float getDirection();
	virtual Vector2D getPosition();
	virtual RectSize getSize();

	int remainingHits();
	bool isDestroyable();
	TEXTURE getTexture();

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
