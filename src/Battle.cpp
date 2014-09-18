#include "Battle.h"

Battle::Battle(Vector2f screenDimensions) :
	_screenDimensions{screenDimensions},
	_tank1{{200, screenDimensions.y/2}},
	_tank2{{screenDimensions.x - 200, screenDimensions.y/2}},
	_missileTimer1{0},
	_missileTimer2{0},
	_mineTimer1{0},
	_mineTimer2{0}
{
	// Make the map for the game.
	makeMap();
}

void Battle::moveTank(Player player, Tank::Direction direction)
{
	if(player == Player1)
	{
		// Act on tank1 (collisions with walls)
		_tank1.setMovement(direction);
	}
	else if (player == Player2)
	{
		// Act on tank2 (collisions with walls)
		_tank2.setMovement(direction);
	}
}

void Battle::moveTank(Player player, Tank::Movement movement)
{
	if(player == Player1)
	{
		// Act on tank1 (collisions with walls)
		if(movement == Tank::FORWARD && !isFrontWallCollision(_tank1)
				&&  !isFrontTankCollision(_tank1, _tank2))
			_tank1.setMovement(movement);
		else if (movement == Tank::BACKWARD && !isBackWallCollision(_tank1)
				&& !isBackTankCollision(_tank1, _tank2))
			_tank1.setMovement(movement);
		else
			_tank1.setMovement(Tank::NONE);
	}
	else if (player == Player2)
	{
		// Act on tank2 (collisions with walls)
		if(movement == Tank::FORWARD && !isFrontWallCollision(_tank2)
				&&  !isFrontTankCollision(_tank2, _tank1))
			_tank2.setMovement(movement);
		else if (movement == Tank::BACKWARD && !isBackWallCollision(_tank2)
				&& !isBackTankCollision(_tank2, _tank1))
			_tank2.setMovement(movement);
		else
			_tank2.setMovement(Tank::NONE);
	}
}

void Battle::update()
{
	checkMissiles();

	// Check if the missiles have hit any tanks.
	missileHit(_tank1);
	missileHit(_tank2);

	// Check if a tank has driven over a mine.
	mineHit(_tank1);
	mineHit(_tank2);

	auto _explosionIterator = _explosions.begin();
	while(_explosionIterator != _explosions.end())
	{
		if(clock() - (*_explosionIterator)->getExplosionTime() > 50)
			_explosionIterator = _explosions.erase(_explosionIterator);
		else
			++_explosionIterator;
	}
}

void Battle::checkMissiles()
{
	// Update all missile objects (delete if they leave the bounds of the screen)
	// Bounce or delete if missiles hit obstacles or leave screen.
	Vector2f _missilePos;
	bool _collisionHorizontal = false;
	auto _missileIterator = _missiles.begin();
	while(_missileIterator != _missiles.end())
	{
		(*_missileIterator)->update();

		_missilePos = (*_missileIterator)->getPosition();

		if(isMissileWallCollision(_missilePos, _collisionHorizontal))
		{
			if((*_missileIterator)->isDestroyable(_collisionHorizontal))
			{
				std::unique_ptr<Explosion> newExplosion(new Explosion{(*_missileIterator)->getPosition()});
				_explosions.push_back(std::move(newExplosion));
				_missileIterator = _missiles.erase(_missileIterator);
			}
		}
		else
			++_missileIterator;
	}
}

bool Battle::isMissileWallCollision(Vector2f & _missilePos, bool & isHorizontal)
{
	// Check the particular missile against all obstacles.
	Vector2f tempObstacleTL, tempObstacleBR;
	auto _obstacleIter = _obstacles.begin();
	float leftDistance = 0, rightDistance = 0;
	float bottomDistance = 0, topDistance = 0;
	while(_obstacleIter != _obstacles.end())
	{
		tempObstacleTL = (*_obstacleIter)->topLeft();
		tempObstacleBR = (*_obstacleIter)->bottomRight();
		// See if missile is inside the bounds of this object.
		if(_missilePos.x > tempObstacleTL.x && _missilePos.x < tempObstacleBR.x
				&& _missilePos.y < tempObstacleBR.y && _missilePos.y > tempObstacleTL.y)
		{
			leftDistance = abs(_missilePos.x - tempObstacleTL.x);
			rightDistance = abs(_missilePos.x - tempObstacleBR.x);
			topDistance = abs(_missilePos.y - tempObstacleTL.y);
			bottomDistance = abs(_missilePos.y - tempObstacleBR.y);

			// Check which side the missile is touching on (for bounce).
			if(leftDistance < bottomDistance && leftDistance < topDistance && leftDistance < rightDistance)
				isHorizontal = false;
			else if (rightDistance < bottomDistance && rightDistance < topDistance && rightDistance < leftDistance)
				isHorizontal = false;
			else
				isHorizontal = true;

			return true;
		}

		++_obstacleIter;
	}
	if(_missilePos.x < 0 || _missilePos.y < 0 ||
			_missilePos.x > (_screenDimensions.x - 10) ||
			_missilePos.y > (_screenDimensions.y - 10))
	{
		if(_missilePos.x < 0 || _missilePos.x > (_screenDimensions.x - 10))
			isHorizontal = false;
		else
			isHorizontal = true;

		return true;
	}
	else
		return false;
}

void Battle::fireMissile(Player player)
{
	Vector2f turret;
	if(player == Player1 && (clock() - _missileTimer1) > 600)
	{
		turret.x = (_tank1.frontLeft().x + _tank1.frontRight().x)/2;
		turret.y = (_tank1.frontRight().y + _tank1.frontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank1.getDirection()});
		_missiles.push_back(std::move(newMissile));

		_missileTimer1 = clock();
	}
	else if (player == Player2 && (clock() - _missileTimer2) > 600)
	{
		turret.x = (_tank2.frontLeft().x + _tank2.frontRight().x)/2;
		turret.y = (_tank2.frontRight().y + _tank2.frontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank2.getDirection()});
		_missiles.push_back(std::move(newMissile));

		_missileTimer2 = clock();
	}

}

void Battle::plantMine(Player player)
{
	Vector2f turret;
	if(player == Player1 && (clock() - _mineTimer1) > 1000 &&  _tank1.getAllowedMines() != 0)
	{
		turret.x = (_tank1.backLeft().x + _tank1.backRight().x)/2;
		turret.y = (_tank1.backRight().y + _tank1.backLeft().y)/2;

		std::unique_ptr<Mine> newMine(new Mine{turret});
		_mines.push_back(std::move(newMine));

		_tank1.plantMine();

		_mineTimer1 = clock();
	}
	else if (player == Player2 && (clock() - _mineTimer2) > 1000 &&  _tank2.getAllowedMines() != 0)
	{
		turret.x = (_tank2.backLeft().x + _tank2.backRight().x)/2;
		turret.y = (_tank2.backRight().y + _tank2.backLeft().y)/2;

		std::unique_ptr<Mine> newMine(new Mine{turret});
		_mines.push_back(std::move(newMine));

		_tank2.plantMine();

		_mineTimer2 = clock();
	}
}

Tank * Battle::getTank1()
{
	return & _tank1;
}

Tank * Battle::getTank2()
{
	return & _tank2;
}

std::list<std::unique_ptr<Missile>> * Battle::getMissiles()
{
	return & _missiles;
}

std::list<std::unique_ptr<Explosion>> * Battle::getExplosions()
{
	return & _explosions;
}

std::list<std::unique_ptr<Obstacle>> * Battle::getObstacles()
{
	return & _obstacles;
}

std::list<std::unique_ptr<Mine>> * Battle::getMines()
{
	return & _mines;
}

bool Battle::isFrontWallCollision(Tank & tank)
{
	// Check for a collision with a wall infront of the tank.
	Vector2f tempContainerFL = tank.frontLeft();
	Vector2f tempContainerFR = tank.frontRight();
	Vector2f tempObstacleTL, tempObstacleBR;

	if (tempContainerFL.x < 0 || tempContainerFL.y < 0 || tempContainerFL.x > _screenDimensions.x || tempContainerFL.y > _screenDimensions.y)
		return true;
	else if (tempContainerFR.x < 0 || tempContainerFR.y < 0 || tempContainerFR.x > _screenDimensions.x || tempContainerFR.y > _screenDimensions.y)
		return true;
	else
	{
		auto _obstacleIter = _obstacles.begin();
		while(_obstacleIter != _obstacles.end())
		{
			tempObstacleTL = (*_obstacleIter)->topLeft();
			tempObstacleBR = (*_obstacleIter)->bottomRight();
			if(tempContainerFL.x > tempObstacleTL.x && tempContainerFL.x < tempObstacleBR.x
					&& tempContainerFL.y < tempObstacleBR.y && tempContainerFL.y > tempObstacleTL.y)
				return true;
			else if (tempContainerFR.x > tempObstacleTL.x && tempContainerFR.x < tempObstacleBR.x
					&& tempContainerFR.y < tempObstacleBR.y && tempContainerFR.y > tempObstacleTL.y)
				return true;

			++_obstacleIter;
		}
		return false;
	}
}

bool Battle::isBackWallCollision(Tank & tank)
{
	// Check for a collision with a wall behind the tank.
	Vector2f tempContainerBL = tank.backLeft();
	Vector2f tempContainerBR = tank.backRight();
	Vector2f tempObstacleTL, tempObstacleBR;

	if (tempContainerBL.x < 0 || tempContainerBL.y < 0 || tempContainerBL.x > _screenDimensions.x || tempContainerBL.y > _screenDimensions.y)
		return true;
	else if (tempContainerBR.x < 0 || tempContainerBR.y < 0 || tempContainerBR.x > _screenDimensions.x || tempContainerBR.y > _screenDimensions.y)
		return true;
	else
	{
		auto _obstacleIter = _obstacles.begin();
		while(_obstacleIter != _obstacles.end())
		{
			tempObstacleTL = (*_obstacleIter)->topLeft();
			tempObstacleBR = (*_obstacleIter)->bottomRight();
			if(tempContainerBL.x > tempObstacleTL.x && tempContainerBL.x < tempObstacleBR.x
					&& tempContainerBL.y < tempObstacleBR.y && tempContainerBL.y > tempObstacleTL.y)
				return true;
			else if (tempContainerBR.x > tempObstacleTL.x && tempContainerBR.x < tempObstacleBR.x
					&& tempContainerBR.y < tempObstacleBR.y && tempContainerBR.y > tempObstacleTL.y)
				return true;

			++_obstacleIter;
		}
		return false;
	}
}

void Battle::missileHit(Tank & tank)
{
	// Check if any missiles have hit any tanks. If they have the tank takes damage.
	std::vector<Vector2f> tankVertex;
	tankVertex.push_back(tank.frontLeft());	// 0 - Front Left
	tankVertex.push_back(tank.frontRight()); // 1 - Front Right
	tankVertex.push_back(tank.backRight()); // 2 - back Right
	tankVertex.push_back(tank.backLeft()); // 3 - back left

	Vector2f _missileCenter;
	std::vector<Vector2f> _missileVertex;

	auto _missileIterator = _missiles.begin();
	while(_missileIterator != _missiles.end())
	{
		_missileCenter.x = (*_missileIterator)->getPosition().x;
		_missileCenter.y = (*_missileIterator)->getPosition().y;
		_missileVertex.clear();
		_missileVertex.push_back(_missileCenter);
		if(isPolyCollision(tankVertex, _missileVertex))
		{
			std::unique_ptr<Explosion> newExplosion(new Explosion{(*_missileIterator)->getPosition()});
			_explosions.push_back(std::move(newExplosion));
			_missileIterator = _missiles.erase(_missileIterator);
		}
		else
			++_missileIterator;
	}
}

void Battle::mineHit(Tank & tank)
{
	// Check if any missiles have hit any tanks. If they have the tank takes damage.
	Vector2f _mineCenter, _tankCenter;
	float distance = 0;

	_tankCenter.x = tank.getPosition().x;
	_tankCenter.y = tank.getPosition().y;

	auto _mineIterator = _mines.begin();
	while(_mineIterator != _mines.end())
	{
		_mineCenter.x = (*_mineIterator)->getPosition().x;
		_mineCenter.y = (*_mineIterator)->getPosition().y;

		distance = sqrt(pow(_tankCenter.x - _mineCenter.x,2) + pow(_tankCenter.y - _mineCenter.y,2));
		if(distance < 30)
		{
			std::unique_ptr<Explosion> newExplosion(new Explosion{_mineCenter});
			_explosions.push_back(std::move(newExplosion));
			_mineIterator = _mines.erase(_mineIterator);
		}
		else
			++_mineIterator;
	}
}

bool Battle::isFrontTankCollision(Tank & aTank, Tank & bTank)
{
	// Check if any tanks are touching any other tanks in front .
	std::vector<Vector2f> aTankVertex, bTankVertex;
	aTankVertex.push_back(aTank.frontLeft());	// 0 - Front Left
	aTankVertex.push_back(aTank.frontRight()); // 1 - Front Right
	aTankVertex.push_back(aTank.backRight()); // 2 - back Right
	aTankVertex.push_back(aTank.backLeft()); // 3 - back left

	bTankVertex.push_back(bTank.frontLeft());	// 0 - Front Left
	bTankVertex.push_back(bTank.frontRight()); // 1 - Front Right
	bTankVertex.push_back(bTank.backRight()); // 2 - back Right
	bTankVertex.push_back(bTank.backLeft()); // 3 - back left

	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2f aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2f aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2f bTankCenter{bTank.getPosition()};

		double frontDistance = sqrt(pow(aTankFront.x - bTankCenter.x, 2) + pow(aTankFront.y - bTankCenter.y, 2));
		double backDistance = sqrt(pow(aTankBack.x - bTankCenter.x, 2) + pow(aTankBack.y - bTankCenter.y, 2));

		if(frontDistance < backDistance)
			return true;
		else return false;
	}
	else
		return false;
}

bool Battle::isBackTankCollision(Tank & aTank, Tank & bTank)
{
	// Check if any tanks are touching any other tanks in the back.
	std::vector<Vector2f> aTankVertex, bTankVertex;
	aTankVertex.push_back(aTank.frontLeft());	// 0 - Front Left
	aTankVertex.push_back(aTank.frontRight()); // 1 - Front Right
	aTankVertex.push_back(aTank.backRight()); // 2 - back Right
	aTankVertex.push_back(aTank.backLeft()); // 3 - back left

	bTankVertex.push_back(bTank.frontLeft());	// 0 - Front Left
	bTankVertex.push_back(bTank.frontRight()); // 1 - Front Right
	bTankVertex.push_back(bTank.backRight()); // 2 - back Right
	bTankVertex.push_back(bTank.backLeft()); // 3 - back left

	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2f aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2f aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2f bTankCenter{bTank.getPosition()};

		double frontDistance = sqrt(pow(aTankFront.x - bTankCenter.x, 2) + pow(aTankFront.y - bTankCenter.y, 2));
		double backDistance = sqrt(pow(aTankBack.x - bTankCenter.x, 2) + pow(aTankBack.y - bTankCenter.y, 2));

		if(frontDistance > backDistance)
			return true;
		else return false;
	}
	else
		return false;
}


bool Battle::isPolyCollision(std::vector<Vector2f> & aVertex, std::vector<Vector2f> & bVertex)
{
	// Check for a collision between any two polygons.
	Vector2f polyAxis{0,0};
	double tmp, minA, maxA, minB, maxB;

	for (unsigned int polySide = 0; polySide < aVertex.size(); polySide++)
	{
		// Get the axis that we will project onto.
		if (polySide == 0)
		{
			polyAxis.y = aVertex[aVertex.size() - 1].y - aVertex[0].y;
			polyAxis.x = aVertex[aVertex.size() - 1].x - aVertex[0].x;
		}
		else
		{
			polyAxis.y = aVertex[polySide].y - aVertex[polySide - 1].y;
			polyAxis.x = aVertex[polySide].x - aVertex[polySide - 1].x;
		}
		// Project A onto axis. (Dot product)
		minA = maxA = aVertex[0].x * polyAxis.x + aVertex[0].y * polyAxis.y;
		for(unsigned int i = 1; i < aVertex.size(); i++)
		{
			tmp = aVertex[i].x * polyAxis.x + aVertex[i].y * polyAxis.y;
			if(tmp > maxA)
				maxA = tmp;
			else if (tmp < minA)
				minA = tmp;
		}

		// Project B onto axis.

		minB = maxB = bVertex[0].x * polyAxis.x + bVertex[0].y * polyAxis.y;
		for(unsigned int i = 1; i < bVertex.size(); i++)
		{
			tmp = bVertex[i].x * polyAxis.x + bVertex[i].y * polyAxis.y;
			if(tmp > maxB)
				maxB = tmp;
			else if (tmp < minB)
				minB = tmp;
		}

		if(maxA < minB || minA > maxB)
			return false;
	}

	// If the object only has on vertex then a single check is needed.
	if(bVertex.size() > 1)
	{
		for (unsigned int polySide = 0; polySide < bVertex.size(); polySide++)
		{
			// Get projection axis.
			if (polySide == 0)
			{
				polyAxis.y = bVertex[bVertex.size() - 1].y - bVertex[0].y;
				polyAxis.x = bVertex[bVertex.size() - 1].x - bVertex[0].x;
			}
			else
			{
				polyAxis.y = bVertex[polySide].y - bVertex[polySide - 1].y;
				polyAxis.x = bVertex[polySide].x - bVertex[polySide - 1].x;
			}
			// Project A onto axis. (Dot product)
			minA = maxA = aVertex[0].x * polyAxis.x + aVertex[0].y * polyAxis.y;
			for(unsigned int i = 1; i < aVertex.size(); i++)
			{
				tmp = aVertex[i].x * polyAxis.x + aVertex[i].y * polyAxis.y;
				if(tmp > maxA)
					maxA = tmp;
				else if (tmp < minA)
					minA = tmp;
			}

			// Project B onto axis.
			minB = maxB = bVertex[0].x * polyAxis.x + bVertex[0].y * polyAxis.y;
			for(unsigned int i = 1; i < bVertex.size(); i++)
			{
				tmp = bVertex[i].x * polyAxis.x + bVertex[i].y * polyAxis.y;
				if(tmp > maxB)
					maxB = tmp;
				else if (tmp < minB)
					minB = tmp;
			}

			if(maxA < minB || minA > maxB)
				return false;
		}
	}

	return true;
}

void Battle::makeMap()
{
	Vector2f tempVect;
	RectSize tempRect;
	// First Obstacle
	tempRect.Width = _screenDimensions.x * 3 / 5;
	tempRect.Height = _screenDimensions.y * 1/8;
	tempVect.x = _screenDimensions.x/2;
	tempVect.y = _screenDimensions.y /6;
	std::unique_ptr<Obstacle> newObstacle(new Obstacle{tempVect, tempRect});
	_obstacles.push_back(std::move(newObstacle));
	// Second Obstacle
	tempVect.y = _screenDimensions.y - _screenDimensions.y /6;
	newObstacle = std::unique_ptr<Obstacle>(new Obstacle{tempVect, tempRect});
	_obstacles.push_back(std::move(newObstacle));
	// Third Obstacle
	tempRect.Width = _screenDimensions.x/16;
	tempRect.Height = _screenDimensions.y/4;
	tempVect.x = _screenDimensions.x/4;
	tempVect.y = _screenDimensions.y/2;
	newObstacle = std::unique_ptr<Obstacle>(new Obstacle{tempVect, tempRect});
	_obstacles.push_back(std::move(newObstacle));
	// Forth Obstacle
	tempVect.x = _screenDimensions.x - _screenDimensions.x/4;
	newObstacle = std::unique_ptr<Obstacle>(new Obstacle{tempVect, tempRect});
	_obstacles.push_back(std::move(newObstacle));
}
