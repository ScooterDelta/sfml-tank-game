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
	Battle(RenderWindow * window);
	friend class Tank;
	void addTank(Vector2f position, Controller::Players player, Color color = Color::Green);
	void update();
	// Overloaded Movement functions
	void tankMovement(Tank::Direction direction);
	void tankMovement(Tank::Movement movement);
private:
	// Private Member Functions
	bool isFrontTankCollision(Tank_iter & aTank, Tank_iter & bTank);
	bool isBackTankCollision(Tank_iter & aTank, Tank_iter & bTank);
	bool isFrontWallCollision(Tank_iter & tankIterator);
	bool isBackWallCollision(Tank_iter & tankIterator);
	void missileHit(Tank_iter & tankIterator);
	void setControls(Controller::Players & player);
	bool isPolyCollision(std::vector<Vector2f> & aVertex, std::vector<Vector2f> & bVertex);
	// Private Member Variables
	RenderWindow * _window;
	std::list<std::unique_ptr<Missile>> _missiles;
	std::list<std::unique_ptr<Tank>> _tanks;
	std::list<std::unique_ptr<HUD>> _HUDs;
	std::list<std::vector<Keyboard::Key>> _playerControls;
};

#endif /* BATTLE_H_ */
