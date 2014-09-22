#include "Vector2D.h"

Vector2D::Vector2D():
	x{0},
	y{0}
{}

Vector2D::Vector2D(float X, float Y):
	x{X},
	y{Y}
{}

Vector2D::Vector2D(const Vector2D & inpt):
	x{inpt.x},
	y{inpt.y}
{}

Vector2D & Vector2D::operator=(const Vector2D & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;

	return * this;
}

bool Vector2D::operator==(const Vector2D & rhs)
{
	return (this->x == rhs.x && this->y == rhs.y);
}

// SFML dependant functions.
Vector2D::Vector2D(sf::Vector2f inpt):
	x{inpt.x},
	y{inpt.y}
{}

Vector2D & Vector2D::operator=(const sf::Vector2f & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;

	return * this;
}
