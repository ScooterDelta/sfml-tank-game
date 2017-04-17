// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Mine.cpp

#include "Mine.h"

namespace game {
namespace domain {

Mine::Mine(Vector2D position, Score::PLAYER player) :
        DrawableObject{position, 0, {0, 0}},
        _isActive{false},
        _player{player} {}

bool Mine::checkIsActive() {
    return _isActive;
}

void Mine::activateMine() {
    if (!_isActive)
        _isActive = true;
}


Score::PLAYER Mine::getPlayer() {
    return _player;
}

}
}
