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

namespace game::gameplay {

  using std::chrono::high_resolution_clock;

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
    high_resolution_clock::time_point _timer;
    //! Variable used for timing the game.
    long _pauseTime;
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
}

#endif /* GAMEPLAY_H_ */
