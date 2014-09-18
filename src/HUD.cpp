#include "HUD.h"

HUD::HUD(RenderWindow * window):
	_window{window}
{
	_font.loadFromFile("assets/cmunit.ttf");

	_description.setFont(_font);
	_description.setOrigin({0.f, 0.f});
	_description.setCharacterSize(20);
	_description.setStyle(Text::Regular);
	_description.setColor(Color::White);
}

void HUD::DrawUI(Tank & tank, Battle::Player player)
{
	int mines = tank.getAllowedMines();
	if(player == Battle::Player1)
	{
		_description.setPosition(Vector2f{50.f, (float)_window->getSize().y - 26.f});
		_description.setString("Tank 1 Mines: ");
		_window->draw(_description);
		_description.setPosition(Vector2f{220.f, (float)_window->getSize().y - 26.f});
		_description.setString(intToString(mines));
		_window->draw(_description);
	}
	else
	{
		_description.setPosition(Vector2f{(float)_window->getSize().x/2 + 50.f, (float)_window->getSize().y - 26.f});
		_description.setString("Tank 2 Mines: ");
		_window->draw(_description);
		_description.setPosition(Vector2f{(float)_window->getSize().x/2 + 220.f, (float)_window->getSize().y - 26.f});
		_description.setString(intToString(mines));
		_window->draw(_description);
	}
}

std::string HUD::floatToString(float input)
{
	std::ostringstream buffer;
	buffer << input;
	return buffer.str();
}

std::string HUD::intToString(int input)
{
	std::ostringstream buffer;
	buffer << input;
	return buffer.str();
}
