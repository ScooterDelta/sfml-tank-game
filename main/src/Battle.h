// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Battle.h

#ifndef BATTLE_H_
#define BATTLE_H_

#include <list>
#include <ctime>
#include <memory>
#include <vector>
#include "Tank.h"
#include "Missile.h"
#include "Obstacle.h"
#include "Explosion.h"
#include "Angle.h"
#include "Vector2D.h"
#include "Mine.h"
#include "Turret.h"
#include "Score.h"

using namespace sf;

//! Battle class that handles internal game conditions.
/*!
 * The battle class stores the objects within the game and handles their
 * collisions and destruction.
 */
class Battle {
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
    Tank *getTank1();
    //! Return a pointer to the player 2 tank object.
    /*!
     * Used for displaying the second tank object or performing external operations on it.
     */
    Tank *getTank2();
    //! Returns a pointer to the list of turrets.
    /*!
     * This function is used for displaying the turrets or performing external operations on them.
     */
    std::list<std::unique_ptr<Turret>> *getTurrets();
    //! Returns a pointer to the list of missiles.
    /*!
     * This function is used for displaying the missiles on the screen, or performing external
     * operations on them.
     */
    std::list<std::unique_ptr<Missile>> *getMissiles();
    //! Returns a pointer to the list of explosions.
    /*!
     * This can be used to display the explosions on the screen.
     */
    std::list<std::unique_ptr<Explosion>> *getExplosions();
    //! Returns a pointer to the list of obstacles.
    /*!
     * This can be used for displaying the obstacles on the screen.
     */
    std::list<std::unique_ptr<Obstacle>> *getObstacles();
    //! Returns a pointer to the list of mines.
    /*!
     * This can be used for displaying mines on the screen.
     */
    std::list<std::unique_ptr<Mine>> *getMines();

    //! Returns the current score of the game.
    Score getScore();

private:
    // Private variables.
    //! The dimensions of the sf::RenderWindow
    Vector2D _screenDimensions;
    //! Tank object for PLAYER1.
    Tank _tank1;
    //! Tank object for PLAYER2.
    Tank _tank2;
    //! List of Turret objects.
    std::list<std::unique_ptr<Turret>> _turrets;
    //! List of Missile Objects.
    std::list<std::unique_ptr<Missile>> _missiles;
    //! List of Explosion objects.
    std::list<std::unique_ptr<Explosion>> _explosions;
    //! List of Obstacle objects.
    std::list<std::unique_ptr<Obstacle>> _obstacles;
    //! List of Mine objects.
    std::list<std::unique_ptr<Mine>> _mines;
    //! Time between _tank1 Missiles.
    clock_t _missileTimer1;
    //! Time between _tank2 Missiles.
    clock_t _missileTimer2;
    //! Time between _tank1 Mines.
    clock_t _mineTimer1;
    //! Time between _tank2 Mines.
    clock_t _mineTimer2;
    //! The game score.
    /*!
     * The current score for each of the players in the game
     * is stored in the Score object.
     */
    Score _score;

    // Private helper functions

    // Collision functions
    //___________________________________
    // Tests collision with another tank.
    //! Check for a front collision with another tank.
    /*!
     * \param aTank The Tank being checked.
     * \param bTank The Tank that aTank could be colliding with.
     */
    bool isFrontTankCollision(Tank &aTank, Tank &bTank);
    //! Check for a rear collision with another tank.
    /*!
     * \param aTank The Tank being checked.
     * \param bTank The Tank that aTank could be colliding with.
     */
    bool isBackTankCollision(Tank &aTank, Tank &bTank);
    // Tests collision with a wall.
    //! Check for a front collision with a wall.
    /*!
     * \param tank The Tank being checked.
     * \param isHorizontal Whether the collision is with a horizontal surface.
     */
    bool isFrontWallCollision(Tank &tank, bool &isHorizontal);
    //! Check for a rear collision with a wall.
    /*!
     * \param tank The Tank being checked.
     * \param isHorizontal Whether the collision is with a horizontal surface.
     */
    bool isBackWallCollision(Tank &tank, bool &isHorizontal);
    // Test missile collision with wall
    //! Check if a missile has collided with a wall.
    /*!
     * If the missile collides with a wall then the isHorizontal variable
     * determines if the wall is horizontal or vertical.
     * \param _missilePos The center of the missile.
     * \param isHorizontal Whether the collision is with a horizontal surface.
     */
    bool isMissileWallCollision(Vector2D &_missilePos, bool &isHorizontal);
    // Test a generic point for collisions with the obstacles.
    //! Generic function checking if a point is colliding with any walls.
    /*!
     * \param position The point being checked.
     * \param isHorizontal Whether the collision is with a horizontal surface.
     */
    bool isWallCollision(Vector2D position, bool &isHorizontal);
    // Test a generic point for collisions with the turrets.
    //! Check if a point is colliding with any turrets.
    /*!
     * \param position The point being checked.
     * \param isHorizontal Whether the collision is with a horizontal surface.
     */
    bool isTurretCollision(Vector2D position, bool &isHorizontal);
    // Generic collision function, tests for collision between two polygons.
    //! Polygon collision check for any size polygon.
    /*!
     * Checks for a collision between any two objects with any number of vertices.
     * \param aVertex List of vertices of the first object.
     * \param bVertex List of vertices of the object being checked against.
     */
    bool isPolyCollision(std::vector<Vector2D> &aVertex, std::vector<Vector2D> &bVertex);

    // Test if missile has hit a tank.
    //! Check if any missiles have hit the tank object.
    //! \param tank The Tank object being checked.
    void missileHit(Tank &tank);

    // Test if a missile has hit a turret.
    //! Check if any missiles have hit any of the turrets.
    void missileHitTurret();

    // Test if a tank has driven over a mine.
    //! Check if any mines are colliding with a particular Tank.
    //! \param tank The Tank object that is being checked.
    void mineHit(Tank &tank);

    // Check missile obstacle collisions;
    //! Check all missiles locations and update.
    void checkMissiles();

    // Make map
    //! Make the map of obstacles for the game.
    void makeMap();

    // Place turrets on the map.
    //! Place the games turrets on the map.
    void placeTurrets();
    // Move tank
    //! Move the tank with a particular movement.
    /*!
     * Holds all the movement checks for the tank, tankA is the tank being moved
     * and tankB is checked for collisions.
     * \param movement The Movement the tank should take
     * \param tankA The Tank being moved.
     * \param tankB The Tank being checked for collisions
     */
    void moveTank(Tank::Movement movement, Tank &tankA, Tank &tankB);
    //! Move the tank with a particular direction.
    /*!
     * Holds all the movement checks for the tank, tankA is the tank being moved
     * and tankB is checked for collisions.
     * \param direction The direction the tank should rotate.
     * \param tankA The Tank being moved.
     * \param tankB The Tank being checked for collisions.
     */
    void moveTank(Tank::Direction direction, Tank &tankA, Tank &tankB);
    // Fill group
    //! Fill a rectangle grid of obstacles.
    /*!
     * The obstacles are filled from squares, this function starts filling
     * from the top left corner for a certain sized rectangle.
     * \param location The top left corner of the rectangle being filled.
     * \param size The size of the rectangle being filled.
     * \param texture The type of obstacle (Brick or Box).
     */
    void fillObstacle(Vector2D location, Vector2D size, Obstacle::TEXTURE texture);
    // Check which side a collision happened
    //! Check if a collision with an obstacle is horizontal.
    /*!
     * If the point collision with the obstacle is horizontal then the
     * function returns true.
     * \param point The point being checked.
     * \param obstacle The obstacle that is being checked.
     */
    bool checkIsHorizontal(Vector2D &point, AxisAligned &obstacle);
    //! Check if a collision with the edges of the screen is horizontal.
    /*!
     * If the collision is horizontal then the function returns true.
     * \param point The point being checked with the edges of the screen.
     */
    bool checkIsHorizontal(Vector2D &point);
    // Edit the score for a player hit by an obstacle
    //! Change the score when a player is hit by a projectile.
    /*!
     * When a players tank (player) is hit by projectile (projectileOwner),
     * then change the score accodingly.
     * \param player The player that the tank being hit belongs to.
     * \param projectileOwner The player that the projectile belongs to.
     */
    void playerHit(Score::PLAYER player, Score::PLAYER projectileOwner);
};

#endif /* BATTLE_H_ */
