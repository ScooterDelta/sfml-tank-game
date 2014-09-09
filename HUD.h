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
	HUD(RenderWindow * window, Controller::Players player);
	void update(float health);
private:
	std::string floatToString(float & input);
	RenderWindow * _window;
	Controller::Players _player;
	Text _playerText;
	Text _healthText;
	Font _font;
};


#endif /* HUD_H_ */
