#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <SFML/System.hpp>

class Vector2D
{
public:
	// Constructor.
	Vector2D();
	Vector2D(float X, float Y);
	// Operator overloads.
	Vector2D & operator=(const Vector2D & rhs);
	bool operator==(const Vector2D & rhs);

	// SFML dependent overloads, change this if a different
	// display library is used.
	Vector2D(sf::Vector2f inpt);
	Vector2D & operator=(const sf::Vector2f & rhs);




	float x;
	float y;
};



#endif /* VECTOR2D_H_ */
