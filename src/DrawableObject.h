// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - DrawableObject.h

#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Vector2D.h"
#include "Angle.h"
#include <cmath>

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
	RectSize(const RectSize & inpt){
		Width = inpt.Width;
		Height = inpt.Height;
	}

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
	DrawableObject(Vector2D position, float direction, RectSize size) :
		_direction{direction},
		_position{position},
		_size{size}
	{}

	// Return the direction the object is facing.
	virtual float getDirection(){
		return _direction.getAngle();
	}
	// Return the position of the object.
	virtual Vector2D getPosition(){
		return _position;
	}
	// Return the size of the object
	virtual RectSize getSize(){
		return _size;
	}
	// Destructor.
	virtual ~DrawableObject() {}
protected:
	// Private member variables
	Angle _direction;
	Vector2D _position;
	RectSize _size;
};

#endif /* DRAWABLEOBJECT_H_ */
