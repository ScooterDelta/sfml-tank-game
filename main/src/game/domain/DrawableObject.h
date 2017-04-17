// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - DrawableObject.h

#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

#include "../utility/Vector2D.h"
#include "../utility/Angle.h"
#include <cmath>

using namespace sf;

using game::utility::Vector2D;
using game::utility::Angle;

namespace game {
namespace domain {

// Structure for the size of the object.
//! Struct to define the size of an object.
/*!
 * This struct defines the length and breadth of a rectangular shaped object.
 */
struct RectSize {
    //! The height of the rectangle object.
    float Height;
    //! The width of the rectangle object.
    float Width;
    // Empty initializer.
    //! Empty initializer.
    /*!
     * When this initializer is called the width and height are initialized to 0.
     */
    RectSize() {
        Width = 0;
        Height = 0;
    }
    // Overloaded initializer.
    //! Copy constructor.
    /*!
     * Copies the width and height from the input to the new object.
     * \param inpt The RectSize object that is being copied.
     */
    RectSize(const RectSize &inpt) {
        Width = inpt.Width;
        Height = inpt.Height;
    }

    //! Overloaded constructor.
    /*!
     * Loads the object with a particular width and height.
     */
    RectSize(float width, float height) {
        Width = width;
        Height = height;
    }
    // Equals overloading.
    //! Copy operator.
    /*!
     * Copies the width and height of the input object.
     * \param rhs The object that is being copied.
     */
    RectSize &operator=(const RectSize &rhs) {
        this->Height = rhs.Height;
        this->Width = rhs.Width;
        return *this;
    }
};

//! Base class for drawable game objects.
/*!
 * The derived objects must have returnable positions, directions and sizes in order
 * to be drawn on the screen.
 */
class DrawableObject {
public:
    //! DrawableObject constructor.
    /*!
     * Initializes the position, direction and size of the drawable object.
     * \param position The location of the object.
     * \param direction The direction the object is facing.
     * \param size The size of the object as a RectSize object.
     */
    DrawableObject(Vector2D position, float direction, RectSize size) :
            _direction{direction},
            _position{position},
            _size{size} {}

    // Return the direction the object is facing.
    //! Virtual function returning the direction.
    /*!
     * Virtual function, returns the direction the object is facing as a
     * float.
     */
    virtual float getDirection() {
        return _direction.getAngle();
    }
    // Return the position of the object.
    //! Virtual function returning the position of the object.
    /*
     * Virtual function, returns the position of the object
     * as a Vector2D.
     */
    virtual Vector2D getPosition() {
        return _position;
    }
    // Return the size of the object
    //! Return the size of the object.
    /*!
     * Virtual function, returns the size of the object as
     * a RectSize object.
     */
    virtual RectSize getSize() {
        return _size;
    }

    // Destructor.
    //! Destructor.
    virtual ~DrawableObject() {}

protected:
    // Private member variables
    //! Stores the direction the object is facing.
    Angle _direction;
    //! Stores the position of the object.
    Vector2D _position;
    //! Stores the size of the object.
    RectSize _size;
};

}
}

#endif /* DRAWABLEOBJECT_H_ */
