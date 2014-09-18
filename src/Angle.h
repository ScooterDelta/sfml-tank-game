#ifndef ANGLE_H_
#define ANGLE_H_

// Class to hold an angle, can only exist
// between (equal to) 0 and (not equal to) 360 degrees.
class Angle
{
public:
	// Initializers
	Angle();
	Angle(float angle);
	Angle(const Angle & angle);

	// Operators
	Angle & operator=(const Angle & rhs);
	Angle & operator=(float rhs);
	Angle & operator+=(const Angle & rhs);
	Angle & operator-=(const Angle & rhs);
	Angle & operator+=(float rhs);
	Angle & operator-=(float rhs);

	float getAngle();
private:
	float _angle;
};



#endif /* ANGLE_H_ */
