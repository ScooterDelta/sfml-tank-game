#include "Obstacle.h"

// Constructor
Obstacle::Obstacle(Rect<float> ObstacleSize)
{
	_obstacle.setSize({ObstacleSize.width, ObstacleSize.height});
	_obstacle.setOrigin({ObstacleSize.width/2.f, ObstacleSize.height/2.f});
	_obstacle.setPosition(ObstacleSize.left, ObstacleSize.top);
	_obstacle.setFillColor(Color::Cyan);
}

// Function to return the location and size of the object.
Rect<float> Obstacle::getBounds() const
{
	return _obstacle.getLocalBounds();
}

// Update the object (Draw on the screen)
void Obstacle::update()
{
	_window->draw(_obstacle);
}
