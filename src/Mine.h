#ifndef MINE_H_
#define MINE_H_

#include <SFML/Graphics.hpp>
#include "DrawableObject.h"

class Mine : public DrawableObject
{
public:
	~Mine(){}
	Mine(Vector2f position);
	// Return the direction the object is facing.
	virtual float getDirection();
	// Return the position of the object.
	virtual Vector2f getPosition();
	// Return the size of the object
	virtual RectSize getSize();
private:
	// Private member variables
	Angle _direction;
	Vector2f _position;
	RectSize _size;
};




#endif /* MINE_H_ */
