#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "Gameplay.h"

using namespace std;
using namespace sf;

constexpr int windowWidth{1600}, windowHeight{900};

bool endGame(Gameplay & game, RenderWindow & window);
void eventHandle(RenderWindow & window);

int main()
{
	// Add Style::Fullscreen for fullscreen (last command input)
	RenderWindow window{{windowWidth, windowHeight}, "Epic tank battles of DOOOOM"};
	window.setFramerateLimit(120);
	//window.setVerticalSyncEnabled(true);

	Gameplay game(&window);

	while (window.isOpen())
	{
		eventHandle(window);

		window.clear(Color::Black);

		if(Keyboard::isKeyPressed(Keyboard::Escape))
			if(endGame(game, window))
				break;

		if(!game.isGameOver())
			game.display();

		// Display the window:
		window.display();
	}
}

bool endGame(Gameplay & game, RenderWindow & window)
{
	while(Keyboard::isKeyPressed(Keyboard::Escape));

	if(game.isGameOver())
		return true;

	while(1)
	{
		window.clear(Color::Black);

		game.pauseGame();
		if(Keyboard::isKeyPressed(Keyboard::R))
			return false;
		else if(Keyboard::isKeyPressed(Keyboard::P))
		{
			game.restartGame();
			return false;
		}
		else if(Keyboard::isKeyPressed(Keyboard::Escape))
			return true;

		// Display the window:
		window.display();
	}
	return false;
}

void eventHandle(RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}
