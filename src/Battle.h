#ifndef BATTLE_H_
#define BATTLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <ctime>
#include "Tank.h"
#include "Missile.h"
#include "Controller.h"
#include "HUD.h"

using namespace std;
using namespace sf;

typedef std::list<std::unique_ptr<Tank>>::iterator Tank_iter;

class Battle
{
public:
	// Constructor
	Battle(RenderWindow * window);
	// Allow the Tank class access to member variables.
	friend class Tank;
	// Add another tank to the battle.
	void addTank(Vector2f position, Controller::Players player, Color color = Color::Green);
	// Update the battle, testing collisions and missile hits.
	void update();
	// Overloaded Movement functions
	void tankMovement(Tank::Direction direction);
	void tankMovement(Tank::Movement movement);
private:
	// Private Member Functions

	// Collision functions
	// Tests collision with another tank.
	bool isFrontTankCollision(Tank_iter & aTank, Tank_iter & bTank);
	bool isBackTankCollision(Tank_iter & aTank, Tank_iter & bTank);
	// Tests collision with a wall.
	bool isFrontWallCollision(Tank_iter & tankIterator);
	bool isBackWallCollision(Tank_iter & tankIterator);
	// Generic collision function, tests for collision between two polygons.
	bool isPolyCollision(std::vector<Vector2f> & aVertex, std::vector<Vector2f> & bVertex);

	// Test if missile has hit a tank.
	void missileHit(Tank_iter & tankIterator);
	// Set the controls for a tank object.
	void setControls(Controller::Players & player);

	// Private Member Variables
	RenderWindow * _window;
	std::list<std::unique_ptr<Missile>> _missiles;
	std::list<std::unique_ptr<Tank>> _tanks;
	std::list<std::unique_ptr<HUD>> _HUDs;
	std::list<std::vector<Keyboard::Key>> _playerControls;
	// Missile class contains static pointers to these objects.
	Texture _missileTexture;
	Texture _explosionTexture;
};

#endif /* BATTLE_H_ */
