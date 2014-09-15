#ifndef RECTANGLEOBJECT_H_
#define RECTANGLEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "DrawableObject.h"

using namespace sf;

class RectangleObject : public DrawableObject
{
public:
	virtual ~RectangleObject() {}
	virtual Vector2f frontLeft() = 0;
	virtual Vector2f frontRight() = 0;
	virtual Vector2f backLeft() = 0;
	virtual Vector2f backRight() = 0;

private:
	// No private members
};



#endif /* RECTANGLEOBJECT_H_ */
