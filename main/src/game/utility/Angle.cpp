// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Angle.cpp

#include "Angle.h"

namespace game {
namespace utility {

// Constructors:
Angle::Angle() :
        _pi{(float) (atan(1) * 4)} {
    _angle = 0;
}

Angle::Angle(float angle) :
        _pi{(float) (atan(1) * 4)} {
    while (angle >= 360)
        angle -= 360;

    while (angle < 0)
        angle += 360;

    _angle = angle;
}

Angle::Angle(const Angle &angle) :
        _pi{(float) (atan(1) * 4)} {
    _angle = angle._angle;
}

// Operators:
Angle &Angle::operator=(const Angle &rhs) {
    this->_angle = rhs._angle;
    return *this;
}

Angle &Angle::operator=(float rhs) {
    this->_angle = rhs;

    while (this->_angle >= 360)
        this->_angle -= 360;

    while (this->_angle < 0)
        this->_angle += 360;

    return *this;
}

Angle &Angle::operator+=(const Angle &rhs) {
    this->_angle += rhs._angle;

    while (this->_angle >= 360)
        this->_angle -= 360;

    while (this->_angle < 0)
        this->_angle += 360;

    return *this;
}

Angle &Angle::operator-=(const Angle &rhs) {
    this->_angle -= rhs._angle;

    while (this->_angle >= 360)
        this->_angle -= 360;

    while (this->_angle < 0)
        this->_angle += 360;

    return *this;
}

Angle &Angle::operator+=(float rhs) {
    this->_angle += rhs;

    while (this->_angle >= 360)
        this->_angle -= 360;

    while (this->_angle < 0)
        this->_angle += 360;

    return *this;
}

Angle &Angle::operator-=(float rhs) {
    this->_angle -= rhs;

    while (this->_angle >= 360)
        this->_angle -= 360;

    while (this->_angle < 0)
        this->_angle += 360;

    return *this;
}

bool Angle::operator==(const Angle &rhs) {
    return (_angle == rhs._angle);
}

bool Angle::operator==(float rhs) {
    while (rhs >= 360)
        rhs -= 360;

    while (rhs < 0)
        rhs += 360;

    return (_angle == rhs);
}

bool Angle::operator>=(const Angle &rhs) {
    return (_angle >= rhs._angle);
}


bool Angle::operator>=(float rhs) {
    while (rhs >= 360)
        rhs -= 360;

    while (rhs < 0)
        rhs += 360;

    return (_angle >= rhs);
}

bool Angle::operator<=(const Angle &rhs) {
    return (_angle <= rhs._angle);
}

bool Angle::operator<=(float rhs) {
    while (rhs >= 360)
        rhs -= 360;

    while (rhs < 0)
        rhs += 360;

    return (_angle <= rhs);
}

bool Angle::operator>(const Angle &rhs) {
    return (_angle > rhs._angle);
}

bool Angle::operator>(float rhs) {
    while (rhs >= 360)
        rhs -= 360;

    while (rhs < 0)
        rhs += 360;

    return (_angle > rhs);
}

bool Angle::operator<(const Angle &rhs) {
    return (_angle < rhs._angle);
}

bool Angle::operator<(float rhs) {
    while (rhs >= 360)
        rhs -= 360;

    while (rhs < 0)
        rhs += 360;

    return (_angle < rhs);
}

// Getters:
float Angle::getAngle() {
    return _angle;
}

float Angle::getAngleRadians() {
    return _angle / 180 * _pi;
}

}
}
