#ifndef HUD_H_
#define HUD_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "Battle.h"
#include "Players.h"

using namespace sf;

class HUD
{
public:
	// Initializer.
	HUD(RenderWindow * window);
	// DrawUI for a tank.
	void DrawUI(Tank & tank, Players::PLAYER player);

private:
	RenderWindow * _window;
	Font _font;
	Text _description;

	// Converts a float to a string.
	std::string floatToString(float input);
	std::string intToString(int input);
};



#endif /* HUD_H_ */
