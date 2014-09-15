#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class DrawableObject
{
public:
	virtual float getDirection() = 0;
	virtual void update() = 0;
	virtual Vector2f getPosition() = 0;

	virtual ~DrawableObject() {}
private:
	// No private members
};



#endif /* DRAWABLEOBJECT_H_ */
