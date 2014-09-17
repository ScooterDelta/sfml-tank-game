#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

struct RectSize{
	float Height;
	float Width;

	RectSize(){
		Width = 0;
		Height = 0;
	}

	RectSize(float width, float height){
		Width = width;
		Height = height;
	}

	RectSize & operator=(const RectSize &rhs){
		this->Height = rhs.Height;
		this->Width = rhs.Width;
		return *this;
	}
};

class DrawableObject
{
public:
	virtual float getDirection(){
		return _direction;
	}

	virtual Vector2f getPosition(){
		return _position;
	}

	virtual RectSize getSize(){
		return _size;
	}

	virtual ~DrawableObject() {}
private:
	// Private member variables
	float _direction;
	Vector2f _position;
	RectSize _size;
};



#endif /* DRAWABLEOBJECT_H_ */
