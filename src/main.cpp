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
	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);

	Gameplay game(&window);

	game.restartGame();

	while (window.isOpen())
	{
		eventHandle(window);

		window.clear(Color::Black);

		// Load the pause menu for the game, if pressed again then break.
		if(Keyboard::isKeyPressed(Keyboard::Escape))
			if(endGame(game, window))
				break;

		// Continuously checks if the game is running, if it is then display it.
		// If the game stops running then end game screen is displayed.
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

	clock_t pauseTime = clock();

	while(1)
	{
		window.clear(Color::Black);

		game.pauseGame(pauseTime);
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
