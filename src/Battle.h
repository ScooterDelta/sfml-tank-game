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

using namespace sf;

class Battle
{
public:
	enum Player {Player1 = 1, Player2};
	Battle(Vector2f screenDimensions);
	friend class Display;
	void update();
	void moveTank(Player player, Tank::Direction direction);
	void moveTank(Player player, Tank::Movement movement);
	void fireMissile(Player player);
	void plantMine(Player player);

	// Getters for display
	Tank * getTank1();
	Tank * getTank2();
	std::list<std::unique_ptr<Missile>> * getMissiles();
	std::list<std::unique_ptr<Explosion>> * getExplosions();
	std::list<std::unique_ptr<Obstacle>> * getObstacles();
	std::list<std::unique_ptr<Mine>> * getMines();

private:
	Vector2f _screenDimensions;
	Tank _tank1;
	Tank _tank2;
	std::list<std::unique_ptr<Missile>> _missiles;
	std::list<std::unique_ptr<Explosion>> _explosions;
	std::list<std::unique_ptr<Obstacle>> _obstacles;
	std::list<std::unique_ptr<Mine>> _mines;
	clock_t _missileTimer1;
	clock_t _missileTimer2;
	clock_t _mineTimer1;
	clock_t _mineTimer2;

	// Private helper functions

	// Collision functions
	//___________________________________
	// Tests collision with another tank.
	bool isFrontTankCollision(Tank & aTank, Tank & bTank);
	bool isBackTankCollision(Tank & aTank, Tank & bTank);
	// Tests collision with a wall.
	bool isFrontWallCollision(Tank & tank);
	bool isBackWallCollision(Tank & tank);
	// Test missile collision with wall
	bool isMissileWallCollision(Vector2f & _missilePos, bool & isHorizontal);
	// Generic collision function, tests for collision between two polygons.
	bool isPolyCollision(std::vector<Vector2f> & aVertex, std::vector<Vector2f> & bVertex);
	// Test if missile has hit a tank.
	void missileHit(Tank & tank);
	// Test if a tank has driven over a mine.
	void mineHit(Tank & tank);
	// Check missile obstacle collisions;
	void checkMissiles();
	// Make map
	void makeMap();
};



#endif /* BATTLE_H_ */
