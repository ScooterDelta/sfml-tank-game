#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Angle.h"

using namespace sf;

// Structure for the size of the object.
struct RectSize{
	float Height;
	float Width;
	// Empty initializer.
	RectSize(){
		Width = 0;
		Height = 0;
	}
	// Overloaded initializer.
	RectSize(float width, float height){
		Width = width;
		Height = height;
	}
	// Equals overloading.
	RectSize & operator=(const RectSize &rhs){
		this->Height = rhs.Height;
		this->Width = rhs.Width;
		return *this;
	}
};

class DrawableObject
{
public:
	// Return the direction the object is facing.
	virtual float getDirection(){
		return _direction.getAngle();
	}
	// Return the position of the object.
	virtual Vector2f getPosition(){
		return _position;
	}
	// Return the size of the object
	virtual RectSize getSize(){
		return _size;
	}
	// Destructor.
	virtual ~DrawableObject() {}
private:
	// Private member variables
	Angle _direction;
	Vector2f _position;
	RectSize _size;
};

#endif /* DRAWABLEOBJECT_H_ */
