#ifndef MINE_H_
#define MINE_H_

#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "Score.h"

class Mine : public DrawableObject
{
public:
	~Mine(){}
	Mine(Vector2f position, Score::PLAYER player);
	// Return the direction the object is facing.
	virtual float getDirection();
	// Return the position of the object.
	virtual Vector2f getPosition();
	// Return the size of the object
	virtual RectSize getSize();
	// Check is the mine activated
	bool checkIsActive();
	// Activate the mine.
	void activateMine();
	// Which player planted the mine
	Score::PLAYER getPlayer();
private:
	// Private member variables
	Angle _direction;
	Vector2f _position;
	RectSize _size;
	bool _isActive;
	Score::PLAYER _player;
};




#endif /* MINE_H_ */
