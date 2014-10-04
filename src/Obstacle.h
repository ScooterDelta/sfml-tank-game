// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Obstacle.h

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "AxisAligned.h"

//! Obstacle class, inherits from AxisAligned.
/*!
 * Class for handling the obstacles on the screen, different from normal Axis Aligned
 * objects because the position is the top left corner, not the center.
 */
class Obstacle : public AxisAligned
{
public:
	// Overloaded inherited functions and constructor.
	//! Enum defining the type of texture the obstacle will use.
	/*!
	 * Two type of obstacles are used in the game, bricks and boxes, this enum
	 * helps to define one for each obstacle object.
	 */
	enum TEXTURE{
		BRICK = 0,	//!< Texture type Brick.
		BOX			//!< Texture type Box.
	};
	//! Obstacle constructor.
	/*!
	 * The obstacle is initialized with a certain position and the size of the window,
	 * since the obstacles size is a fraction of the window size (32 by 16 obstacles on a window).
	 * \param position The position (top left corner) of the obstacle.
	 * \param windowSize The size of the window.
	 * \param texture The type of texture for this obstacle.
	 */
	Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture);
	//! Destructor.
	virtual ~Obstacle() {}

	// Functions for which texture to display in display class.
	//! Returns the number of hits remaining on the obstacle.
	/*!
	 * The Obstacle should be destroyed after the number of remaining hits reaches 0.
	 */
	int remainingHits();
	//! Checks if the obstacle object is destroyable.
	/*!
	 * If the number of remaining hits reaches 0 then the object is destroyable,
	 * this function will decrement the remaining hits since it treats it as taking
	 * a hit.
	 */
	bool isDestroyable();
	//! Returns the type of texture for the obstacle.
	TEXTURE getTexture();

	// Overload inherited functions.
	//! Overloaded virtual function inherited from AxisAligned.
	virtual Vector2D getTopLeft();
	//! Overloaded virtual function inherited from AxisAligned.
	virtual Vector2D getBottomRight();

private:
	// Private member variables
	int _remainingHits;
	TEXTURE _texture;
};



#endif /* OBSTACLE_H_ */
