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

void HUD::DrawUI(Tank & tank, Score::PLAYER player)
{
	int mines = tank.getAllowedMines();
	std::string tempString;
	Vector2f tempLocation;
	if(player == Score::PLAYER1)
	{
		tempLocation = Vector2f{50.f, (float)_window->getSize().y - 26.f};
		displayString("Tank 1 Mines: ", tempLocation);
		tempString = intToString(mines);
		tempLocation = Vector2f{220.f, (float)_window->getSize().y - 26.f};
		displayString(tempString, tempLocation);
	}
	else
	{
		tempLocation = Vector2f{(float)_window->getSize().x/2 + 50.f, (float)_window->getSize().y - 26.f};
		displayString("Tank 2 Mines: ", tempLocation);
		tempString = intToString(mines);
		tempLocation = Vector2f{(float)_window->getSize().x/2 + 220.f, (float)_window->getSize().y - 26.f};
		displayString(tempString, tempLocation);
	}
}

void HUD::DrawScore(Score & score, bool isPaused)
{
	Vector2f windowSize{_window->getSize()};
	std::string tempString;

	displayScore(score);

	// Display message:
	if(isPaused)
	{
		tempString = "Press ESC to end game.";
		displayString(tempString, {windowSize.x/16, windowSize.y * 8/9});
		tempString = "press R to resume game, or P to restart game.";
		displayString(tempString, {windowSize.x/16, windowSize.y * 8/9 + 30});
	}
	else
	{
		tempString = "Press ESC to end game, or press P to play again.";
		displayString(tempString, {windowSize.x/16, windowSize.y * 8/9});
	}
}

void HUD::displayScore(Score & score)
{
	Vector2f windowSize{_window->getSize()};
	std::string tempString;

	displayString("SCORE:", {windowSize.x/16, windowSize.y/9}, 40);
	displayString("Kills", {windowSize.x/16 + 200, windowSize.y/9 + 120});
	displayString("Deaths", {windowSize.x/16 + 300, windowSize.y/9 + 120});
	// Player 1
	displayString("Player 1: ", {windowSize.x/16, windowSize.y/9 + 150});
	tempString = intToString(score.getKills(Score::PLAYER1));
	displayString(tempString, {windowSize.x/16 + 200, windowSize.y/9 + 150});
	tempString = intToString(score.getDeaths(Score::PLAYER1));
	displayString(tempString, {windowSize.x/16 + 300, windowSize.y/9 + 150});
	// Player 2
	displayString("Player 2: ", {windowSize.x/16, windowSize.y/9 + 180});
	tempString = intToString(score.getKills(Score::PLAYER2));
	displayString(tempString, {windowSize.x/16 + 200, windowSize.y/9 + 180});
	tempString = intToString(score.getDeaths(Score::PLAYER2));
	displayString(tempString, {windowSize.x/16 + 300, windowSize.y/9 + 180});
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

void HUD::displayString(std::string str, Vector2f location, unsigned int size)
{
	_description.setCharacterSize(size);
	_description.setPosition(location);
	_description.setString(str);

	_window->draw(_description);
}
