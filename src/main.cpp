// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - main.cpp

#include <iostream>
#include <memory>
#include "Gameplay.h"

using namespace std;
using namespace sf;

constexpr int windowWidth{1600}, windowHeight{900};

// Function for handling the pause menu and ending game.
bool endGame(Gameplay & game, shared_ptr<RenderWindow> & window);
// Function for handling windows events.
void eventHandle(shared_ptr<RenderWindow> & window);

int main()
{
	// Add Style::Fullscreen for fullscreen (last command input)
	shared_ptr<RenderWindow> window(new RenderWindow{{windowWidth, windowHeight},
		"Epic tank battles of DOOM", Style::Fullscreen});
	window->setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);

	Gameplay game(window);

	// Initialise all game components to 0 before it starts.
	game.restartGame();

	bool startGame = false;

	while (window->isOpen())
	{
		eventHandle(window);

		window->clear(Color::Black);

		if(!startGame)
		{
			game.drawSplash();

			if(Keyboard::isKeyPressed(Keyboard::Q))
				break;
			else if(Keyboard::isKeyPressed(Keyboard::P))
				startGame = true;
		}
		else
		{
			// Continuously checks if the game is running, if it is then display it.
			// If the game stops running then end game screen is displayed.
			if(!game.isGameOver())
			{
				game.display();
				// Load the pause menu for the game, if pressed again then break.
				if(Keyboard::isKeyPressed(Keyboard::Escape))
					if(endGame(game, window))
						break;
			}
			// If the game is not running and Q is pressed then exit game loop.
			else if(Keyboard::isKeyPressed(Keyboard::Q))
				break;
		}


		// Display the window:
		window->display();
	}
}

// Function for handling the pause menu and ending game.
bool endGame(Gameplay & game, shared_ptr<RenderWindow> & window)
{
	while(Keyboard::isKeyPressed(Keyboard::Escape));

	game.pauseTimer();

	while(1)
	{
		window->clear(Color::Black);

		game.pauseGame();
		// Pressing the escape key while in the pause menu will return to the game.
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			while(Keyboard::isKeyPressed(Keyboard::Escape));
			game.resumeTimer();
			return false;
		}
		// Pressing P while in the pause menu will restart the game
		else if(Keyboard::isKeyPressed(Keyboard::P))
		{
			game.restartGame();
			return false;
		}
		// Pressing Q while in the pause menu will quit the game.
		else if(Keyboard::isKeyPressed(Keyboard::Q))
			return true;

		// Display the window:
		window->display();
	}
	return false;
}

// Function for handling windows events.
void eventHandle(shared_ptr<RenderWindow> & window)
{
	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			window->close();
}
