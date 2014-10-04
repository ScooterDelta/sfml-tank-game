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

//! Battle class that handles internal game conditions.
/*!
 * The battle class stores the objects within the game and handles their
 * collisions and destruction.
 */
class Battle
{
public:
	// Constructor.
	//! Battle constructor.
	/*!
	 * The constructor requires the screenDimensions, since all objects must be scaled
	 * with the size of the screen.
	 * \param screenDimensions The size of the screen in pixels.
	 */
	Battle(Vector2D screenDimensions);
	//! The Display class needs to display members of Battle.
	friend class Display;
	// Update the battle, updating all locations and collisions of objects
	//! Updates the members of Battle.
	/*!
	 * All of the objects of the Battle need to have the locations updated
	 * in every loop of the game. This function controls the turrets and
	 * the missiles.
	 */
	void update();
	// Overloaded move functions, for changing direction and movement of tanks.
	//! Rotates the tank belonging to player.
	/*!
	 * The Direction enum defines rotation as Clockwise or Anticlockwise (or straight).
	 * The function then checks if the rotation is possible with objects around the tank.
	 * \param player The player that the tank belongs to.
	 * \param direction The direction that the tank should rotate, Clockwise or Anticlockwise.
	 */
	void moveTank(Score::PLAYER player, Tank::Direction direction);
	//! Moves the tank belonging to player.
	/*!
	 * The Movement enum defines movement as Forwards or Backwards (or none).
	 * The function then checks if the movement is possible with objects around the tank.
	 * \param player The player that the tank belongs to.
	 * \param movement The movement that the tank should make, Forwards or Backwards.
	 */
	void moveTank(Score::PLAYER player, Tank::Movement movement);
	// Function for a particular tank (player) to fire a missile or plant a mine.
	//! Fire a missile for a particular player.
	/*!
	 * This will fire a missile from a tank belonging to player.
	 * \param player The player that the tank belongs to.
	 */
	void fireMissile(Score::PLAYER player);
	//! Fire a missile for a particular player.
	/*!
	 * This will plant a mine from a tank belonging to player.
	 * \param player The player that the tank belongs to.
	 */
	void plantMine(Score::PLAYER player);
	//! Turn a tank invisible.
	/*!
	 * This will turn a tank belonging to a particular player invisible.
	 * \param player The player that the tank belongs to.
	 */
	void turnInvisible(Score::PLAYER player);
	// Restart battle, resets all values to initial conditions.
	//! Return all aspects of the battle to their starting conditions.
	/*!
	 * All members of the battle are reset, including map and all objects.
	 */
	void restartBattle();

	// Getters for display
	//! Return a pointer to the player 1 tank object.
	/*!
	 * Used for displaying the first tank object or performing external operations on it.
	 */
	Tank * getTank1();
	//! Return a pointer to the player 2 tank object.
	/*!
	 * Used for displaying the second tank object or performing external operations on it.
	 */
	Tank * getTank2();
	//! Returns a pointer to the list of turrets.
	/*!
	 * This function is used for displaying the turrets or performing external operations on them.
	 */
	std::list<std::unique_ptr<Turret>> * getTurrets();
	//! Returns a pointer to the list of missiles.
	/*!
	 * This function is used for displaying the missiles on the screen, or performing external
	 * operations on them.
	 */
	std::list<std::unique_ptr<Missile>> * getMissiles();
	//! Returns a pointer to the list of explosions.
	/*!
	 * This can be used to display the explosions on the screen.
	 */
	std::list<std::unique_ptr<Explosion>> * getExplosions();
	//! Returns a pointer to the list of obstacles.
	/*!
	 * This can be used for displaying the obstacles on the screen.
	 */
	std::list<std::unique_ptr<Obstacle>> * getObstacles();
	//! Returns a pointer to the list of mines.
	/*!
	 * This can be used for displaying mines on the screen.
	 */
	std::list<std::unique_ptr<Mine>> * getMines();

	//! Returns the current score of the game.
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
	// Test a generic point for collisions with the obstacles.
	bool isWallCollision(Vector2D position, bool & isHorizontal);
	// Test a generic point for collisions with the turrets.
	bool isTurretCollision(Vector2D position, bool & isHorizontal);
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
	// Edit the score for a player hit by an obstacle
	void playerHit(Score::PLAYER player, Score::PLAYER projectileOwner);
};

#endif /* BATTLE_H_ */
