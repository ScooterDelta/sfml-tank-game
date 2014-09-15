#ifndef MISSILE_H_
#define MISSILE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include "DrawableObject.h"

using namespace sf;

class Missile : public DrawableObject
{
public:
	// Constructor
	Missile(float direction, Vector2f location);
	virtual ~Missile();
	// Return the position of the missile.
	virtual Vector2f getPosition();
	// Return the direction of the object
	virtual float getDirection();
	// Update the missile, returns true if the missile leaves the screen.
	virtual void update();
	// Set the pointer to the texture of the explosion and missile.
	// This must be set for the class to work.
	static void setTextures(Texture * missileTexture, Texture * explosionTexture){
		_missileTexture = missileTexture;
		_explosionTexture = explosionTexture;
	}
	static void setRenderWindow(RenderWindow * window){
		_window = window;
	}
private:
	// Private member variables
	Sprite _missile;
	static RenderWindow * _window;
	Vector2f _velocity;
	float _pi;
	float _direction;
	// Since all missile objects use the same texture,
	// it is declared statically and initialized in the Battle class.
	static Texture * _missileTexture;
	static Texture * _explosionTexture;
};

#endif /* MISSILE_H_ */
