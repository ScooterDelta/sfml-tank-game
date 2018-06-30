// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Gameplay.cpp

#include "Gameplay.h"

namespace game::gameplay {

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  const long gameDuration = 120;

  // Constructor.
  Gameplay::Gameplay(std::shared_ptr<RenderWindow> window) :
    _battle{Vector2D{(float) window->getSize().x, (float) window->getSize().y}},
    _display{window},
    _score{0, 0},
    _timer{high_resolution_clock::now()},
    _pauseTime{0},
    _pausedTime{0},
    _displayPauseTime{0} {}

  // Continuously check if game is over.
  bool Gameplay::isGameOver() {
    float runTime = (double) ((duration_cast<milliseconds>( high_resolution_clock::now() - _timer ) / 1000.0).count() - _pausedTime);
    if (runTime < gameDuration) {
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
    return (double) ((duration_cast<milliseconds>( high_resolution_clock::now() - _timer ) / 1000.0).count() - _pausedTime);
  }

  void Gameplay::display() {
    // Draw all objects onto the screen calling the display class.
    float runTime = (double) ((duration_cast<milliseconds>( high_resolution_clock::now() - _timer ) / 1000.0).count() - _pausedTime);
    displayGameObjects(255);
    _display.draw((gameDuration - runTime));
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
    _timer = high_resolution_clock::now();
    _battle.restartBattle();
    _pauseTime = 0;
    _pausedTime = 0;
  }

  void Gameplay::pauseTimer() {
    // Store time that game is paused.
    _pauseTime = clock();
    _displayPauseTime = (float) (gameDuration - ((duration_cast<milliseconds>( high_resolution_clock::now() - _timer ) / 1000.0).count() - _pausedTime));
  }

  void Gameplay::resumeTimer() {
    // When game is resumed add to paused time total.
    _pausedTime += (clock() - _pauseTime) / (double) CLOCKS_PER_SEC;
  }
}
