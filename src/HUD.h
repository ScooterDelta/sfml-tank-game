#ifndef HUD_H_
#define HUD_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "Battle.h"
#include "Score.h"

using namespace sf;

class HUD
{
public:
	// Initializer.
	HUD(RenderWindow * window);
	// DrawUI for a tank.
	void DrawUI(Tank & tank, Score::PLAYER player);
	void DrawScore(Score & score, bool isPaused);
	void DrawTimer(float remainingTime);

private:
	RenderWindow * _window;
	Font _font;
	Text _description;

	// Converts a float to a string.
	std::string floatToString(float input);
	std::string intToString(int input);
	void displayScore(Score & score);
	void displayString(std::string str, Vector2f location, unsigned int size = 20);
};



#endif /* HUD_H_ */
