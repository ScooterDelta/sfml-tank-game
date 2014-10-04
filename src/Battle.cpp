// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Battle.cpp

#include "Battle.h"

Battle::Battle(Vector2D screenDimensions) :
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

	placeTurrets();
}

void Battle::moveTank(Score::PLAYER player, Tank::Direction direction)
{

	// The tank is not allowed to exist inside of an obstacle, if it enters into
	// an obstacle it is then moved out again.
	if(player == Score::PLAYER1)
	{
		moveTank(direction, _tank1, _tank2);
	}
	else if (player == Score::PLAYER2)
	{
		moveTank(direction, _tank2, _tank1);
	}
}

void Battle::moveTank(Score::PLAYER player, Tank::Movement movement)
{
	// The tank is not allowed to exist inside of an obstacle, if it enters into
	// an obstacle it is then moved out again.
	// If the tank collides with a barrier it is allowed to slide along the barrier,
	// but not to pass through it. The following condition checks ensure this.
	if(player == Score::PLAYER1)
	{
		moveTank(movement, _tank1, _tank2);
	}
	else if (player == Score::PLAYER2)
	{
		moveTank(movement, _tank2, _tank1);
	}
}

// Function to do movements on tank A, checking position of tank B.
void Battle::moveTank(Tank::Movement movement, Tank & tankA, Tank & tankB)
{
	bool isHorizontal = false;
	// Act on tank1 (collisions with walls)
	if(movement == Tank::FORWARD && !isFrontWallCollision(tankA, isHorizontal)
			&&  !isFrontTankCollision(tankA, tankB))
		tankA.setMovement(movement);
	else if (movement == Tank::BACKWARD && !isBackWallCollision(tankA, isHorizontal)
			&& !isBackTankCollision(tankA, tankB))
		tankA.setMovement(movement);
	else if (isFrontWallCollision(tankA, isHorizontal) && isBackWallCollision(tankA, isHorizontal))
		tankA.setMovement(Tank::NONE);
	else if (movement == Tank::FORWARD && (isFrontWallCollision(tankA, isHorizontal)
			||  isFrontTankCollision(tankA, tankB)))
	{
		while(isFrontWallCollision(tankA, isHorizontal) || isFrontTankCollision(tankA, tankB))
			tankA.setMovement(Tank::BACKWARD, 0, 0.01);
		tankA.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
		if(isFrontWallCollision(tankA, isHorizontal) || isFrontTankCollision(tankA, tankB))
		{
			tankA.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
			tankA.setMovement(Tank::FORWARDOBSTACLE, !isHorizontal);
		}
		tankA.setMovement(Tank::FORWARD, 0, 0.01);
	}
	else if (movement == Tank::BACKWARD && (isBackWallCollision(tankA, isHorizontal)
			||  isBackTankCollision(tankA, _tank2)))
	{
		while(isBackWallCollision(tankA, isHorizontal) || isBackTankCollision(tankA, tankB))
			tankA.setMovement(Tank::FORWARD, 0, 0.01);
		tankA.setMovement(Tank::BACKWARDOBSTACLE, isHorizontal);
		if(isBackWallCollision(tankA, isHorizontal) || isBackTankCollision(tankA, tankB))
		{
			tankA.setMovement(Tank::FORWARDOBSTACLE, isHorizontal);
			tankA.setMovement(Tank::BACKWARDOBSTACLE, !isHorizontal);
		}
		tankA.setMovement(Tank::BACKWARD, 0, 0.01);
	}
	else if(movement == Tank::NONE && (isBackWallCollision(tankA, isHorizontal)
			|| isBackTankCollision(tankA, tankB)))
		tankA.setMovement(Tank::NONE, 0, 0);
	else if(movement == Tank::NONE && (isFrontWallCollision(tankA, isHorizontal)
			|| isFrontTankCollision(tankA, tankB)))
		tankA.setMovement(Tank::NONE, 0, 0);
	else
		tankA.setMovement(Tank::NONE);
}

// Function to do movements on tank A, checking position of tank B.
void Battle::moveTank(Tank::Direction direction, Tank & tankA, Tank & tankB)
{
	bool isHorizontal = false;
	// Act on tank1 (collisions with walls)
	if (isFrontWallCollision(tankA, isHorizontal)
			||  isFrontTankCollision(tankA, tankB))
	{
		while(isFrontWallCollision(_tank1, isHorizontal) || isFrontTankCollision(tankA, tankB))
			tankA.setMovement(Tank::BACKWARD, 0.1);
		tankA.setMovement(Tank::FORWARD, 0.1);
	}
	else if (isBackWallCollision(_tank1, isHorizontal)
			||  isBackTankCollision(tankA, tankB))
	{
		while(isBackWallCollision(tankA, isHorizontal) || isBackTankCollision(tankA, tankB))
			tankA.setMovement(Tank::FORWARD, 0.1);
		tankA.setMovement(Tank::BACKWARD, 0.1);
	}
	tankA.setMovement(direction);
}

void Battle::update()
{
	missileHitTurret();

	auto turretIter = _turrets.begin();
	while(turretIter != _turrets.end())
	{
		if((*turretIter)->canFollowTarget(_tank1, _tank1.isInvisible()) && (*turretIter)->canFireMissile())
		{
			std::unique_ptr<Missile> newMissile(new Missile{(*turretIter)->getFirePosition(), (*turretIter)->getDirection(), Score::NONPLAYER});
			_missiles.push_back(std::move(newMissile));
		}
		else if ((*turretIter)->canFollowTarget(_tank2, _tank2.isInvisible()) && (*turretIter)->canFireMissile())
		{
			std::unique_ptr<Missile> newMissile(new Missile{(*turretIter)->getFirePosition(), (*turretIter)->getDirection(), Score::NONPLAYER});
			_missiles.push_back(std::move(newMissile));
		}
		else
			(*turretIter)->update();

		++turretIter;
	}


	// Check that missiles are not colliding, if they are either bounce them or
	// display an explosion.
	checkMissiles();

	// Check if the missiles have hit any tanks.
	missileHit(_tank1);
	missileHit(_tank2);

	// Check if a tank has driven over a mine.
	mineHit(_tank1);
	mineHit(_tank2);

	// Iterate through explosions, remove them from the screen if their life time
	// has expired.
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
	Vector2D _missilePos;
	bool _collisionHorizontal = false;
	auto _missileIterator = _missiles.begin();
	// Check collisions against all objects on the screen.
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

bool Battle::isMissileWallCollision(Vector2D & _missilePos, bool & isHorizontal)
{
	// Check the particular missile against all obstacles.
	auto _obstacleIter = _obstacles.begin();
	Vector2D tempObstacleTL, tempObstacleBR;
	while(_obstacleIter != _obstacles.end())
	{
		tempObstacleTL = (*_obstacleIter)->getTopLeft();
		tempObstacleBR = (*_obstacleIter)->getBottomRight();
		// See if missile is inside the bounds of this object.
		if(_missilePos.x >= tempObstacleTL.x && _missilePos.x <= tempObstacleBR.x
				&& _missilePos.y <= tempObstacleBR.y && _missilePos.y >= tempObstacleTL.y)
		{
			// Check if the collision is with a horizontal or vertical surface.
			isHorizontal = checkIsHorizontal(_missilePos, **_obstacleIter);

			if((*_obstacleIter)->isDestroyable())
				_obstacleIter = _obstacles.erase(_obstacleIter);

			return true;
		}

		++_obstacleIter;
	}
	// Check if the missile has collided with the screen boundaries.
	if(_missilePos.x < 0 || _missilePos.y < 0 ||
			_missilePos.x > (_screenDimensions.x - 10) ||
			_missilePos.y > (_screenDimensions.y - 10))
	{
		// Check if the collision is with a horizontal or vertical surface.
		isHorizontal = checkIsHorizontal(_missilePos);

		return true;
	}
	else
		return false;
}

bool Battle::checkIsHorizontal(Vector2D & point, AxisAligned & obstacle)
{
	// Check if the collision with the obstacle is horizontal or not
	Vector2D tempObstacleTL{obstacle.getTopLeft()};
	Vector2D tempObstacleBR{obstacle.getBottomRight()};
	// Calculate the distance of each point from the wall.
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

bool Battle::checkIsHorizontal(Vector2D & point)
{
	// Check that the collision with the screen boundaries is horizontal or not.
	if(point.x < 0 || point.x > (_screenDimensions.x - 10))
		return false;
	else return true;
}

void Battle::fireMissile(Score::PLAYER player)
{
	// Fire a missile for the particular player in the direction that it is facing.
	Vector2D turret;
	if(player == Score::PLAYER1 && (clock() - _missileTimer1) > 500)
	{
		turret.x = (_tank1.getFrontLeft().x + _tank1.getFrontRight().x)/2;
		turret.y = (_tank1.getFrontRight().y + _tank1.getFrontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank1.getDirection(), player});
		_missiles.push_back(std::move(newMissile));

		_missileTimer1 = clock();
	}
	else if (player == Score::PLAYER2 && (clock() - _missileTimer2) > 500)
	{
		turret.x = (_tank2.getFrontLeft().x + _tank2.getFrontRight().x)/2;
		turret.y = (_tank2.getFrontRight().y + _tank2.getFrontLeft().y)/2;

		std::unique_ptr<Missile> newMissile(new Missile{turret, _tank2.getDirection(), player});
		_missiles.push_back(std::move(newMissile));

		_missileTimer2 = clock();
	}

}

void Battle::plantMine(Score::PLAYER player)
{
	// Plant a mine from the location of the tank related to player.
	if(player == Score::PLAYER1 && (clock() - _mineTimer1) > 1000 &&  _tank1.getAllowedMines() != 0)
	{
		std::unique_ptr<Mine> newMine(new Mine{_tank1.getPosition(), Score::PLAYER1});
		_mines.push_back(std::move(newMine));

		_tank1.plantMine();

		_mineTimer1 = clock();
	}
	else if (player == Score::PLAYER2 && (clock() - _mineTimer2) > 1000 &&  _tank2.getAllowedMines() != 0)
	{
		std::unique_ptr<Mine> newMine(new Mine{_tank2.getPosition(), Score::PLAYER2});
		_mines.push_back(std::move(newMine));

		_tank2.plantMine();

		_mineTimer2 = clock();
	}
}

void Battle::turnInvisible(Score::PLAYER player)
{
	if(player == Score::PLAYER1)
		_tank1.turnInvisible();
	else if (player == Score::PLAYER2)
		_tank2.turnInvisible();
}

Tank * Battle::getTank1()
{
	// Return a pointer to tank 1.
	return & _tank1;
}

Tank * Battle::getTank2()
{
	// Return a pointer to tank 2.
	return & _tank2;
}

std::list<std::unique_ptr<Turret>> * Battle::getTurrets()
{
	return & _turrets;
}

std::list<std::unique_ptr<Missile>> * Battle::getMissiles()
{
	// Return a pointer to list of missiles.
	return & _missiles;
}

std::list<std::unique_ptr<Explosion>> * Battle::getExplosions()
{
	// Return a pointer to list of explosions.
	return & _explosions;
}

std::list<std::unique_ptr<Obstacle>> * Battle::getObstacles()
{
	// Return a pointer to list of obstacles.
	return & _obstacles;
}

std::list<std::unique_ptr<Mine>> * Battle::getMines()
{
	// Return a pointer to list of mines.
	return & _mines;
}

Score Battle::getScore()
{
	// Return the score.
	return _score;
}

bool Battle::isFrontWallCollision(Tank & tank, bool & isHorizontal)
{
	// Check for a collision with a wall infront of the tank.
	Vector2D tempContainerFL = tank.getFrontLeft();
	Vector2D tempContainerFR = tank.getFrontRight();
	Vector2D tempContainerFM;

	// Get the front middle of the tank for more accurate collision detection.
	tempContainerFM.x = (tank.getFrontLeft().x + tank.getFrontRight().x)/2;
	tempContainerFM.y = (tank.getFrontLeft().y + tank.getFrontRight().y)/2;

	if(isWallCollision(tempContainerFL, isHorizontal) || isWallCollision(tempContainerFR, isHorizontal)
			|| isWallCollision(tempContainerFM, isHorizontal))
		return true;
	else return false;
}

bool Battle::isBackWallCollision(Tank & tank, bool & isHorizontal)
{
	// Check for a collision with a wall behind the tank.
	Vector2D tempContainerBL = tank.getBackLeft();
	Vector2D tempContainerBR = tank.getBackRight();
	Vector2D tempContainerBM;

	// Get the front middle of the tank for more accurate collision detection.
	tempContainerBM.x = (tank.getBackLeft().x + tank.getBackRight().x)/2;
	tempContainerBM.y = (tank.getBackLeft().y + tank.getBackRight().y)/2;

	if(isWallCollision(tempContainerBL, isHorizontal) || isWallCollision(tempContainerBR, isHorizontal)
			|| isWallCollision(tempContainerBM, isHorizontal))
		return true;
	else return false;
}

bool Battle::isWallCollision(Vector2D position, bool & isHorizontal)
{
	Vector2D tempObstacleTL, tempObstacleBR;
	// Check collisions with the bounds of the screen.
	if (position.x < 0 || position.y < 0 || position.x > _screenDimensions.x || position.y > _screenDimensions.y)
	{
		isHorizontal = checkIsHorizontal(position);
		return true;
	}
	// Check for a collision with the point against each obstacle.
	// if a collision occurs then check if it is vertical or horizontal collision.
	else
	{
		auto _obstacleIter = _obstacles.begin();
		while(_obstacleIter != _obstacles.end())
		{
			tempObstacleTL = (*_obstacleIter)->getTopLeft();
			tempObstacleBR = (*_obstacleIter)->getBottomRight();
			if(position.x > tempObstacleTL.x && position.x < tempObstacleBR.x
					&& position.y < tempObstacleBR.y && position.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(position, **_obstacleIter);
				return true;
			}
			else
				++_obstacleIter;
		}
		// Check for vehicle collision with turrets.
		auto _turretIter = _turrets.begin();
		while(_turretIter != _turrets.end())
		{
			tempObstacleTL = (*_turretIter)->getTopLeft();
			tempObstacleBR = (*_turretIter)->getBottomRight();
			if(position.x > tempObstacleTL.x && position.x < tempObstacleBR.x
					&& position.y < tempObstacleBR.y && position.y > tempObstacleTL.y)
			{
				isHorizontal = checkIsHorizontal(position, **_turretIter);
				return true;
			}
			else
				++_turretIter;
		}
		return false;
	}
}

void Battle::missileHit(Tank & tank)
{
	// Check if any missiles have hit any tanks. If they have the tank takes damage.
	std::vector<Vector2D> tankVertex;
	tankVertex.push_back(tank.getFrontLeft());	// 0 - Front Left
	tankVertex.push_back(tank.getFrontRight()); // 1 - Front Right
	tankVertex.push_back(tank.getBackRight()); // 2 - back Right
	tankVertex.push_back(tank.getBackLeft()); // 3 - back left

	// Helper variables.
	Score::PLAYER tempTankPlayer, tempMissilePlayer;
	tempTankPlayer = tank.getPlayer();

	Vector2D _missileCenter;
	std::vector<Vector2D> _missileVertex;

	auto _missileIterator = _missiles.begin();
	// For all missiles on the screen check if they collide with a tank.
	while(_missileIterator != _missiles.end())
	{
		_missileCenter.x = (*_missileIterator)->getPosition().x;
		_missileCenter.y = (*_missileIterator)->getPosition().y;
		_missileVertex.clear();
		_missileVertex.push_back(_missileCenter);
		if(isPolyCollision(tankVertex, _missileVertex))
		{
			tempMissilePlayer = (*_missileIterator)->getPlayer();

			// If the missile hits a tank then display an explosion.
			std::unique_ptr<Explosion> newExplosion(new Explosion{(*_missileIterator)->getPosition()});
			_explosions.push_back(std::move(newExplosion));
			_missileIterator = _missiles.erase(_missileIterator);

			// Check who the owner of the missile is in order to count kill toward a particular
			// character.
			playerHit(tempTankPlayer, tempMissilePlayer);

			break;
		}
		else
			++_missileIterator;
	}
}

void Battle::missileHitTurret()
{
	// Check the particular missile against all obstacles.
	auto _missileIter = _missiles.begin();
	auto _turretIter = _turrets.begin();
	Vector2D tempTurretTL, tempTurretBR, _missilePos;

	while(_turretIter != _turrets.end())
	{
		_missileIter = _missiles.begin();
		while(_missileIter != _missiles.end())
		{
			_missilePos = (*_missileIter)->getPosition();
			tempTurretTL = (*_turretIter)->getTopLeft();
			tempTurretBR = (*_turretIter)->getBottomRight();
			// See if missile is inside the bounds of this object.
			if(_missilePos.x >= tempTurretTL.x && _missilePos.x <= tempTurretBR.x
					&& _missilePos.y <= tempTurretBR.y && _missilePos.y >= tempTurretTL.y)
			{
				// If the missile hits a turret then display an explosion.
				std::unique_ptr<Explosion> newExplosion(new Explosion{(*_missileIter)->getPosition()});
				_explosions.push_back(std::move(newExplosion));

				_missileIter = _missiles.erase(_missileIter);

				// Delete the turret that it hit.
				_turretIter = _turrets.erase(_turretIter);
			}
			else
				++_missileIter;
		}
		++_turretIter;
	}
}

void Battle::mineHit(Tank & tank)
{
	// Check if any missiles have hit any tanks. If they have the tank takes damage.
	Vector2D _mineCenter;
	bool isCollision;
	std::vector<Vector2D> _mineVertex, tankVertex;
	tankVertex.push_back(tank.getFrontLeft());	// 0 - Front Left
	tankVertex.push_back(tank.getFrontRight()); // 1 - Front Right
	tankVertex.push_back(tank.getBackRight()); // 2 - back Right
	tankVertex.push_back(tank.getBackLeft()); // 3 - back left

	// Helper variables.
	Score::PLAYER tempTankPlayer, tempMinePlayer;
	tempTankPlayer = tank.getPlayer();

	auto _mineIterator = _mines.begin();
	// Check collisions with all mines on the screen.
	while(_mineIterator != _mines.end())
	{
		_mineCenter.x = (*_mineIterator)->getPosition().x;
		_mineCenter.y = (*_mineIterator)->getPosition().y;

		_mineVertex.clear();
		_mineVertex.push_back(_mineCenter);

		// Check if the tank has driven off the mine the first time,
		// this prevents accidental suicide from planting the mine.
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

			// If the mine is detonated then display an explosion animation.

			std::unique_ptr<Explosion> newExplosion(new Explosion{_mineCenter});
			_explosions.push_back(std::move(newExplosion));
			_mineIterator = _mines.erase(_mineIterator);

			// Check who the owner of the mine is in order to count kill toward a particular
			// character.
			playerHit(tempTankPlayer, tempMinePlayer);

			break;
		}
		else
			++_mineIterator;
	}
}

void Battle::playerHit(Score::PLAYER player, Score::PLAYER projectileOwner)
{
	if(player == Score::PLAYER1 && (projectileOwner == Score::PLAYER1
			|| projectileOwner == Score::NONPLAYER))
		_score.increaseDeaths(Score::PLAYER1);
	else if(player == Score::PLAYER2 && (projectileOwner == Score::PLAYER2
			|| projectileOwner == Score::NONPLAYER))
		_score.increaseDeaths(Score::PLAYER2);
	else if(player == Score::PLAYER2 && projectileOwner == Score::PLAYER1)
	{
		_score.increaseKills(Score::PLAYER1);
		_score.increaseDeaths(Score::PLAYER2);
	}
	else if(player == Score::PLAYER1 && projectileOwner == Score::PLAYER2)
	{
		_score.increaseKills(Score::PLAYER2);
		_score.increaseDeaths(Score::PLAYER1);
	}

	// Respawn both tanks to prevent an unfair spawn advantage.
	_tank1.respawn();
	_tank2.respawn();

	// Replace turrets.
	placeTurrets();

	// Clear the missiles and mines from the screen to prevent accidental deaths from respawning.
	_missiles.clear();
	_mines.clear();
}

bool Battle::isFrontTankCollision(Tank & aTank, Tank & bTank)
{
	// Check if any tanks are touching any other tanks in front .
	std::vector<Vector2D> aTankVertex, bTankVertex;
	aTankVertex.push_back(aTank.getFrontLeft());	// 0 - Front Left
	aTankVertex.push_back(aTank.getFrontRight()); // 1 - Front Right
	aTankVertex.push_back(aTank.getBackRight()); // 2 - back Right
	aTankVertex.push_back(aTank.getBackLeft()); // 3 - back left

	bTankVertex.push_back(bTank.getFrontLeft());	// 0 - Front Left
	bTankVertex.push_back(bTank.getFrontRight()); // 1 - Front Right
	bTankVertex.push_back(bTank.getBackRight()); // 2 - back Right
	bTankVertex.push_back(bTank.getBackLeft()); // 3 - back left

	// Check if a collision has happened between two objects.
	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2D aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2D aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2D bTankCenter{bTank.getPosition()};

		// Calculate distance between front and back of object to test if front or back collision.
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
	std::vector<Vector2D> aTankVertex, bTankVertex;
	aTankVertex.push_back(aTank.getFrontLeft());	// 0 - Front Left
	aTankVertex.push_back(aTank.getFrontRight()); // 1 - Front Right
	aTankVertex.push_back(aTank.getBackRight()); // 2 - back Right
	aTankVertex.push_back(aTank.getBackLeft()); // 3 - back left

	bTankVertex.push_back(bTank.getFrontLeft());	// 0 - Front Left
	bTankVertex.push_back(bTank.getFrontRight()); // 1 - Front Right
	bTankVertex.push_back(bTank.getBackRight()); // 2 - back Right
	bTankVertex.push_back(bTank.getBackLeft()); // 3 - back left

	// Check if a collision has happened between two objects.
	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2D aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2D aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2D bTankCenter{bTank.getPosition()};

		// Calculate distance between front and back of object to test if front or back collision.
		double frontDistance = sqrt(pow(aTankFront.x - bTankCenter.x, 2) + pow(aTankFront.y - bTankCenter.y, 2));
		double backDistance = sqrt(pow(aTankBack.x - bTankCenter.x, 2) + pow(aTankBack.y - bTankCenter.y, 2));

		if(frontDistance > backDistance)
			return true;
		else return false;
	}
	else
		return false;
}


bool Battle::isPolyCollision(std::vector<Vector2D> & aVertex, std::vector<Vector2D> & bVertex)
{
	// Check for a collision between any two polygons.
	Vector2D polyAxis{0,0};
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
	fillObstacle({6.f, 2.f},{20.f, 2.f}, Obstacle::BRICK);
	// Bottom obstacle:
	fillObstacle({6.f, 14.f},{20.f, 2.f}, Obstacle::BRICK);
	// Left obstacle:
	fillObstacle({6.f, 6.f},{2.f, 6.f}, Obstacle::BOX);
	// Right obstacle:
	fillObstacle({24.f, 6.f},{2.f, 6.f}, Obstacle::BOX);
	// Top under obstacle:
	fillObstacle({11.f, 4.f},{10.f, 1.f}, Obstacle::BRICK);
	// Bottom over obstacle:
	fillObstacle({11.f, 13.f},{10.f, 1.f}, Obstacle::BRICK);
}

void Battle::placeTurrets()
{
	_turrets.clear();

	std::unique_ptr<Turret> newTurret(new Turret{{_screenDimensions.x/2,
			_screenDimensions.y * 13/18 - 20}, {10, 170}, _screenDimensions});
	_turrets.push_back(std::move(newTurret));

	newTurret = std::unique_ptr<Turret>(new Turret{{_screenDimensions.x/2,
			_screenDimensions.y * 5/18 + 20}, {190, 350}, _screenDimensions});
	_turrets.push_back(std::move(newTurret));
}

void Battle::fillObstacle(Vector2D location, Vector2D size, Obstacle::TEXTURE texture)
{
	// Fill up an area starting from top left (location) for the size.
	// Uses small objects that are predefined.
	std::unique_ptr<Obstacle> newObstacle;
	Vector2D tempVect;
	tempVect.x = _screenDimensions.x/32;
	tempVect.y = _screenDimensions.y/18;
	for(int i = 0; i < size.y; i++)
	{
		for(int j = 0; j < size.x; j++)
		{
			newObstacle = std::unique_ptr<Obstacle>(new Obstacle
					{{tempVect.x * (location.x + j), tempVect.y *
						(location.y + i)}, _screenDimensions, texture});
			_obstacles.push_back(std::move(newObstacle));
		}
	}
}

void Battle::restartBattle()
{
	// Reset all values to their initial conditions to restart the battle.
	_tank1.respawn();
	_tank2.respawn();
	_obstacles.clear();
	_missiles.clear();
	_explosions.clear();
	_mines.clear();
	_score = Score{0,0};
	makeMap();
	placeTurrets();
}
