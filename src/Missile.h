// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Missile.h

#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Angle.h"
#include "DrawableObject.h"
#include "Score.h"

using namespace sf;

class Missile : public DrawableObject
{
public:
	// Constructor
	Missile(Vector2D location, float direction, Score::PLAYER player, Vector2D windowSize = {1600, 900});
	virtual ~Missile();
	// Update missile object
	void update();
	// Check if missile is Destroyable.
	bool isDestroyable(bool isHorizontal);
	// Check which player the missile was fired from
	Score::PLAYER getPlayer();
private:
	// Private member variables
	Vector2D _velocity;
	const float _pi;
	float _collisions;
	float _velocityModifier;
	Score::PLAYER _player;

	// Private helper functions
	bool isDestroyCone(float cone = 5);
};

#endif /* MISSILE_H_ */
