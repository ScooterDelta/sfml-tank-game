#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "Battle.h"

using namespace std;
using namespace sf;

constexpr int windowWidth{1600}, windowHeight{900};

void eventHandle(RenderWindow & window);

// Static variable, must be declared in global scope.
Texture * Missile::_explosionTexture;
Texture * Missile::_missileTexture;
RenderWindow * Tank::_window;
RenderWindow * Missile::_window;
RenderWindow * Obstacle::_window;

int main()
{
	RenderWindow window{{windowWidth, windowHeight}, "Epic tank battles of DOOOOM"};
	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);

	srand(time(0));

	Battle tankBattle{&window};

	tankBattle.addTank(Vector2f{100, windowHeight/2}, Controller::Player1);
	tankBattle.addTank(Vector2f{windowWidth - 100, windowHeight/2}, Controller::Player2);

	while (window.isOpen())
	{
		eventHandle(window);

		window.clear(Color::Black);

		if(Keyboard::isKeyPressed(Keyboard::Escape)) break;

		tankBattle.update();
		// Display the window:
		window.display();
	}
}

void eventHandle(RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}
