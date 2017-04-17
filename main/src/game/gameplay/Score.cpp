// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Score.cpp

#include "Score.h"

namespace game {
namespace gameplay {

// Constructor.
Score::Score(const Score &score) :
        _player1Kills{score._player1Kills},
        _player1Deaths{score._player1Deaths},
        _player2Kills{score._player2Kills},
        _player2Deaths(score._player2Deaths) {}

Score::Score(int player1Score, int player2Score) :
        _player1Kills{player1Score},
        _player1Deaths{player1Score},
        _player2Kills{player2Score},
        _player2Deaths{player2Score} {}

// Copy operator.
Score &Score::operator=(const Score &rhs) {
    this->_player1Kills = rhs._player1Kills;
    this->_player1Deaths = rhs._player1Deaths;
    this->_player2Kills = rhs._player2Kills;
    this->_player2Deaths = rhs._player2Deaths;

    return *this;
}

// Increase number of kills
void Score::increaseKills(PLAYER player) {
    if (player == PLAYER1)
        _player1Kills++;
    else if (player == PLAYER2)
        _player2Kills++;
}

// Increase number of deaths.
void Score::increaseDeaths(PLAYER player) {
    if (player == PLAYER1)
        _player1Deaths++;
    else if (player == PLAYER2)
        _player2Deaths++;
}

// Get number of kills for player.
int Score::getKills(PLAYER player) {
    if (player == PLAYER1)
        return _player1Kills;
    else if (player == PLAYER2)
        return _player2Kills;
    else return 0;
}

// Get number of deaths for palyer.
int Score::getDeaths(PLAYER player) {
    if (player == PLAYER1)
        return _player1Deaths;
    else if (player == PLAYER2)
        return _player2Deaths;
    else return 0;
}

}
}
