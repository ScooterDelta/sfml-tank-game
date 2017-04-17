// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Angle.h

#ifndef ANGLE_H_
#define ANGLE_H_

#include <cmath>

namespace game {
namespace utility {

//! Class to hold an Angle.
/*!
 * The angle can only exist between 0 and 360 degrees.
 */
class Angle {
public:
    //! Empty constructor.
    /*!
     * Initializes the Angle to 0 degrees.
     */
    Angle();
    //! Copy constructor type float.
    /*!
     * Initializes the Angle to be the same value as the input,
     * changes the value to it's equivalent angle between 0 and 360 degrees.
     *
     * \param angle Takes the angle for the copy constructor.
     * \sa Angle(), Angle(const Angle & angle)
     */
    Angle(float angle);
    //! Copy constructor type Angle.
    /*!
     * Initializes the Angle to be the same as the input,
     * The value will already be between 0 and 360 degrees.
     *
     * \param angle The angle for the copy constructor.
     * \sa Angle(), Angle(float angle)
     */
    Angle(const Angle &angle);

    // Operators.
    //! Copy operator type Angle.
    //! \param rhs The value the operator is copying.
    Angle &operator=(const Angle &rhs);

    //! Copy operator type float.
    //! \param rhs The value the operator is copying.
    Angle &operator=(float rhs);

    //! Value increment operator type Angle.
    //! \param rhs The value the operator is incrementing by.
    Angle &operator+=(const Angle &rhs);

    //! Value decrement operator type Angle.
    //! \param rhs The value the operator is decrementing by.
    Angle &operator-=(const Angle &rhs);

    //! Value increment operator type float.
    //! \param rhs The value the operator is  incrementing by.
    Angle &operator+=(float rhs);

    //! Value decrement operator type float.
    //! \param rhs The value the operator is decrementing by.
    Angle &operator-=(float rhs);

    // Equality operators.
    //! Equality operator type Angle.
    //! \param rhs The Angle that is compared.
    bool operator==(const Angle &rhs);
    //! Equality operator type float.
    /*!
     * The float is converted to be in the range of 0 to 360 degrees before
     * being compared to the object.
     * \param rhs The float that is compared.
     */
    bool operator==(float rhs);

    //! Greater than equal to operator type Angle.
    //! \param rhs The Angle that is compared.
    bool operator>=(const Angle &rhs);
    //! Equality operator type float.
    /*!
     * The float is converted to be in the range of 0 to 360 degrees before
     * being compared to the object.
     * \param rhs The float that is compared.
     */
    bool operator>=(float rhs);

    //! Less than equal to operator type Angle.
    //! \param rhs The Angle that is compared.
    bool operator<=(const Angle &rhs);
    //! Less than equal to operator type float.
    /*!
     * The float is converted to be in the range of 0 to 360 degrees before
     * being compared to the object.
     * \param rhs The float that is compared.
     */
    bool operator<=(float rhs);

    //! Greater than operator type Angle.
    //! \param rhs The Angle that is compared.
    bool operator>(const Angle &rhs);
    //! Greater than operator type float.
    /*!
     * The float is converted to be in the range of 0 to 360 degrees before
     * being compared to the object.
     * \param rhs The float that is compared.
     */
    bool operator>(float rhs);

    //! Less than operator type Angle.
    //! \param rhs The Angle that is compared.
    bool operator<(const Angle &rhs);
    //! Less than operator type float.
    /*!
     * The float is converted to be in the range of 0 to 360 degrees before
     * being compared to the object.
     * \param rhs The float that is compared.
     */
    bool operator<(float rhs);

    // Getters:
    //! Returns the angle in degrees (as a float).
    /*!
     * The value will only be between 0 and 360 degrees.
     */
    float getAngle();
    //! Returns the angle in radians (as a float).
    /*!
     * The value will only be between 0 and 2 * pi radians.
     */
    float getAngleRadians();

private:
    //! Private variable that stores the angle.
    /*!
     * The angle is stored in degrees.
     */
    float _angle;
    //! Private variable that stores the value of pi.
    /*!
     * This is used to convert between degrees and radians.
     */
    float _pi;
};

}
}

#endif /* ANGLE_H_ */
