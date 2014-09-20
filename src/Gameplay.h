#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "Battle.h"
#include "Display.h"

class Gameplay
{
public:
	Gameplay(RenderWindow * window);
	void update();
	void display();
private:
	Battle _battle;
	Display _display;
};

Gameplay::Gameplay(RenderWindow * window):
	_battle{Vector2f{(float)window->getSize().x, (float)window->getSize().y}},
	_display{window} {}


void Gameplay::update()
{
// Player 1 Controls.
	if(Keyboard::isKeyPressed(Keyboard::W))
		_battle.moveTank(Players::PLAYER1, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		_battle.moveTank(Players::PLAYER1, Tank::BACKWARD);

	if(Keyboard::isKeyPressed(Keyboard::A))
		_battle.moveTank(Players::PLAYER1, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::D))
		_battle.moveTank(Players::PLAYER1, Tank::CLOCKWISE);

	if(Keyboard::isKeyPressed(Keyboard::Space))
		_battle.fireMissile(Players::PLAYER1);

	if(Keyboard::isKeyPressed(Keyboard::LControl))
		_battle.plantMine(Players::PLAYER1);

// Player 2 Controls.
	if(Keyboard::isKeyPressed(Keyboard::Up))
		_battle.moveTank(Players::PLAYER2, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::Down))
		_battle.moveTank(Players::PLAYER2, Tank::BACKWARD);

	if(Keyboard::isKeyPressed(Keyboard::Left))
		_battle.moveTank(Players::PLAYER2, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		_battle.moveTank(Players::PLAYER2, Tank::CLOCKWISE);

	if(Keyboard::isKeyPressed(Keyboard::RControl))
		_battle.fireMissile(Players::PLAYER2);

	if(Keyboard::isKeyPressed(Keyboard::Slash))
		_battle.plantMine(Players::PLAYER2);

// Update the battle class.
	_battle.update();
}

void Gameplay::display()
{
// Draw all objects onto the screen calling the display class.
	_display.draw(_battle.getObstacles());
	_display.draw(_battle.getMines());
	_display.draw(_battle.getMissiles());
	_display.draw(*_battle.getTank1(), Players::PLAYER1);
	_display.draw(*_battle.getTank2(), Players::PLAYER2);
	_display.draw(_battle.getExplosions());
}

#endif /* GAMEPLAY_H_ */
