#ifndef HUD_H_
#define HUD_H_

#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "iostream"
#include <sstream>
#include <string>

using namespace sf;

class HUD
{
public:
	// Initializer
	HUD(RenderWindow * window, Controller::Players player);
	// Update the health on the hud
	void update(float health);
private:
	// Private Member functions.
	// Converts a float to a string.
	std::string floatToString(float & input);
	// Private member variables.
	RenderWindow * _window;
	Controller::Players _player;
	Text _playerText;
	Text _healthText;
	Font _font;
};


#endif /* HUD_H_ */
