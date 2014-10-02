// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Gameplay.h

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <ctime>
#include "Battle.h"
#include "Display.h"

class Gameplay
{
public:
	// Constructor.
	Gameplay(RenderWindow * window);
	// Check if the game is over, call continuously in game loop.
	bool isGameOver();
	// Get score of current game.
	Score getScore();
	// Pause game, call continuously while game is paused
	void pauseGame();
	// Pause timer, call when pause game is initially called.
	void pauseTimer();
	// Resume timer is used when pause game is finished being called.
	void resumeTimer();
	// Display the obstacles on the screen.
	void display();
	// Restart the game if needed.
	void restartGame();
private:
	// Private member variables.
	Battle _battle;
	Display _display;
	Score _score;
	clock_t _timer;
	clock_t _pauseTime;
	float _pausedTime;

	// Helper functions
	void checkControls();
};

// Constructor.
Gameplay::Gameplay(RenderWindow * window):
	_battle{Vector2D{(float)window->getSize().x, (float)window->getSize().y}},
	_display{window},
	_score{0, 0},
	_timer{clock()},
	_pauseTime{0},
	_pausedTime{0}
{}

// Continuously check if game is over.
bool Gameplay::isGameOver()
{
	float runTime = ((clock() - _timer)/(double) CLOCKS_PER_SEC) - _pausedTime;
	if(runTime < 120)
	{
		checkControls();

		// Update the battle class.
		_battle.update();
		// Update the score.
		_score = _battle.getScore();
		return false;
	}
	else
	{
		// Display score screen.
		_score = _battle.getScore();
		_display.draw(_score);
		// Press P to restart game.
		if(Keyboard::isKeyPressed(Keyboard::P))
			restartGame();
		return true;
	}
}

void Gameplay::display()
{
// Draw all objects onto the screen calling the display class.
	float runTime = ((clock() - _timer)/(double) CLOCKS_PER_SEC) - _pausedTime;
	_display.drawBackGround();
	_display.draw(_battle.getTurrets());
	_display.draw(_battle.getObstacles());
	_display.draw(_battle.getMines());
	_display.draw(_battle.getMissiles());
	_display.draw(*_battle.getTank1(), Score::PLAYER1);
	_display.draw(*_battle.getTank2(), Score::PLAYER2);
	_display.draw(_battle.getExplosions());
	_display.draw((120 - runTime));
}

Score Gameplay::getScore()
{
	return _score;
}

// Display pause game screen, showing the score.
void Gameplay::pauseGame()
{
	_score = _battle.getScore();
	_display.draw(_score, true);
}

void Gameplay::checkControls()
{
	if(Keyboard::isKeyPressed(Keyboard::W))
		_battle.moveTank(Score::PLAYER1, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		_battle.moveTank(Score::PLAYER1, Tank::BACKWARD);
	else
		_battle.moveTank(Score::PLAYER1, Tank::NONE);

	if(Keyboard::isKeyPressed(Keyboard::A))
		_battle.moveTank(Score::PLAYER1, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::D))
		_battle.moveTank(Score::PLAYER1, Tank::CLOCKWISE);
	else
		_battle.moveTank(Score::PLAYER1, Tank::STRAIGHT);

	if(Keyboard::isKeyPressed(Keyboard::Space))
		_battle.fireMissile(Score::PLAYER1);

	if(Keyboard::isKeyPressed(Keyboard::LControl))
		_battle.plantMine(Score::PLAYER1);

	// Player 2 Controls.
	if(Keyboard::isKeyPressed(Keyboard::Up))
		_battle.moveTank(Score::PLAYER2, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::Down))
		_battle.moveTank(Score::PLAYER2, Tank::BACKWARD);
	else
		_battle.moveTank(Score::PLAYER2, Tank::NONE);

	if(Keyboard::isKeyPressed(Keyboard::Left))
		_battle.moveTank(Score::PLAYER2, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		_battle.moveTank(Score::PLAYER2, Tank::CLOCKWISE);
	else
		_battle.moveTank(Score::PLAYER2, Tank::STRAIGHT);

	if(Keyboard::isKeyPressed(Keyboard::RControl))
		_battle.fireMissile(Score::PLAYER2);

	if(Keyboard::isKeyPressed(Keyboard::Slash))
		_battle.plantMine(Score::PLAYER2);
}

void Gameplay::restartGame()
{
	// Reset all members to initial conditions.
	_score = Score{0,0};
	_timer = clock();
	_battle.restartBattle();
	_pauseTime = 0;
	_pausedTime = 0;
}

void Gameplay::pauseTimer()
{
	// Store time that game is paused.
	_pauseTime = clock();
}

void Gameplay::resumeTimer()
{
	// When game is resumed add to paused time total.
	_pausedTime += (clock() - _pauseTime) / (double) CLOCKS_PER_SEC;
}

#endif /* GAMEPLAY_H_ */
