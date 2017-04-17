// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Display.h

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <memory>
#include "../gameplay/Battle.h"
#include "HUD.h"

namespace game {
namespace display {

using namespace sf;

//! Class to display objects on the screen.
/*!
 * This class has overloaded functions for each of the objects it needs to display,
 * it loads a texture onto a sprite for displaying the objects.
 */
class Display {
public:
    //! Display constructor.
    /*!
     * The display function needs to take in a pointer to the window so that it
     * can draw all objects onto the window itself.
     * \param window A pointer to the RenderWindow used for the game.
     */
    Display(std::shared_ptr<RenderWindow> window);
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
     * \param tank The tank object to be displayed on the screen.
     * \param player The player that the tank belongs to.
     * \param contrast Sets the contrast of the texture loaded.
     */
    void draw(Tank &tank, Score::PLAYER player, sf::Uint8 contrast = 255);

    //! Draw all the turrets in the list on the screen.
    //! \param turret Pointer to the list of turrets in the game.
    //! \param contrast Sets the contrast of the texture loaded.
    void draw(std::list<std::unique_ptr<Turret>> *turret, sf::Uint8 contrast = 255);

    //! Draw all the missiles in the list on the screen.
    //! \param missile Pointer to the list of missiles in the game.
    //! \param contrast Sets the contrast of the texture loaded.
    void draw(std::list<std::unique_ptr<Missile>> *missile, sf::Uint8 contrast = 255);

    //! Draw all the explosions in the list on the screen.
    //! \param explosion Pointer to the list of explosions in the game.
    //! \param contrast Sets the contrast of the texture loaded.
    void draw(std::list<std::unique_ptr<Explosion>> *explosion, sf::Uint8 contrast = 255);

    //! Draw all the obstacles in the list on the screen.
    //! \param obstacle Pointer to the list of obstacles in the game.
    //! \param contrast Sets the contrast of the texture loaded.
    void draw(std::list<std::unique_ptr<Obstacle>> *obstacle, sf::Uint8 contrast = 255);

    //! Draw all the mines in the list on the screen.
    //! \param mine Pointer to the list of mines in the game.
    //! \param contrast Sets the contrast of the texture loaded.
    void draw(std::list<std::unique_ptr<Mine>> *mine, sf::Uint8 contrast = 255);
    //! Draw the remaining time on the screen.
    /*!
     * This is on the screen while the game is running in order to
     * show the players how much time is left in the round.
     * \param remainingTime The amount of time remaining in a round.
     */
    void draw(float remainingTime);
    //! Draw the score screen.
    /*!
     * The score screen is drawn when the game is paused or over, if the game is paused
     * then isPaused is true, else the game is over.
     * \param _score The score from the game to be displayed.
     * \param isPaused Whether the score screen is for paused game or not.
     */
    void draw(Score &_score, bool isPaused = false);

private:
    //! Shared pointer to the RenderWindow.
    std::shared_ptr<RenderWindow> _window;

    // Textures for objects
    //! Texture for Tank belonging to PLAYER1
    Texture _player1TankTexture;
    //! Texture for Tank belonging to PLAYER2
    Texture _player2TankTexture;
    //! Texture for the missile object.
    Texture _missileTexture;
    //! First texture for box obstacle.
    Texture _obstacleTextureBox1;
    //! Second texture for box obstacle.
    Texture _obstacleTextureBox2;
    //! Third texture for box obstacle.
    Texture _obstacleTextureBox3;
    //! Fourth texture for box obstacle.
    Texture _obstacleTextureBox4;
    //! First texture for brick obstacle.
    Texture _obstacleTextureBrick1;
    //! Second texture for brick obstacle.
    Texture _obstacleTextureBrick2;
    //! Third texture for brick obstacle.
    Texture _obstacleTextureBrick3;
    //! Fourth texture for brick obstacle.
    Texture _obstacleTextureBrick4;
    //! Texture for explosion object.
    Texture _explosionTexture;
    //! First texture for mine object.
    Texture _mineTexture1;
    //! Second texture for mine object.
    Texture _mineTexture2;
    //! Texture for game back ground
    Texture _backGroundTexture;
    //! Texture for the turret object.
    Texture _turretTexture;
    //! Texture for the splash screen.
    Texture _splashTexture;

    // Sprites for objects on screen.
    //! Sprite for drawing Tank for PLAYER1
    Sprite _drawPlayer1Tank;
    //! Sprite for drawing Tank for PLAYER2
    Sprite _drawPlayer2Tank;
    //! Sprite for drawing a Missile.
    Sprite _drawMissile;
    //! RectangleShape object for drawing an Obstacle.
    RectangleShape _drawObstacle;
    //! Sprite for drawing an Explosion.
    Sprite _drawExplosion;
    //! Sprite for drawing the Mine animation
    Sprite _drawMine1;
    //! Sprite for drawing the Mine animation
    Sprite _drawMine2;
    //! Sprite for drawing the game background
    Sprite _drawBackGround;
    //! Sprite for drawing the Turret.
    Sprite _drawTurret;
    //! Sprite for drawing the splash screen.
    Sprite _drawSplash;

    // Private member variables.
    //! HUD object for drawing text on the screen.
    /*!
     * All text in the game is drawn using the HUD object.
     */
    HUD _hud;
    //! Timer for the Mine display animation.
    unsigned int _mineTime;
    //! Check which state the mine animation is in.
    bool _mineLight;

    // Private helper functions
    //! Initialize the Tank objects (Texture and Sprite).
    void initializeTank();

    //! Initialize the Missile objects (Texture and Sprite).
    void initializeMissile();

    //! Initialize the Explosion objects (Texture and Sprite).
    void initializeExplosion();

    //! Initialize the Obstacle objects (Texture and Sprite).
    void initializeObstacle();

    //! Initialize the Mine objects (Texture and Sprite).
    void initializeMine();

    //! Initialize the Back Ground objects (Texture and Sprite).
    void initializeBackGround();

    //! Initialize the Turret objects (Texture and Sprite).
    void initializeTurret();

    //! Initialize the Splash screen objects (Texture and Sprite).
    void initializeSplash();
};

}
}

#endif /* DISPLAY_H_ */
