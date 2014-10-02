#ifndef NONAXISALIGNED_H_
#define NONAXISALIGNED_H_

#include "DrawableObject.h"

class nonAxisAligned : public DrawableObject
{
public:
	nonAxisAligned(Vector2D position, float direction, RectSize size) :
		DrawableObject(position, direction, size),
		_pi{atan(1) * 4}
	{
		_cornerDistance = sqrt(pow(_size.Height/2,2) + pow(_size.Width/2,2));
		_cornerAngle = atan(_size.Height/_size.Width) * 180 / _pi;
	}

	virtual Vector2D getFrontLeft(){
		// Calculate the location of the front left corner of the object
		float xLocation = DrawableObject::getPosition().x -
				_cornerDistance * cos((DrawableObject::getDirection() - _cornerAngle) * _pi / 180);
		float yLocation = DrawableObject::getPosition().y -
				_cornerDistance * sin((DrawableObject::getDirection() - _cornerAngle) * _pi / 180);

		return Vector2D{xLocation, yLocation};
	}

	virtual Vector2D getFrontRight(){
		// Calculate the location of the front right corner of the tank
		float xLocation = DrawableObject::getPosition().x -
				_cornerDistance * cos((DrawableObject::getDirection() + _cornerAngle) * _pi / 180);
		float yLocation = DrawableObject::getPosition().y -
				_cornerDistance * sin((DrawableObject::getDirection() + _cornerAngle) * _pi / 180);

		return Vector2D{xLocation, yLocation};
	}

	virtual Vector2D getBackLeft(){
		// Calculate the location of the back left corner of the tank
		float xLocation = DrawableObject::getPosition().x -
				_cornerDistance * cos((180 + DrawableObject::getDirection() + _cornerAngle) * _pi / 180);
		float yLocation = DrawableObject::getPosition().y -
				_cornerDistance * sin((180 + DrawableObject::getDirection() + _cornerAngle) * _pi / 180);

		return Vector2D{xLocation, yLocation};
	}

	virtual Vector2D getBackRight(){
		// Calculate the location of the back right corner of the tank
		float xLocation = DrawableObject::getPosition().x -
				_cornerDistance * cos((180 + DrawableObject::getDirection() - _cornerAngle) * _pi / 180);
		float yLocation = DrawableObject::getPosition().y -
				_cornerDistance * sin((180 + DrawableObject::getDirection() - _cornerAngle) * _pi / 180);

		return Vector2D{xLocation, yLocation};
	}

protected:
	const float _pi;
	float _cornerDistance;
	float _cornerAngle;
};



#endif /* NONAXISALIGNED_H_ */
