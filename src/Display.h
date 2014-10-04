// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Display.h

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

//! Class to display objects on the screen.
/*!
 * This class has overloaded functions for each of the objects it needs to display,
 * it loads a texture onto a sprite for displaying the objects.
 */
class Display
{
public:
	//! Display constructor.
	/*!
	 * The display function needs to take in a pointer to the window so that it
	 * can draw all objects onto the window itself.
	 * \param window A pointer to the RenderWindow used for the game.
	 */
	Display(RenderWindow * window);
	// Draw functions for various objects in the game.
	//! Draw the background for the battle.
	/*!
	 * Draws the background image with a certain contrast.
	 * \param contrast Sets the contrast of the texture loaded.
	 */
	void drawBackGround(sf::Uint8 contrast = 255);
	//! Draw the initial splash screen.
	/*!
	 * Used before the game has started in order to display information
	 * about the game (controls, etc).
	 */
	void DrawSplash();
	//! Draw a tank on the screen.
	/*!
	 * The tank will be drawn with the texture relating to the player.
	 * \param player The player that the tank belongs to.
	 */
	void draw(Tank & tank, Score::PLAYER player, sf::Uint8  contrast = 255);
	//! Draw all the turrets in the list on the screen.
	//! \param turret Pointer to the list of turrets in the game.
	//! \param contrast Sets the contrast of the texture loaded.
	void draw(std::list<std::unique_ptr<Turret>> * turret, sf::Uint8  contrast = 255);
	//! Draw all the missiles in the list on the screen.
	//! \param missile Pointer to the list of missiles in the game.
	//! \param contrast Sets the contrast of the texture loaded.
	void draw(std::list<std::unique_ptr<Missile>> * missile, sf::Uint8  contrast = 255);
	//! Draw all the explosions in the list on the screen.
	//! \param explosion Pointer to the list of explosions in the game.
	//! \param contrast Sets the contrast of the texture loaded.
	void draw(std::list<std::unique_ptr<Explosion>> * explosion, sf::Uint8  contrast = 255);
	//! Draw all the obstacles in the list on the screen.
	//! \param obstacle Pointer to the list of obstacles in the game.
	//! \param contrast Sets the contrast of the texture loaded.
	void draw(std::list<std::unique_ptr<Obstacle>> * obstacle, sf::Uint8  contrast = 255);
	//! Draw all the mines in the list on the screen.
	//! \param obstacle Pointer to the list of mines in the game.
	//! \param contrast Sets the contrast of the texture loaded.
	void draw(std::list<std::unique_ptr<Mine>> * mine, sf::Uint8 contrast = 255);
	//! Draw the remaining time on the screen.
	/*!
	 * This is on the screen while the game is running in order to
	 * show the players how much time is left in the round.
	 * \param float remainingTime The amount of time remaining in a round.
	 */
	void draw(float remainingTime);
	//! Draw the score screen.
	/*!
	 * The score screen is drawn when the game is paused or over, if the game is paused
	 * then isPaused is true, else the game is over.
	 * \param _score The score from the game to be displayed.
	 * \param isPaused Whether the score screen is for paused game or not.
	 */
	void draw(Score & _score, bool isPaused = false);

private:
	RenderWindow * _window;

	// Textures for objects
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
	Texture _turretTexture;

	// Sprites for objects on screen.
	Sprite _drawPlayer1Tank;
	Sprite _drawPlayer2Tank;
	Sprite _drawMissile;
	RectangleShape _drawObstacle;
	Sprite _drawExplosion;
	Sprite _drawMine1;
	Sprite _drawMine2;
	Sprite _drawBackGround;
	Sprite _drawTurret;

	// Private member variables.
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
	void initializeTurret();
};

#endif /* DISPLAY_H_ */
