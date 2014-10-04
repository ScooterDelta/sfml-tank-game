// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Battle.h

#ifndef BATTLE_H_
#define BATTLE_H_

#include <SFML/Graphics.hpp>
#include <list>
#include <ctime>
#include <memory>
#include "Tank.h"
#include "Missile.h"
#include "Obstacle.h"
#include "Explosion.h"
#include "Angle.h"
#include "Mine.h"
#include "Turret.h"
#include "Score.h"

using namespace sf;

class Battle
{
public:
	// Constructor.
	Battle(Vector2D screenDimensions);
	friend class Display;
	// Update the battle, updating all locations and collisions of objects
	void update();
	// Overloaded move functions, for changing direction and movement of tanks.
	void moveTank(Score::PLAYER player, Tank::Direction direction);
	void moveTank(Score::PLAYER player, Tank::Movement movement);
	// Function for a particular tank (player) to fire a missile or plant a mine.
	void fireMissile(Score::PLAYER player);
	void plantMine(Score::PLAYER player);
	void turnInvisible(Score::PLAYER player);
	// Restart battle, resets all values to initial conditions.
	void restartBattle();

	// Getters for display
	Tank * getTank1();
	Tank * getTank2();
	std::list<std::unique_ptr<Turret>> * getTurrets();
	std::list<std::unique_ptr<Missile>> * getMissiles();
	std::list<std::unique_ptr<Explosion>> * getExplosions();
	std::list<std::unique_ptr<Obstacle>> * getObstacles();
	std::list<std::unique_ptr<Mine>> * getMines();

	Score getScore();

private:
	// Private variables.
	Vector2D _screenDimensions;
	Tank _tank1;
	Tank _tank2;
	std::list<std::unique_ptr<Turret>> _turrets;
	std::list<std::unique_ptr<Missile>> _missiles;
	std::list<std::unique_ptr<Explosion>> _explosions;
	std::list<std::unique_ptr<Obstacle>> _obstacles;
	std::list<std::unique_ptr<Mine>> _mines;
	clock_t _missileTimer1;
	clock_t _missileTimer2;
	clock_t _mineTimer1;
	clock_t _mineTimer2;
	Score _score;

	// Private helper functions

	// Collision functions
	//___________________________________
	// Tests collision with another tank.
	bool isFrontTankCollision(Tank & aTank, Tank & bTank);
	bool isBackTankCollision(Tank & aTank, Tank & bTank);
	// Tests collision with a wall.
	bool isFrontWallCollision(Tank & tank, bool & isHorizontal);
	bool isBackWallCollision(Tank & tank, bool & isHorizontal);
	// Test missile collision with wall
	bool isMissileWallCollision(Vector2D & _missilePos, bool & isHorizontal);
	// Generic collision function, tests for collision between two polygons.
	bool isPolyCollision(std::vector<Vector2D> & aVertex, std::vector<Vector2D> & bVertex);
	// Test if missile has hit a tank.
	void missileHit(Tank & tank);
	// Test if a missile has hit a turret.
	void missileHitTurret();
	// Test if a tank has driven over a mine.
	void mineHit(Tank & tank);
	// Check missile obstacle collisions;
	void checkMissiles();
	// Make map
	void makeMap();
	// Place turrets on the map.
	void placeTurrets();
	// Move tank
	void moveTank(Tank::Movement movement, Tank & tankA, Tank & tankB);
	void moveTank(Tank::Direction direction, Tank & tankA, Tank & tankB);
	// Fill group
	void fillObstacle(Vector2D location, Vector2D size, Obstacle::TEXTURE texture);
	// Check which side a collision happened
	bool checkIsHorizontal(Vector2D & point, AxisAligned & obstacle);
	bool checkIsHorizontal(Vector2D & point);
};

#endif /* BATTLE_H_ */
