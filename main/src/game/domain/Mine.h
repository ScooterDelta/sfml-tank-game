// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Mine.h

#ifndef MINE_H_
#define MINE_H_

#include "DrawableObject.h"
#include "../gameplay/Score.h"

using game::gameplay::Score;

namespace game {
namespace domain {

//! Mine class, inherits from DrawableObject.
/*!
 * This class is used for displaying the mines on the screen,
 * and handling the mine logic.
 */
class Mine : public DrawableObject {
public:
    // Overloaded inherited functions.
    //! Destructor.
    ~Mine() {}
    //! Mine constructor.
    /*!
     * Initializes the position and the owner of the planted mine,
     * it is initialized as an inactive mine.
     * \param position The location of the mine.
     * \param player The player who owns the mine.
     */
    Mine(Vector2D position, Score::PLAYER player);
    // Check is the mine activated
    //! Check if the mine is active or not.
    /*!
     * If the mine is active then it can detonate when passed over by a tank,
     * otherwise it will not detonate.
     */
    bool checkIsActive();
    // Activate the mine.
    //! Set the mines state to active.
    /*!
     * This function will set the mines state to active, meaning the next time
     * an object passes over it, it can be detonated.
     */
    void activateMine();

    // Which player planted the mine
    //! Return the player that planted the mine.
    Score::PLAYER getPlayer();

private:
    // Private member variables
    //! Variable defining if the mine is active or not.
    bool _isActive;
    //! Store the player that the mine belongs to.
    Score::PLAYER _player;
};

}
}

#endif /* MINE_H_ */
