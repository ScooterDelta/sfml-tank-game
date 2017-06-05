// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - AxisAligned.h

#ifndef AXISALIGNED_H_
#define AXISALIGNED_H_

#include "DrawableObject.h"

namespace game::domain {

//! Base class for Axis Aligned objects.
/*!
 * This class allows for easy implementation of objects that are axis aligned
 * in the game.
 */
    class AxisAligned : public DrawableObject {
    public:
        //! Axis Aligned constructor.
        /*!
         * This constructor will initialize the position, direction and size of the object.
         * The direction is for display purposes since the hit box is treated as axis aligned.
         *
         * \param location This is the position of the object.
         * \param direction This is the direction for the object to face.
         * \param size The size of the object, of type RectSize(float Width, float Height).
         */
        AxisAligned(Vector2D location, float direction, RectSize size) :
                DrawableObject{location, direction, size} {}

        //! Return the top left corner of the object (virtual function).
        /*!
         * Return the position of the top left corner of the object, as a vector
         * with the x and y magnitudes.
         */
        virtual Vector2D getTopLeft() {
            Vector2D tempPos{DrawableObject::getPosition()};
            RectSize tempRect{DrawableObject::getSize()};

            tempPos.x -= tempRect.Width / 2;
            tempPos.y -= tempRect.Height / 2;

            return tempPos;
        }

        //! Return the bottom right corner of the object (virtual function).
        /*!
         * Return the position of the bottom right corner of the object, as a vector
         * with the x and y magnitudes.
         */
        virtual Vector2D getBottomRight() {
            Vector2D tempPos{DrawableObject::getPosition()};
            RectSize tempRect{DrawableObject::getSize()};

            tempPos.x += tempRect.Width / 2;
            tempPos.y += tempRect.Height / 2;

            return tempPos;
        }
    };
}

#endif /* AXISALIGNED_H_ */
