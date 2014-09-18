#ifndef TANK_H_
#define TANK_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <ctime>
#include "DrawableObject.h"
#include "Angle.h"

using namespace sf;

class Tank : public DrawableObject
{
public:
	// Enumerations for control.
	enum Movement{NONE = 0, FORWARD, BACKWARD};
	enum Direction{STRAIGHT = 0, CLOCKWISE, ANTICLOCKWISE};
	// Public access functions.
	Tank(Vector2f position);
	// Virtual functions from Drawable
	virtual float getDirection();
	virtual Vector2f getPosition();
	virtual RectSize getSize();
	// Destructor for the tank.
	virtual ~Tank() {}
	// Overloaded functions for moving the tank object
	void setMovement(Movement movement, float Magnitude = 6.f);
	void setMovement(Direction direction, float Magnitude = 4.f);
	// Vertexes of tank.
	Vector2f frontLeft();
	Vector2f frontRight();
	Vector2f backLeft();
	Vector2f backRight();
private:
	// Private member variables.
	Vector2f _position;
	RectSize _size;
	Angle _direction;
	float _pi;
	float _cornerAngle;
	float _cornerDistance;
};

#endif /* TANK_H_ */
