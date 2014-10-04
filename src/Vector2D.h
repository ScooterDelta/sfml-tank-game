// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Vector2D.h

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <SFML/System.hpp>

//! Utility class for storing 2 Dimensional Vectors.
/*!
 * A utility class to store a 2 dimension vector, used to
 * Separate game logic requiring 2D vectors from SFML, but keeping
 * the containers compatible.
 */
class Vector2D
{
public:
	// Constructor.
	//! Default constructor.
	/*!
	 * Initializes the x and y parameters to 0.
	 */
	Vector2D();
	//! Overloaded constructor.
	/*!
	 * Initializes the x and y parameters to the values passed in.
	 * \param X The value that x will be initialized to.
	 * \param Y The value that y will be initialized to.
	 */
	Vector2D(float X, float Y);
	//! Copy constructor.
	/*!
	 * The values for x and y are copied from the input argument.
	 * \param inpt The Vector2D object to be copied.
	 */
	Vector2D(const Vector2D & inpt);
	// Operator overloads.
	//! Copy operator.
	/*!
	 * The operator will copy the x and y values of the input argument
	 * into this object.
	 * \param rhs The argument to be copied.
	 */
	Vector2D & operator=(const Vector2D & rhs);
	//! Equality operator.
	/*!
	 * Check that the value of the object is equal to that of the input,
	 * compares the value of x and y in both.
	 * \param rhs The argument to be compared.
	 */
	bool operator==(const Vector2D & rhs);

	// SFML dependent overloads, change this if a different
	// display library is used.
	//! Copy constructor for SFML Vector2f.
	/*!
	 * In order to make the Vector2D object compatible with SFML the copy
	 * constructor is provided, if a different graphics package is used,
	 * then this function can be modified or removed.
	 * \param inpt The SFML Vector2f to be copied.
	 */
	Vector2D(sf::Vector2f inpt);
	//! Copy operator for SFML Vector2f.
	/*!
	 * In order to make the Vector2D object compatible with SFML the copy
	 * constructor is provided, if a different graphics package is used,
	 * then this function can be modified or removed.
	 * \param rhs The SFML Vector2f to be copied.
	 */
	Vector2D & operator=(const sf::Vector2f & rhs);

	// Data containers for the Vector class.
	//! The x coordinate of the vector.
	float x;
	//! The y coordinate of the vector.
	float y;
};



#endif /* VECTOR2D_H_ */
