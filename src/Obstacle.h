#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <SFML/Graphics.hpp>
#include <cmath>

#include "RectangleObject.h"

using namespace sf;

class Obstacle : public RectangleObject
{
public:
	// Constructor
	Obstacle(Rect<float> ObstacleSize, float direction);
	// Destructor
	virtual ~Obstacle() {}
	// Update the object, draw on the screen
	virtual void update();
	// Return the size of the object.
	virtual Vector2f frontLeft();
	virtual Vector2f frontRight();
	virtual Vector2f backLeft();
	virtual Vector2f backRight();
	// Return origin and direction.
	virtual float getDirection();
	virtual Vector2f getPosition();

	// Set static render window.
	static void setRenderWindow(RenderWindow * window){
		_window = window;
	}
private:
	// Private member Variables.
	RectangleShape _drawable;
	Texture _texture;
	static RenderWindow * _window;
	float _pi;
	float _cornerAngle;
	float _cornerDistance;
	float _direction;

};



#endif /* OBSTACLE_H_ */
