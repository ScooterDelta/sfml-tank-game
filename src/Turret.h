#ifndef TURRET_H_
#define TURRET_H_

#include "AxisAligned.h"
#include <cmath>
#include <iostream>

class Turret : public AxisAligned
{
public:
	Turret(Vector2D position, Vector2D range);
	bool canFollowTarget(DrawableObject & target);
	void update();

	Vector2D getFirePosition();

private:
	// Private member variables
	Vector2D _range;
	const float _pi;
	bool _isClockwise;
};



#endif /* TURRET_H_ */
