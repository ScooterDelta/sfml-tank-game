#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
public:
	// Constructor
	Obstacle(Rect<float> ObstacleSize);
	// Return the bounds of the object
	Rect<float> getBounds() const;
	// Update the object, draw on the screen
	void update();

	// Set static render window.
	static void setRenderWindow(RenderWindow * window){
		_window = window;
	}
private:
	// Private member Variables.
	RectangleShape _obstacle;
	static RenderWindow * _window;
};



#endif /* OBSTACLE_H_ */
