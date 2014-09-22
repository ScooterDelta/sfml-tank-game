#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <ctime>
#include "Battle.h"
#include "Display.h"

class Gameplay
{
public:
	Gameplay(RenderWindow * window);
	bool isGameOver();
	Score getScore();
	// Pause game, call continuously while game is paused
	void pauseGame(clock_t pauseTime);
	void display();
	void restartGame();
private:
	Battle _battle;
	Display _display;
	Score _score;
	clock_t _timer;
	clock_t _pauseTime;
	clock_t _resumeTime;

	// Helper functions
	void checkControls();
};

Gameplay::Gameplay(RenderWindow * window):
	_battle{Vector2f{(float)window->getSize().x, (float)window->getSize().y}},
	_display{window},
	_score{0, 0},
	_timer{clock()},
	_pauseTime{0},
	_resumeTime{0}
{}

bool Gameplay::isGameOver()
{
	float runTime = ((clock() - _timer - _resumeTime + _pauseTime)/(double) CLOCKS_PER_SEC);
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
		_score = _battle.getScore();
		_display.draw(_score);
		if(Keyboard::isKeyPressed(Keyboard::P))
			restartGame();
		return true;
	}
}

void Gameplay::display()
{
// Draw all objects onto the screen calling the display class.
	float runTime = ((clock() - _timer - _resumeTime + _pauseTime)/(double) CLOCKS_PER_SEC);
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

void Gameplay::pauseGame(clock_t pauseTime)
{
	_score = _battle.getScore();
	_display.draw(_score, true);
	_pauseTime = pauseTime;
	_resumeTime = clock();
}

void Gameplay::checkControls()
{
	// Player 1 Controls.
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
	_score = Score{0,0};
	_timer = clock();
	_battle.restartBattle();
}

#endif /* GAMEPLAY_H_ */
