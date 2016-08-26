// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - nonAxisAligned.h

#ifndef NONAXISALIGNED_H_
#define NONAXISALIGNED_H_

#include "DrawableObject.h"

//! Non Axis Aligned base class.
/*!
 * Objects derived from this class are not aligned to the axis,
 * their hit box is dependant on the direction that they face.
 */
class nonAxisAligned : public DrawableObject
{
public:
	//! nonAxisAligned constructor.
	/*!
	 * The object is initialized to a location and direction, with a
	 * particular size.
	 * \param position The location of the object.
	 * \param direction The direction the object is facing.
	 * \param size The size of the object.
	 */
	nonAxisAligned(Vector2D position, float direction, RectSize size) :
		DrawableObject(position, direction, size),
		_pi{(const float) (atan(1) * 4)}
	{
		_cornerDistance = (float) sqrt(pow(_size.Height / 2, 2) + pow(_size.Width / 2, 2));
		_cornerAngle = (float) (atan(_size.Height / _size.Width) * 180 / _pi);
	}

	//! Virtual function - Returns the front left corner of the object.
	/*!
	 * Returns a Vector2D representing the front left corner of the object.
	 */
	virtual Vector2D getFrontLeft(){
		// Calculate the location of the front left corner of the object
		float xLocation = (float) (DrawableObject::getPosition().x -
                        _cornerDistance * cos((DrawableObject::getDirection() - _cornerAngle) * _pi / 180));
		float yLocation = (float) (DrawableObject::getPosition().y -
                        _cornerDistance * sin((DrawableObject::getDirection() - _cornerAngle) * _pi / 180));

		return Vector2D{xLocation, yLocation};
	}

	//! Virtual function - Returns the front right corner of the object.
	/*!
	 * Returns a Vector2D representing the front right corner of the object.
	 */
	virtual Vector2D getFrontRight(){
		// Calculate the location of the front right corner of the tank
		float xLocation = (float) (DrawableObject::getPosition().x -
                        _cornerDistance * cos((DrawableObject::getDirection() + _cornerAngle) * _pi / 180));
		float yLocation = (float) (DrawableObject::getPosition().y -
                        _cornerDistance * sin((DrawableObject::getDirection() + _cornerAngle) * _pi / 180));

		return Vector2D{xLocation, yLocation};
	}

	//! Virtual function - Returns the back left corner of the object.
	/*!
	 * Returns a Vector2D representing the back left corner of the object.
	 */
	virtual Vector2D getBackLeft(){
		// Calculate the location of the back left corner of the tank
		float xLocation = (float) (DrawableObject::getPosition().x -
                        _cornerDistance * cos((180 + DrawableObject::getDirection() + _cornerAngle) * _pi / 180));
		float yLocation = (float) (DrawableObject::getPosition().y -
                        _cornerDistance * sin((180 + DrawableObject::getDirection() + _cornerAngle) * _pi / 180));

		return Vector2D{xLocation, yLocation};
	}

	//! Virtual function - Returns the back left corner of the object.
	/*!
	 * Returns a Vector2D representing the back right corner of the object.
	 */
	virtual Vector2D getBackRight(){
		// Calculate the location of the back right corner of the tank
		float xLocation = (float) (DrawableObject::getPosition().x -
                        _cornerDistance * cos((180 + DrawableObject::getDirection() - _cornerAngle) * _pi / 180));
		float yLocation = (float) (DrawableObject::getPosition().y -
                        _cornerDistance * sin((180 + DrawableObject::getDirection() - _cornerAngle) * _pi / 180));

		return Vector2D{xLocation, yLocation};
	}

protected:
	//! Stores the constant value of pi for trig calculations.
	const float _pi;
	//! Stores the distance to the corner of the object from the center.
	/*!
	 * This is used in calculating the locations of the corners relative to a particular direction.
	 */
	float _cornerDistance;
	//! Stores the size of the angle from the center to the corner of the object.
	/*!
	 * This is used in calculating the locations of the corners relative to a particular direction.
	 */
	float _cornerAngle;
};



#endif /* NONAXISALIGNED_H_ */
