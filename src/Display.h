#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <memory>
#include <iostream>
#include "DrawableObject.h"
#include "Battle.h"
#include "Tank.h"
#include "Missile.h"
#include "Explosion.h"
#include "Mine.h"
#include "Obstacle.h"
#include "HUD.h"

using namespace sf;

class Display
{
public:
	Display(RenderWindow * window);
	void draw(Tank & tank, Battle::Player player);
	void draw(std::list<std::unique_ptr<Missile>> * missile);
	void draw(std::list<std::unique_ptr<Explosion>> * explosion);
	void draw(std::list<std::unique_ptr<Obstacle>> * obstacle);
	void draw(std::list<std::unique_ptr<Mine>> * mine);

private:
	RenderWindow * _window;

	Texture _player1TankTexture;
	Texture _player2TankTexture;
	Texture _missileTexture;
	Texture _obstacleTexture;
	Texture _explosionTexture;
	Texture _mineTexture;

	Sprite _drawPlayer1Tank;
	Sprite _drawPlayer2Tank;
	Sprite _drawMissile;
	RectangleShape _drawObstacle;
	Sprite _drawExplosion;
	Sprite _drawMine;

	HUD _hud;

	// Private helper functions
	void initializeTank();
	void initializeMissile();
	void initializeExplosion();
	void initializeObstacle();
	void initializeMine();
};

#endif /* DISPLAY_H_ */
