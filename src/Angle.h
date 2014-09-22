#ifndef ANGLE_H_
#define ANGLE_H_

#include <cmath>

// Class to hold an angle, can only exist
// between (equal to) 0 and (not equal to) 360 degrees.
class Angle
{
public:
	// Initializers
	Angle();
	Angle(float angle);
	Angle(const Angle & angle);

	// Operators.
	Angle & operator=(const Angle & rhs);
	Angle & operator=(float rhs);
	Angle & operator+=(const Angle & rhs);
	Angle & operator-=(const Angle & rhs);
	Angle & operator+=(float rhs);
	Angle & operator-=(float rhs);

	// Equality operators.
	bool operator==(const Angle & rhs);
	bool operator==(float rhs);
	bool operator>=(const Angle & rhs);
	bool operator>=(float rhs);
	bool operator<=(const Angle & rhs);
	bool operator<=(float rhs);
	bool operator>(const Angle & rhs);
	bool operator>(float rhs);
	bool operator<(const Angle & rhs);
	bool operator<(float rhs);

	// Getters:
	float getAngle();
	float getAngleRadians();
private:
	float _angle;
	float _pi;
};



#endif /* ANGLE_H_ */
