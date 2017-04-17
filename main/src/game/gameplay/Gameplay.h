// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Gameplay.h

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <ctime>
#include <memory>
#include "Battle.h"
#include "../display/Display.h"

using game::display::Display;

namespace game {
namespace gameplay {

//! Gameplay class.
/*!
 * This class manages player input, game timers and pausing and resuming the game.
 * It also passes displayable objects between the Battle class and the Display class.
 */
class Gameplay {
public:
    // Constructor.
    //! Class constructor.
    /*!
     * The class constructor initializes the pointer to the sf::RenderWindow so that objects can be
     * displayed in the Display class.
     * \param window The pointer to the sf::RenderWindow for display purposes.
     */
    Gameplay(std::shared_ptr<RenderWindow> window);
    // Check if the game is over, call continuously in game loop.
    //! Check if the game is over, call in game loop.
    /*!
     * This function must be called in the game loop as it handles updating the game objects
     * in every loop, allowing the game to update.
     */
    bool isGameOver();
    // Get score of current game.
    //! Get the score of the game, returns a Score object.
    /*!
     * Returns the current score of the game as a Score object.
     */
    Score getScore();
    // Get the remaining time for the game.
    //! Get the remaining time in the game.
    /*!
     * Returns the amount of time remaining in the game in seconds.
     */
    float getRemainingTime();
    // Pause game, call continuously while game is paused
    //! Display the pause game screen.
    /*!
     * Call this in the pause game loop to display the score screen
     * and control information while paused.
     */
    void pauseGame();
    // Pause timer, call when pause game is initially called.
    //! Pause the game timer before pause loop.
    /*!
     * Call this function before the game enters a pause game loop,
     * since it will pause the game timer.
     */
    void pauseTimer();
    // Resume timer is used when pause game is finished being called.
    //! Resume the game timer after the pause loop.
    /*!
     * Call this function after game leaves the pause loop, this
     * will resume the game timer.
     */
    void resumeTimer();
    // Display the obstacles on the screen.
    //! Display the game on the screen.
    /*!
     * Call this function in the game loop in order to display all objects
     * on the sf::RenderWindow.
     */
    void display();
    // Restart the game if needed.
    //! Restart all game assets to starting positions.
    /*!
     * This function will reset all objects in the game to their starting conditions,
     * and reset the score and timer.
     */
    void restartGame();
    // Draw the splash screen for the start of the game.
    //! Draw the splash screen.
    /*!
     * Use this function to display the starting screen before the game starts.
     */
    void drawSplash();

private:
    // Private member variables.
    //! The game Battle object, handling game interactions.
    Battle _battle;
    //! The display class, for drawing the game objects.
    Display _display;
    //! The game Score.
    Score _score;
    //! Variable used for timing the game.
    clock_t _timer;
    //! Variable used for timing the game.
    clock_t _pauseTime;
    //! Variable used for timing the game.
    float _pausedTime;
    //! Variable used for timing the game.
    float _displayPauseTime;

    // Helper functions
    //! Check the game controls, and input them if pressed.
    void checkControls();
    //! Display the game objects.
    /*!
     * All the ingame objects in battle are displayed using this function,
     * their Contrast can be defined.
     * \param Contrast The contrast of the ingame objects.
     */
    void displayGameObjects(int Contrast);
};

// Constructor.
Gameplay::Gameplay(std::shared_ptr<RenderWindow> window) :
        _battle{Vector2D{(float) window->getSize().x, (float) window->getSize().y}},
        _display{window},
        _score{0, 0},
        _timer{clock()},
        _pauseTime{0},
        _pausedTime{0},
        _displayPauseTime{0} {}

// Continuously check if game is over.
bool Gameplay::isGameOver() {
    float runTime = (float) (((clock() - _timer) / (double) CLOCKS_PER_SEC) - _pausedTime);
    if (runTime < 120) {
        checkControls();

        // Update the battle class.
        _battle.update();
        // Update the score.
        _score = _battle.getScore();
        return false;
    } else {
        // Display score screen.
        _score = _battle.getScore();
        displayGameObjects(60);
        _display.draw(_score);
        // Press P to restart game.
        if (Keyboard::isKeyPressed(Keyboard::P))
            restartGame();
        return true;
    }
}

void Gameplay::drawSplash() {
    _display.DrawSplash();
    // While splash is being displayed stop game from starting by constantly restarting it.
    restartGame();
}

float Gameplay::getRemainingTime() {
    return (float) (((clock() - _timer) / (double) CLOCKS_PER_SEC) - _pausedTime);
}

void Gameplay::display() {
// Draw all objects onto the screen calling the display class.
    float runTime = (float) (((clock() - _timer) / (double) CLOCKS_PER_SEC) - _pausedTime);
    displayGameObjects(255);
    _display.draw((120 - runTime));
}

void Gameplay::displayGameObjects(int Contrast) {
    sf::Uint8 _contrast = (sf::Uint8) Contrast;
    _display.drawBackGround(_contrast);
    _display.draw(_battle.getTurrets(), _contrast);
    _display.draw(_battle.getObstacles(), _contrast);
    _display.draw(_battle.getMines(), _contrast);
    _display.draw(_battle.getMissiles(), _contrast);
    _display.draw(*_battle.getTank1(), Score::PLAYER1, _contrast);
    _display.draw(*_battle.getTank2(), Score::PLAYER2, _contrast);
    _display.draw(_battle.getExplosions(), _contrast);
}

Score Gameplay::getScore() {
    return _score;
}

// Display pause game screen, showing the score.
void Gameplay::pauseGame() {
    _score = _battle.getScore();
    displayGameObjects(60);
    _display.draw(_displayPauseTime);
    _display.draw(_score, true);
}

void Gameplay::checkControls() {
    if (Keyboard::isKeyPressed(Keyboard::W))
        _battle.moveTank(Score::PLAYER1, Tank::FORWARD);
    else if (Keyboard::isKeyPressed(Keyboard::S))
        _battle.moveTank(Score::PLAYER1, Tank::BACKWARD);
    else
        _battle.moveTank(Score::PLAYER1, Tank::NONE);

    if (Keyboard::isKeyPressed(Keyboard::A))
        _battle.moveTank(Score::PLAYER1, Tank::ANTICLOCKWISE);
    else if (Keyboard::isKeyPressed(Keyboard::D))
        _battle.moveTank(Score::PLAYER1, Tank::CLOCKWISE);
    else
        _battle.moveTank(Score::PLAYER1, Tank::STRAIGHT);

    if (Keyboard::isKeyPressed(Keyboard::Space))
        _battle.fireMissile(Score::PLAYER1);

    if (Keyboard::isKeyPressed(Keyboard::LControl))
        _battle.plantMine(Score::PLAYER1);

    if (Keyboard::isKeyPressed(Keyboard::E))
        _battle.turnInvisible(Score::PLAYER1);

    // Player 2 Controls.
    if (Keyboard::isKeyPressed(Keyboard::Up))
        _battle.moveTank(Score::PLAYER2, Tank::FORWARD);
    else if (Keyboard::isKeyPressed(Keyboard::Down))
        _battle.moveTank(Score::PLAYER2, Tank::BACKWARD);
    else
        _battle.moveTank(Score::PLAYER2, Tank::NONE);

    if (Keyboard::isKeyPressed(Keyboard::Left))
        _battle.moveTank(Score::PLAYER2, Tank::ANTICLOCKWISE);
    else if (Keyboard::isKeyPressed(Keyboard::Right))
        _battle.moveTank(Score::PLAYER2, Tank::CLOCKWISE);
    else
        _battle.moveTank(Score::PLAYER2, Tank::STRAIGHT);

    if (Keyboard::isKeyPressed(Keyboard::RControl))
        _battle.fireMissile(Score::PLAYER2);

    if (Keyboard::isKeyPressed(Keyboard::Slash))
        _battle.plantMine(Score::PLAYER2);

    if (Keyboard::isKeyPressed(Keyboard::Period))
        _battle.turnInvisible(Score::PLAYER2);
}

void Gameplay::restartGame() {
    // Reset all members to initial conditions.
    _score = Score{0, 0};
    _timer = clock();
    _battle.restartBattle();
    _pauseTime = 0;
    _pausedTime = 0;
}

void Gameplay::pauseTimer() {
    // Store time that game is paused.
    _pauseTime = clock();
    _displayPauseTime = (float) (120 - (((clock() - _timer) / (double) CLOCKS_PER_SEC) - _pausedTime));
}

void Gameplay::resumeTimer() {
    // When game is resumed add to paused time total.
    _pausedTime += (clock() - _pauseTime) / (double) CLOCKS_PER_SEC;
}

}
}



#endif /* GAMEPLAY_H_ */
