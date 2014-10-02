#ifndef AXISALIGNED_H_
#define AXISALIGNED_H_

#include "DrawableObject.h"

class AxisAligned : public DrawableObject
{
public:
	AxisAligned(Vector2D location, float direction, RectSize size) :
		DrawableObject{location, direction, size}
	{}

	virtual Vector2D getTopLeft(){
		Vector2D tempPos{DrawableObject::getPosition()};
		RectSize tempRect{DrawableObject::getSize()};

		tempPos.x -= tempRect.Width/2;
		tempPos.y -= tempRect.Height/2;

		return tempPos;
	}

	virtual Vector2D getBottomRight(){
		Vector2D tempPos{DrawableObject::getPosition()};
		RectSize tempRect{DrawableObject::getSize()};

		tempPos.x += tempRect.Width/2;
		tempPos.y += tempRect.Height/2;

		return tempPos;
	}
};


#endif /* AXISALIGNED_H_ */
