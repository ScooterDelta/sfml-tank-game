// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Mine.h

#ifndef MINE_H_
#define MINE_H_

#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "Score.h"

class Mine : public DrawableObject
{
public:
	// Overloaded inherited functions.
	~Mine(){}
	Mine(Vector2D position, Score::PLAYER player);
	// Check is the mine activated
	bool checkIsActive();
	// Activate the mine.
	void activateMine();
	// Which player planted the mine
	Score::PLAYER getPlayer();
private:
	// Private member variables
	bool _isActive;
	Score::PLAYER _player;
};




#endif /* MINE_H_ */
