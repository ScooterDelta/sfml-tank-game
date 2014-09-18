#include "Angle.h"

Angle::Angle() :
	_pi{atan(1) * 4}
{
	_angle = 0;
}

Angle::Angle(float angle):
	_pi{atan(1) * 4}
{
	while(angle >= 360)
		angle -= 360;

	while(angle < 0)
		angle += 360;

	_angle = angle;
}

Angle::Angle(const Angle & angle):
	_pi{atan(1) * 4}
{
	_angle = angle._angle;
}

Angle & Angle::operator=(const Angle & rhs)
{
	this->_angle = rhs._angle;
	return *this;
}

Angle & Angle::operator=(float rhs)
{
	this->_angle = rhs;

	while(this->_angle >= 360)
		this->_angle -= 360;

	while(this->_angle < 0)
		this->_angle += 360;

	return *this;
}

Angle & Angle::operator+=(const Angle & rhs)
{
	this->_angle += rhs._angle;

	while(this->_angle >= 360)
		this->_angle -= 360;

	while(this->_angle < 0)
		this->_angle += 360;

	return *this;
}

Angle & Angle::operator-=(const Angle & rhs)
{
	this->_angle -= rhs._angle;

	while(this->_angle >= 360)
		this->_angle -= 360;

	while(this->_angle < 0)
		this->_angle += 360;

	return *this;
}

Angle & Angle::operator+=(float rhs)
{
	this->_angle += rhs;

	while(this->_angle >= 360)
		this->_angle -= 360;

	while(this->_angle < 0)
		this->_angle += 360;

	return *this;
}

Angle & Angle::operator-=(float rhs)
{
	this->_angle -= rhs;

	while(this->_angle >= 360)
		this->_angle -= 360;

	while(this->_angle < 0)
		this->_angle += 360;

	return *this;
}

float Angle::getAngle()
{
	return _angle;
}

float Angle::getAngleRadians()
{
	return _angle/180 * _pi;
}
