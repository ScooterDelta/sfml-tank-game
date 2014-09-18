#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "Battle.h"

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
	if(Keyboard::isKeyPressed(Keyboard::W))
		_battle.moveTank(Battle::Player1, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::S))
		_battle.moveTank(Battle::Player1, Tank::BACKWARD);

	if(Keyboard::isKeyPressed(Keyboard::A))
		_battle.moveTank(Battle::Player1, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::D))
		_battle.moveTank(Battle::Player1, Tank::CLOCKWISE);

	if(Keyboard::isKeyPressed(Keyboard::Space))
		_battle.fireMissile(Battle::Player1);


	if(Keyboard::isKeyPressed(Keyboard::Up))
		_battle.moveTank(Battle::Player2, Tank::FORWARD);
	else if (Keyboard::isKeyPressed(Keyboard::Down))
		_battle.moveTank(Battle::Player2, Tank::BACKWARD);

	if(Keyboard::isKeyPressed(Keyboard::Left))
		_battle.moveTank(Battle::Player2, Tank::ANTICLOCKWISE);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		_battle.moveTank(Battle::Player2, Tank::CLOCKWISE);

	if(Keyboard::isKeyPressed(Keyboard::RControl))
		_battle.fireMissile(Battle::Player2);

	_battle.update();
}

void Gameplay::display()
{
	_display.draw(_battle.getObstacles());
	_display.draw(_battle.getMissiles());
	_display.draw(*_battle.getTank1(), Battle::Player1);
	_display.draw(*_battle.getTank2(), Battle::Player2);
	_display.draw(_battle.getExplosions());
}

#endif /* GAMEPLAY_H_ */
