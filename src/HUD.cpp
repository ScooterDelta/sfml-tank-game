#include "HUD.h"

// Initialize the HUD
HUD::HUD(RenderWindow * window, Controller::Players player):
	_window{window},
	_player{player}
{
	_font.loadFromFile("assets/cmunit.ttf");
	_playerText.setFont(_font);
	_playerText.setOrigin({0.f, 0.f});
	_healthText.setFont(_font);
	_healthText.setOrigin({0.f, 0.f});
	if(player == Controller::Player1)
	{
		_playerText.setPosition(Vector2f{50.f, (float)_window->getSize().y - 26.f});
		_healthText.setPosition(Vector2f{160.f, (float)_window->getSize().y - 26.f});
		_playerText.setString("Player 1: ");
	}
	else if (player == Controller::Player2)
	{
		_playerText.setPosition(Vector2f{(float)_window->getSize().x/2 + 50.f, (float)_window->getSize().y - 26.f});
		_healthText.setPosition(Vector2f{(float)_window->getSize().x/2 + 160.f, (float)_window->getSize().y - 26.f});
		_playerText.setString("Player 2: ");
	}
	_playerText.setCharacterSize(20);
	_playerText.setStyle(Text::Regular);
	_playerText.setColor(Color::White);

	_healthText.setString("100");
	_healthText.setCharacterSize(20);
	_healthText.setStyle(Text::Regular);
	_healthText.setColor(Color::White);


	// Create text.
}

// Update health on screen.
void HUD::update(float health)
{
	_healthText.setString(HUD::floatToString(health));
	_window->draw(_playerText);
	_window->draw(_healthText);
}

// Convert a float to a string.
std::string HUD::floatToString(float & input)
{
	std::ostringstream buffer;
	buffer << input;
	return buffer.str();
}
