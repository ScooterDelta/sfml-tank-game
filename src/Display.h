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
#include "Score.h"

using namespace sf;

class Display
{
public:
	Display(RenderWindow * window);
	void drawBackGround();
	void draw(Tank & tank, Score::PLAYER player);
	void draw(std::list<std::unique_ptr<Missile>> * missile);
	void draw(std::list<std::unique_ptr<Explosion>> * explosion);
	void draw(std::list<std::unique_ptr<Obstacle>> * obstacle);
	void draw(std::list<std::unique_ptr<Mine>> * mine);
	void draw(float remainingTime);
	void draw(Score & _score, bool isPaused = false);

private:
	RenderWindow * _window;

	Texture _player1TankTexture;
	Texture _player2TankTexture;
	Texture _missileTexture;
	Texture _obstacleTextureBox1;
	Texture _obstacleTextureBox2;
	Texture _obstacleTextureBox3;
	Texture _obstacleTextureBox4;
	Texture _obstacleTextureBrick1;
	Texture _obstacleTextureBrick2;
	Texture _obstacleTextureBrick3;
	Texture _obstacleTextureBrick4;
	Texture _explosionTexture;
	Texture _mineTexture1;
	Texture _mineTexture2;
	Texture _backGroundTexture;

	Sprite _drawPlayer1Tank;
	Sprite _drawPlayer2Tank;
	Sprite _drawMissile;
	RectangleShape _drawObstacle;
	Sprite _drawExplosion;
	Sprite _drawMine1;
	Sprite _drawMine2;
	Sprite _drawBackGround;

	HUD _hud;
	unsigned int _mineTime;
	bool _mineLight;

	// Private helper functions
	void initializeTank();
	void initializeMissile();
	void initializeExplosion();
	void initializeObstacle();
	void initializeMine();
	void initializeBackGround();
};

#endif /* DISPLAY_H_ */
