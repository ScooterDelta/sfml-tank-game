#ifndef TURRET_H_
#define TURRET_H_

#include "AxisAligned.h"
#include <cmath>
#include <ctime>
#include <iostream>

class Turret : public AxisAligned
{
public:
	~Turret() {}
	Turret(Vector2D position, Vector2D range, Vector2D screenSize);
	bool canFollowTarget(DrawableObject & target, bool TargetInvisible = false);
	void update();

	Vector2D getFirePosition();
	bool canFireMissile();

private:
	// Private member variables
	Vector2D _range;
	const float _pi;
	bool _isClockwise;
	clock_t _fireTime;
};



#endif /* TURRET_H_ */
