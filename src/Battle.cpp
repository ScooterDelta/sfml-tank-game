#include "Battle.h"

Battle::Battle(Vector2f screenDimensions) :
	_screenDimensions{screenDimensions},
	_tank1{{200, screenDimensions.y/2}, Score::PLAYER1, screenDimensions},
	_tank2{{screenDimensions.x - 200, screenDimensions.y/2}, Score::PLAYER2, screenDimensions},
	_missileTimer1{clock() - 600},
	_missileTimer2{clock() - 600},
	_mineTimer1{clock() - 1200},
	_mineTimer2{clock() - 1200},
	_score{0, 0}
{
	// Make the map for the game.
	makeMap();
}

void Battle::moveTank(Score::PLAYER player, Tank::Direction direction)
{
	bool isHorizontal = false;
	if(player == Score::PLAYER1)
	{
		// Act on tank1 (collisions with walls)
		if (isFrontWallCollision(_tank1, isHorizontal)
				||  isFrontTankCollision(_tank1, _tank2))
		{
			while(isFrontWallCollision(_tank1, isHorizontal) || isFrontTankCollision(_tank1, _tank2))
				_tank1.setMovement(Tank::BACKWARD, 0.1);
			_tank1.setMovement(Tank::FORWARD, 0.1);
		}
		else if (isBackWallCollision(_tank1, isHorizontal)
				||  isBackTankCollision(_tank1, _tank2))
		{
			while(isBackWallCollision(_tank1, isHorizontal) || isBackTankCollision(_tank1, _tank2))
				_tank1.setMovement(Tank::FORWARD, 0.1);
			_tank1.setMovement(Tank::BACKWARD, 0.1);
		}
		_tank1.setMovement(direction);
	}
	else if (player == Score::PLAYER2)
	{
		// Act on tank2 (collisions with walls)
		if (isFrontWallCollision(_tank2, isHorizontal)
				||  isFrontTankCollision(_tank2, _tank1))
		{
			while(isFrontWallCollision(_tank2, isHorizontal) || isFrontTankCollision(_tank2, _tank1))
				_tank2.setMovement(Tank::BACKWARD, 0.1);
			_tank2.setMovement(Tank::FORWARD, 0.1);
		}
		else if (isBackWallCollision(_tank2, isHorizontal)
				||  isBackTankCollision(_tank2, _tank1))
		{
			while(isBackWallCollision(_tank2, isHorizontal) || isBackTankCollision(_tank2, _tank1))
				_tank2.setMovement(Tank::FORWARD, 0.1);
			_tank2.setMovement(Tank::BACKWARD, 0.1);
		}
		_tank2.setMovement(direction);
	}
}

void Battle::moveTank(Score::PLAYER player, Tank::Movement movement)
{
	bool isHorizontal = false;
	if(player == Score::PLAYER1)
	{
		// Act on tank1 (collisions with walls)
		if(movement == Tank::FORWARD && !isFrontWallCollision(_tank1, isHorizontal)
				&&  !isFrontTankCollision(_tank1, _tank2))
			_tank1.setMovement(movement);
		else if (movement == Tank::BACKWARD && !isBackWallCollision(_tank1, isHorizontal)
				&& !isBackTankCollision(_tank1, _tank2))
			_tank1.setMovement(movement);
		else if (isFrontWallCollision(_tank1, isHorizontal) && isBackWallCollision(_tank1, isHorizontal))
			_tank1.setMovement(Tank::NONE);
		else if (movement == Tank::FORWARD && (isFrontWallCollision(_tank1, isHorizontal)
				||  isFrontTankCollision(_tank1, _tank2)))
		{
			while(isFrontWallCollision(_tank1, isHorizontal) || isFrontTankCollision(_tank1, _tank2))
				_tank1.setMovement(Tank::BACKWARD, 0, 0.01);
			_tank1.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
			if(isFrontWallCollision(_tank1, isHorizontal) || isFrontTankCollision(_tank1, _tank2))
			{
				_tank1.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
				_tank1.setMovement(Tank::FORWARDOBSTACLE, !isHorizontal);
			}
			_tank1.setMovement(Tank::FORWARD, 0, 0.01);
		}
		else if (movement == Tank::BACKWARD && (isBackWallCollision(_tank1, isHorizontal)
				||  isBackTankCollision(_tank1, _tank2)))
		{
			while(isBackWallCollision(_tank1, isHorizontal) || isBackTankCollision(_tank1, _tank2))
				_tank1.setMovement(Tank::FORWARD, 0, 0.01);
			_tank1.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
			if(isBackWallCollision(_tank1, isHorizontal) || isBackTankCollision(_tank1, _tank2))
			{
				_tank1.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
				_tank1.setMovement(Tank::BACKWARDOBSTACLE, !isHorizontal);
			}
			_tank1.setMovement(Tank::BACKWARD, 0, 0.01);
		}
		else if(movement == Tank::NONE && (isBackWallCollision(_tank1, isHorizontal)
				|| isBackTankCollision(_tank1, _tank2)))
			_tank1.setMovement(Tank::NONE, 0, 0);
		else if(movement == Tank::NONE && (isFrontWallCollision(_tank1, isHorizontal)
				|| isFrontTankCollision(_tank1, _tank2)))
			_tank1.setMovement(Tank::NONE, 0, 0);
		else
			_tank1.setMovement(Tank::NONE);
	}
	else if (player == Score::PLAYER2)
	{
		// Act on tank2 (collisions with walls)
		if(movement == Tank::FORWARD && !isFrontWallCollision(_tank2, isHorizontal)
				&&  !isFrontTankCollision(_tank2, _tank1))
			_tank2.setMovement(movement);
		else if (movement == Tank::BACKWARD && !isBackWallCollision(_tank2, isHorizontal)
				&& !isBackTankCollision(_tank2, _tank1))
			_tank2.setMovement(movement);
		else if (isFrontWallCollision(_tank2, isHorizontal) && isBackWallCollision(_tank2, isHorizontal))
			_tank2.setMovement(Tank::NONE);
		else if (movement == Tank::FORWARD && (isFrontWallCollision(_tank2, isHorizontal)
				||  isFrontTankCollision(_tank2, _tank1)))
		{
			while(isFrontWallCollision(_tank2, isHorizontal) || isFrontTankCollision(_tank2, _tank1))
				_tank2.setMovement(Tank::BACKWARD, 0, 0.01);
			_tank2.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
			if(isFrontWallCollision(_tank2, isHorizontal) || isFrontTankCollision(_tank2, _tank1))
			{
				_tank2.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
				_tank2.setMovement(Tank::FORWARDOBSTACLE, !isHorizontal);
			}
			_tank2.setMovement(Tank::FORWARD, 0, 0.01);
		}
		else if (movement == Tank::BACKWARD && (isBackWallCollision(_tank2, isHorizontal)
				||  isBackTankCollision(_tank2, _tank1)))
		{
			while(isBackWallCollision(_tank2, isHorizontal) || isBackTankCollision(_tank2, _tank1))
				_tank2.setMovement(Tank::FORWARD, 0, 0.01);
			_tank2.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
			if(isBackWallCollision(_tank2, isHorizontal) || isBackTankCollision(_tank2, _tank1))
			{
				_tank2.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
				_tank2.setMovement(Tank::BACKWARDOBSTACLE, !isHorizontal);
			}
			_tank2.setMovement(Tank::BACKWARD, 0, 0.01);
		}
		else if(movement == Tank::NONE && (isBackWallCollision(_tank2, isHorizontal)
				|| isBackTankCollision(_tank2, _tank1)))
			_tank2.setMovement(Tank::NONE, 0, 0);
		else if(movement == Tank::NONE && (isFrontWallCollision(_tank2, isHorizontal)
				|| isFrontTankCollision(_tank2, _tank1)))
			_tank2.setMovement(Tank::NONE, 0, 0);
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
		if(clock() - (*_explosionIterator)->getExplosionTime() > 90)
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
	auto _obstacleIter = _obstacles.begin();
	Vector2f tempObstacleTL, tempObstacleBR;
	while(_obstacleIter != _obstacles.end())
	{
		tempObstacleTL = (*_obstacleIter)->topLeft();
		tempObstacleBR = (*_obstacleIter)->bottomRight();
		// See if missile is inside the bounds of this object.
		if(_missilePos.x >= tempObstacleTL.x && _missilePos.x <= tempObstacleBR.x
				&& _missilePos.y <= tempObstacleBR.y && _missilePos.y >= tempObstacleTL.y)
		{
			isHorizontal = checkIsHorizontal(_missilePos, **_obstacleIter);

			if((*_obstacleIter)->isDestroyable())
				_obstacleIter = _obstacles.erase(_obstacleIter);

			return true;
		}

		++_obstacleIter;
	}
	if(_missilePos.x < 0 || _missilePos.y < 0 ||
			_missilePos.x > (_screenDimensions.x - 10) ||
			_missilePos.y > (_screenDimensions.y - 10))
	{
		isHorizontal = checkIsHorizontal(_missilePos);

		return true;
	}
	else
		return false;
}

bool Battle::checkIsHorizontal(Vector2f & point, Obstacle & obstacle)
{
	// Check if the collision with the obstacle is horizontal or not
	Vector2f tempObstacleTL{obstacle.topLeft()};
	Vector2f tempObstacleBR{obstacle.bottomRight()};
	float leftDistance = abs(point.x - tempObstacleTL.x);
	float rightDistance = abs(point.x - tempObstacleBR.x);
	float topDistance = abs(point.y - tempObstacleTL.y);
	float bottomDistance = abs(point.y - tempObstacleBR.y);

	// Check which side the missile is touching on (for bounce).
	if(leftDistance < bottomDistance && leftDistance < topDistance && leftDistance < rightDistance)
		return false;
	else if (rightDistance < bottomDistance && rightDistance < topDistance && rightDistance < leftDistance)
		return false;
	else
		return true;
}

bool Battle::checkIsHorizontal(Vector2f & point)
{
	// Check that the collision with the screen boundaries is horizontal or not.
	if(point.x < 0 || point.x > (_screenDimensions.x - 10))
		return false;
	else return true;
}

void Battle::fireMissile(Score::PLAYER player)
{
	// Fire a missile for the particular player in the direction that it is facing.
	Vector2f turret;
	if(player == Score::PLAYER1 && (clock() - _missileTimer1) > 500)
	{
		turret.x = (_tank1.frontLeft().x + _tank1.frontRight().x)/2;
		turret.y = (_tank1.frontRight().y + _tank1.frontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank1.getDirection(), player});
		_missiles.push_back(std::move(newMissile));

		_missileTimer1 = clock();
	}
	else if (player == Score::PLAYER2 && (clock() - _missileTimer2) > 500)
	{
		turret.x = (_tank2.frontLeft().x + _tank2.frontRight().x)/2;
		turret.y = (_tank2.frontRight().y + _tank2.frontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank2.getDirection(), player});
		_missiles.push_back(std::move(newMissile));

		_missileTimer2 = clock();
	}

}

void Battle::plantMine(Score::PLAYER player)
{
	Vector2f turret;
	if(player == Score::PLAYER1 && (clock() - _mineTimer1) > 1000 &&  _tank1.getAllowedMines() != 0)
	{
		turret.x = (_tank1.backLeft().x + _tank1.backRight().x)/2;
		turret.y = (_tank1.backRight().y + _tank1.backLeft().y)/2;

		std::unique_ptr<Mine> newMine(new Mine{turret, Score::PLAYER1});
		_mines.push_back(std::move(newMine));

		_tank1.plantMine();

		_mineTimer1 = clock();
	}
	else if (player == Score::PLAYER2 && (clock() - _mineTimer2) > 1000 &&  _tank2.getAllowedMines() != 0)
	{
		turret.x = (_tank2.backLeft().x + _tank2.backRight().x)/2;
		turret.y = (_tank2.backRight().y + _tank2.backLeft().y)/2;

		std::unique_ptr<Mine> newMine(new Mine{turret, Score::PLAYER2});
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

Score Battle::getScore()
{
	return _score;
}

bool Battle::isFrontWallCollision(Tank & tank, bool & isHorizontal)
{
	// Check for a collision with a wall infront of the tank.
	Vector2f tempContainerFL = tank.frontLeft();
	Vector2f tempContainerFR = tank.frontRight();
	Vector2f tempContainerFM;

	tempContainerFM.x = (tank.frontLeft().x + tank.frontRight().x)/2;
	tempContainerFM.y = (tank.frontLeft().y + tank.frontRight().y)/2;

	Vector2f tempObstacleTL, tempObstacleBR;

	if (tempContainerFL.x < 0 || tempContainerFL.y < 0 || tempContainerFL.x > _screenDimensions.x || tempContainerFL.y > _screenDimensions.y)
	{
		isHorizontal = checkIsHorizontal(tempContainerFL);
		return true;
	}
	else if (tempContainerFR.x < 0 || tempContainerFR.y < 0 || tempContainerFR.x > _screenDimensions.x || tempContainerFR.y > _screenDimensions.y)
	{
		isHorizontal = checkIsHorizontal(tempContainerFR);
		return true;
	}
	else
	{
		auto _obstacleIter = _obstacles.begin();
		while(_obstacleIter != _obstacles.end())
		{
			tempObstacleTL = (*_obstacleIter)->topLeft();
			tempObstacleBR = (*_obstacleIter)->bottomRight();
			if(tempContainerFL.x > tempObstacleTL.x && tempContainerFL.x < tempObstacleBR.x
					&& tempContainerFL.y < tempObstacleBR.y && tempContainerFL.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerFL, **_obstacleIter);
				return true;
			}
			else if (tempContainerFR.x > tempObstacleTL.x && tempContainerFR.x < tempObstacleBR.x
					&& tempContainerFR.y < tempObstacleBR.y && tempContainerFR.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerFR, **_obstacleIter);
				return true;
			}
			if(tempContainerFM.x > tempObstacleTL.x && tempContainerFM.x < tempObstacleBR.x
					&& tempContainerFM.y < tempObstacleBR.y && tempContainerFM.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerFM, **_obstacleIter);
				return true;
			}

			++_obstacleIter;
		}
		return false;
	}
}

bool Battle::isBackWallCollision(Tank & tank, bool & isHorizontal)
{
	// Check for a collision with a wall behind the tank.
	Vector2f tempContainerBL = tank.backLeft();
	Vector2f tempContainerBR = tank.backRight();
	Vector2f tempContainerBM;

	tempContainerBM.x = (tank.backLeft().x + tank.backRight().x)/2;
	tempContainerBM.y = (tank.backLeft().y + tank.backRight().y)/2;

	Vector2f tempObstacleTL, tempObstacleBR;

	if (tempContainerBL.x < 0 || tempContainerBL.y < 0 || tempContainerBL.x > _screenDimensions.x || tempContainerBL.y > _screenDimensions.y)
	{
		isHorizontal = checkIsHorizontal(tempContainerBL);
		return true;
	}
	else if (tempContainerBR.x < 0 || tempContainerBR.y < 0 || tempContainerBR.x > _screenDimensions.x || tempContainerBR.y > _screenDimensions.y)
	{
		isHorizontal = checkIsHorizontal(tempContainerBR);
		return true;
	}
	else
	{
		auto _obstacleIter = _obstacles.begin();
		while(_obstacleIter != _obstacles.end())
		{
			tempObstacleTL = (*_obstacleIter)->topLeft();
			tempObstacleBR = (*_obstacleIter)->bottomRight();
			if(tempContainerBL.x > tempObstacleTL.x && tempContainerBL.x < tempObstacleBR.x
					&& tempContainerBL.y < tempObstacleBR.y && tempContainerBL.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerBL, **_obstacleIter);
				return true;
			}
			else if (tempContainerBR.x > tempObstacleTL.x && tempContainerBR.x < tempObstacleBR.x
					&& tempContainerBR.y < tempObstacleBR.y && tempContainerBR.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerBR, **_obstacleIter);
				return true;
			}
			else if (tempContainerBM.x > tempObstacleTL.x && tempContainerBM.x < tempObstacleBR.x
					&& tempContainerBM.y < tempObstacleBR.y && tempContainerBM.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(tempContainerBM, **_obstacleIter);
				return true;
			}

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

	Score::PLAYER tempTankPlayer, tempMissilePlayer;
	tempTankPlayer = tank.getPlayer();

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
			tempMissilePlayer = (*_missileIterator)->getPlayer();

			std::unique_ptr<Explosion> newExplosion(new Explosion{(*_missileIterator)->getPosition()});
			_explosions.push_back(std::move(newExplosion));
			_missileIterator = _missiles.erase(_missileIterator);

			if(tempTankPlayer == Score::PLAYER1 && tempMissilePlayer == Score::PLAYER1)
				_score.increaseDeaths(Score::PLAYER1);
			else if(tempTankPlayer == Score::PLAYER2 && tempMissilePlayer == Score::PLAYER2)
				_score.increaseDeaths(Score::PLAYER2);
			else if(tempTankPlayer == Score::PLAYER2 && tempMissilePlayer == Score::PLAYER1)
			{
				_score.increaseKills(Score::PLAYER1);
				_score.increaseDeaths(Score::PLAYER2);
			}
			else if(tempTankPlayer == Score::PLAYER1 && tempMissilePlayer == Score::PLAYER2)
			{
				_score.increaseKills(Score::PLAYER2);
				_score.increaseDeaths(Score::PLAYER1);
			}

			_tank1.respawn();
			_tank2.respawn();

			_missiles.clear();
			_mines.clear();
			break;
		}
		else
			++_missileIterator;
	}
}

void Battle::mineHit(Tank & tank)
{
	// Check if any missiles have hit any tanks. If they have the tank takes damage.
	Vector2f _mineCenter;
	bool isCollision;
	std::vector<Vector2f> _mineVertex, tankVertex;
	tankVertex.push_back(tank.frontLeft());	// 0 - Front Left
	tankVertex.push_back(tank.frontRight()); // 1 - Front Right
	tankVertex.push_back(tank.backRight()); // 2 - back Right
	tankVertex.push_back(tank.backLeft()); // 3 - back left

	Score::PLAYER tempTankPlayer, tempMinePlayer;
	tempTankPlayer = tank.getPlayer();

	auto _mineIterator = _mines.begin();
	while(_mineIterator != _mines.end())
	{
		_mineCenter.x = (*_mineIterator)->getPosition().x;
		_mineCenter.y = (*_mineIterator)->getPosition().y;

		_mineVertex.clear();
		_mineVertex.push_back(_mineCenter);

		isCollision = isPolyCollision(tankVertex, _mineVertex);
		if(!isCollision && !(*_mineIterator)->checkIsActive())
		{
			if(tank.getPlayer() == (*_mineIterator)->getPlayer())
				(*_mineIterator)->activateMine();
			++_mineIterator;
		}
		else if(isCollision && (*_mineIterator)->checkIsActive())
		{
			tempMinePlayer = (*_mineIterator)->getPlayer();

			std::unique_ptr<Explosion> newExplosion(new Explosion{_mineCenter});
			_explosions.push_back(std::move(newExplosion));
			_mineIterator = _mines.erase(_mineIterator);

			if(tempTankPlayer == Score::PLAYER1 && tempMinePlayer == Score::PLAYER1)
				_score.increaseDeaths(Score::PLAYER1);
			else if(tempTankPlayer == Score::PLAYER2 && tempMinePlayer == Score::PLAYER2)
				_score.increaseDeaths(Score::PLAYER2);
			else if(tempTankPlayer == Score::PLAYER2 && tempMinePlayer == Score::PLAYER1)
			{
				_score.increaseKills(Score::PLAYER1);
				_score.increaseDeaths(Score::PLAYER2);
			}
			else if(tempTankPlayer == Score::PLAYER1 && tempMinePlayer == Score::PLAYER2)
			{
				_score.increaseKills(Score::PLAYER2);
				_score.increaseDeaths(Score::PLAYER1);
			}

			_tank1.respawn();
			_tank2.respawn();

			_missiles.clear();
			_mines.clear();
			break;
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
	// Top obstacle:
	fillObstacle({6.f, 2.f},{20.f, 2.f});
	// Bottom obstacle:
	fillObstacle({6.f, 14.f},{20.f, 2.f});
	// Left obstacle:
	fillObstacle({6.f, 6.f},{2.f, 6.f});
	// Right obstacle:
	fillObstacle({24.f, 6.f},{2.f, 6.f});
	// Top under obstacle:
	fillObstacle({11.f, 4.f},{10.f, 1.f});
	// Bottom over obstacle:
	fillObstacle({11.f, 13.f},{10.f, 1.f});
}

void Battle::fillObstacle(Vector2f location, Vector2f size)
{
	// Fill up an area starting from top left (location) for the size.
	// Uses small objects that are predefined.
	std::unique_ptr<Obstacle> newObstacle;
	Vector2f tempVect;
	tempVect.x = _screenDimensions.x/32;
	tempVect.y = _screenDimensions.y/18;
	for(int i = 0; i < size.y; i++)
	{
		for(int j = 0; j < size.x; j++)
		{
			newObstacle = std::unique_ptr<Obstacle>(new Obstacle
					{{tempVect.x * (location.x + j), tempVect.y * (location.y + i)}, _screenDimensions});
			_obstacles.push_back(std::move(newObstacle));
		}
	}
}

void Battle::restartBattle()
{
	_tank1.respawn();
	_tank2.respawn();
	_obstacles.clear();
	_missiles.clear();
	_explosions.clear();
	_mines.clear();
	_score = Score{0,0};
	makeMap();
}
