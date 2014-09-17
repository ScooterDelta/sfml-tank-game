#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "Display.h"
#include "Battle.h"
#include "Gameplay.h"

using namespace std;
using namespace sf;

constexpr int windowWidth{1600}, windowHeight{900};

void eventHandle(RenderWindow & window);

int main()
{
	// Add Style::Fullscreen for fullscreen (last command input)
	RenderWindow window{{windowWidth, windowHeight}, "Epic tank battles of DOOOOM"};
	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);

	srand(time(0));

	Gameplay game(&window);

	while (window.isOpen())
	{
		eventHandle(window);

		if(Keyboard::isKeyPressed(Keyboard::Escape)) break;

		window.clear(Color::Black);

		game.update();
		game.display();

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
