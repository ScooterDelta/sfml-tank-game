// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Turret.h

#ifndef TURRET_H_
#define TURRET_H_

#include "AxisAligned.h"
#include <cmath>
#include <ctime>

namespace game {
namespace domain {

//! Turret class, inherits from AxisAligned.
/*!
 * The Turret class stores the values required for turret, and
 * functions to check it's state.
 */
class Turret : public AxisAligned {
public:
    //! Destructor.
    ~Turret() {}
    //! Turret Constructor.
    /*!
     * The turret is initialized to a particular position and with a range
     * for the turret to sweep looking for enemies to shoot.
     * \param position The position of the turret.
     * \param range The range for the turret to sweep.
     * \param screenSize The size of the screen, used to scale the turret hitbox.
     */
    Turret(Vector2D position, Vector2D range, Vector2D screenSize);
    //! Check if the turret can follow the target.
    /*!
     * Checks if the target is inside the turrets lock on area and range,
     * if it is then the turret will track it.
     * \param target The target that needs to be checked.
     * \param TargetInvisible The turret will not track the target if it is invisible.
     */
    bool canFollowTarget(DrawableObject &target, bool TargetInvisible = false);
    //! Update the turret.
    /*!
     * The function that will make the turret sweep the area,
     * looking for a target to lock onto.
     */
    void update();

    //! Return the location of the front of the barrel.
    /*!
     * This returns a vector representing the location of the front of the barrel
     * of the turret, so that a missile may be fired from it.
     */
    Vector2D getFirePosition();
    //! Check if the turret can fire a missile.
    /*!
     * The turret may not fire too many missiles in too short of a time,
     * so a timer limits the fire rate.
     */
    bool canFireMissile();

private:
    // Private member variables
    //! The range that the turret will rotate throught.
    Vector2D _range;
    //! Value of pi used for calculations.
    const float _pi;
    //! The direction of rotation for the turret.
    /*!
     * The turret will rotate clockwise and anticlockwise between the
     * min and max values of the range.
     */
    bool _isClockwise;
    //! Amount of time between firing missiles.
    clock_t _fireTime;
    //! The maximum distance for the turret to see a Tank.
    float _lockDistance;
};

}
}

#endif /* TURRET_H_ */
