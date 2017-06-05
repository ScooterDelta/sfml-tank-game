// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Display.cpp

#include "Display.h"

namespace game::display {

    // Constructor:
    Display::Display(std::shared_ptr<RenderWindow> window) :
            _window{window},
            _hud{window},
            _mineLight{false} {
        initializeTank();
        initializeMissile();
        initializeExplosion();
        initializeObstacle();
        initializeMine();
        initializeBackGround();
        initializeTurret();
        initializeSplash();
    }

    // Draw functions for various objects.
    // Draw the back drop on the game.
    void Display::drawBackGround(sf::Uint8 contrast) {
        _drawBackGround.setColor(Color{contrast, contrast, contrast});
        _window->draw(_drawBackGround);
    }

    // Draw the tank on the screen in a particular position.
    void Display::draw(Tank &tank, Score::PLAYER player, sf::Uint8 contrast) {
        if (player == Score::PLAYER1) {
            _drawPlayer1Tank.setPosition({tank.getPosition().x, tank.getPosition().y});
            _drawPlayer1Tank.setRotation(tank.getDirection());

            if (tank.isInvisible())
                _drawPlayer1Tank.setColor(Color{contrast, contrast, contrast, 60});
            else
                _drawPlayer1Tank.setColor(Color{contrast, contrast, contrast, 255});

            _window->draw(_drawPlayer1Tank);
        } else {
            _drawPlayer2Tank.setPosition({tank.getPosition().x, tank.getPosition().y});
            _drawPlayer2Tank.setRotation(tank.getDirection());

            if (tank.isInvisible())
                _drawPlayer2Tank.setColor(Color{contrast, contrast, contrast, 60});
            else
                _drawPlayer2Tank.setColor(Color{contrast, contrast, contrast, 255});

            _window->draw(_drawPlayer2Tank);
        }
        // Draw the UI for the particular tank.
        _hud.DrawUI(tank, player);
    }

    void Display::DrawSplash() {
        _window->draw(_drawSplash);
        _hud.DrawSplash();
    }

    // Draw the turrets on the screen.
    void Display::draw(std::list<std::unique_ptr<Turret>> *turret, sf::Uint8 contrast) {
        Vector2f tempVect;
        auto _turretIterator = turret->begin();
        // Iterate the list of turrets displaying them.
        while (_turretIterator != turret->end()) {
            tempVect = {(*_turretIterator)->getPosition().x, (*_turretIterator)->getPosition().y};
            _drawTurret.setPosition(tempVect);
            _drawTurret.setRotation((*_turretIterator)->getDirection());
            _drawTurret.setColor(Color{contrast, contrast, contrast});

            _window->draw(_drawTurret);

            ++_turretIterator;
        }

    }

    // Draw the missiles on the screen in their positions
    void Display::draw(std::list<std::unique_ptr<Missile>> *missile, sf::Uint8 contrast) {
        Vector2f tempVect;
        auto _missileIterator = missile->begin();
        // Iterate the list of missiles displaying them all.
        while (_missileIterator != missile->end()) {
            tempVect = {(*_missileIterator)->getPosition().x, (*_missileIterator)->getPosition().y};
            _drawMissile.setPosition(tempVect);
            _drawMissile.setRotation((*_missileIterator)->getDirection());
            _drawMissile.setColor(Color{contrast, contrast, contrast});

            _window->draw(_drawMissile);
            ++_missileIterator;
        }

    }

    // Draw the explosions on the screen in their positions.
    void Display::draw(std::list<std::unique_ptr<Explosion>> *explosion, sf::Uint8 contrast) {
        Vector2f tempVect;
        auto _explosionIterator = explosion->begin();
        // Iterate through the list of explosions displaying them all.
        while (_explosionIterator != explosion->end()) {
            tempVect = {(*_explosionIterator)->getPosition().x, (*_explosionIterator)->getPosition().y};
            _drawExplosion.setPosition(tempVect);
            _drawExplosion.setColor(Color{contrast, contrast, contrast});

            _window->draw(_drawExplosion);
            ++_explosionIterator;
        }
    }

    // Draw the obstacles on the screen.
    void Display::draw(std::list<std::unique_ptr<Obstacle>> *obstacle, sf::Uint8 contrast) {
        Vector2f tempVect;
        auto _obstacleIterator = obstacle->begin();
        // Iterate through the list of obstacles, displaying a different one
        // depending on the damage to the obstacle and the type of obstacle.
        while (_obstacleIterator != obstacle->end()) {
            tempVect = {(*_obstacleIterator)->getPosition().x, (*_obstacleIterator)->getPosition().y};
            _drawObstacle.setPosition(tempVect);

            if ((*_obstacleIterator)->getTexture() == Obstacle::BOX) {
                if ((*_obstacleIterator)->remainingHits() == 0)
                    _drawObstacle.setTexture(&_obstacleTextureBox4, true);
                else if ((*_obstacleIterator)->remainingHits() == 1)
                    _drawObstacle.setTexture(&_obstacleTextureBox3, true);
                else if ((*_obstacleIterator)->remainingHits() == 2)
                    _drawObstacle.setTexture(&_obstacleTextureBox2, true);
                else
                    _drawObstacle.setTexture(&_obstacleTextureBox1, true);
            } else if ((*_obstacleIterator)->getTexture() == Obstacle::BRICK) {
                if ((*_obstacleIterator)->remainingHits() == 0)
                    _drawObstacle.setTexture(&_obstacleTextureBrick4, true);
                else if ((*_obstacleIterator)->remainingHits() == 1)
                    _drawObstacle.setTexture(&_obstacleTextureBrick3, true);
                else if ((*_obstacleIterator)->remainingHits() == 2)
                    _drawObstacle.setTexture(&_obstacleTextureBrick2, true);
                else
                    _drawObstacle.setTexture(&_obstacleTextureBrick1, true);
            }
            _drawObstacle.setFillColor(Color{contrast, contrast, contrast});
            // Draw on the screen.
            _window->draw(_drawObstacle);
            ++_obstacleIterator;
        }
    }

    // Draw the mines on the screen.
    void Display::draw(std::list<std::unique_ptr<Mine>> *mine, sf::Uint8 contrast) {
        Vector2f tempVect;
        _mineTime++;
        // Every 30 calls change the texture of the mine.
        // This gives a "Blinking" animation.
        if (_mineTime % 30 == 0)
            _mineLight = !_mineLight;
        auto _mineIterator = mine->begin();
        while (_mineIterator != mine->end()) {
            if (_mineLight) {
                tempVect = {(*_mineIterator)->getPosition().x, (*_mineIterator)->getPosition().y};
                _drawMine1.setPosition(tempVect);
                _drawMine1.setColor(Color{contrast, contrast, contrast});

                _window->draw(_drawMine1);
            } else {
                tempVect = {(*_mineIterator)->getPosition().x, (*_mineIterator)->getPosition().y};
                _drawMine2.setPosition(tempVect);
                _drawMine2.setColor(Color{contrast, contrast, contrast});

                _window->draw(_drawMine2);
            }

            ++_mineIterator;
        }
    }

    // Draw the score screen.
    void Display::draw(Score &_score, bool isPaused) {
        _hud.DrawScore(_score, isPaused);
    }

    // Draw the remaining time on the game screen.
    void Display::draw(float remainingTime) {
        _hud.DrawTimer(remainingTime);
    }

    // Initialize the tank sprite and texture.
    void Display::initializeTank() {
        _player1TankTexture.loadFromFile("assets/tank1.png");
        _drawPlayer1Tank.setTexture(_player1TankTexture, true);
        _player2TankTexture.loadFromFile("assets/tank2.png");
        _drawPlayer2Tank.setTexture(_player2TankTexture, true);

        _drawPlayer1Tank.setOrigin(760.f, _drawPlayer1Tank.getGlobalBounds().height / 2);
        _drawPlayer2Tank.setOrigin(760.f, _drawPlayer2Tank.getGlobalBounds().height / 2);

        //_drawPlayer1Tank.setOrigin(_drawPlayer1Tank.getGlobalBounds().width/2, _drawPlayer1Tank.getGlobalBounds().height/2);
        _drawPlayer1Tank.setScale((float) (0.04 * (_window)->getSize().x / 1600),
                                  (float) (0.04 * (_window)->getSize().y / 900));
        //_drawPlayer2Tank.setOrigin(_drawPlayer2Tank.getGlobalBounds().width/2, _drawPlayer2Tank.getGlobalBounds().height/2);
        _drawPlayer2Tank.setScale((float) (0.04 * (_window)->getSize().x / 1600),
                                  (float) (0.04 * (_window)->getSize().y / 900));
    }

    // Initializes the missile sprite and texture.
    void Display::initializeMissile() {
        _missileTexture.loadFromFile("assets/projectile1.png");
        _drawMissile.setTexture(_missileTexture, true);
        _drawMissile.setOrigin(_drawMissile.getGlobalBounds().width / 2, _drawMissile.getGlobalBounds().height / 2);
        _drawMissile.setScale((float) (0.025 * (_window)->getSize().x / 1600),
                              (float) (0.025 * (_window)->getSize().y / 900));
    }

    // Initialize the explosion sprite and texture.
    void Display::initializeExplosion() {
        // Initialize mine texture.
        Vector2f windowSize{_window->getSize()};

        _explosionTexture.loadFromFile("assets/explosion.png");
        _drawExplosion.setTexture(_explosionTexture, true);
        _drawExplosion.setOrigin(_drawExplosion.getGlobalBounds().width / 2,
                                 _drawExplosion.getGlobalBounds().height / 2);
        _drawExplosion.setScale((float) (0.06 * windowSize.x / 1600), (float) (0.06 * windowSize.y / 900));
    }

    // Initialize the obstacle sprite and textures.
    void Display::initializeObstacle() {
        // Need to initialize texture here.
        _drawObstacle.setRotation(0);
        Vector2f windowSize{_window->getSize()};
        _drawObstacle.setSize({windowSize.x / 32, windowSize.y / 18});
        _drawObstacle.setOrigin({0.f, 0.f});

        _obstacleTextureBox1.loadFromFile("assets/box1.png");
        _obstacleTextureBox2.loadFromFile("assets/box2.png");
        _obstacleTextureBox3.loadFromFile("assets/box3.png");
        _obstacleTextureBox4.loadFromFile("assets/box4.png");
        _obstacleTextureBrick1.loadFromFile("assets/brick1.png");
        _obstacleTextureBrick2.loadFromFile("assets/brick2.png");
        _obstacleTextureBrick3.loadFromFile("assets/brick3.png");
        _obstacleTextureBrick4.loadFromFile("assets/brick4.png");
    }

    // Initialize the mine sprite and texture.
    void Display::initializeMine() {
        // Initialize mine texture.
        Vector2f windowSize{_window->getSize()};

        _mineTexture1.loadFromFile("assets/mine1.png");
        _mineTexture2.loadFromFile("assets/mine2.png");
        _drawMine1.setTexture(_mineTexture1, true);
        _drawMine1.setOrigin(_drawMine1.getGlobalBounds().width / 2, _drawMine1.getGlobalBounds().height / 2);
        _drawMine1.setScale((float) (0.05 * windowSize.x / 1600), (float) (0.05 * windowSize.y / 900));
        _drawMine2.setTexture(_mineTexture2, true);
        _drawMine2.setOrigin(_drawMine2.getGlobalBounds().width / 2, _drawMine2.getGlobalBounds().height / 2);
        _drawMine2.setScale((float) (0.05 * windowSize.x / 1600), (float) (0.05 * windowSize.y / 900));
    }

    // Initialize the background sprite and texture.
    void Display::initializeBackGround() {
        Vector2f windowSize{_window->getSize()};
        // Initialize the background testure.
        _backGroundTexture.loadFromFile("assets/backdrop.png");
        _drawBackGround.setTexture(_backGroundTexture, true);
        _drawBackGround.setOrigin(0, 0);
        _drawBackGround.setScale(windowSize.x / 3200, windowSize.y / 1800);
        _drawBackGround.setPosition(0, 0);
    }

    // Initialize the splash screen sprite and texture.
    void Display::initializeSplash() {
        Vector2f windowSize{_window->getSize()};
        // Initialize the splash screen texture.
        _splashTexture.loadFromFile("assets/splash.png");
        _drawSplash.setTexture(_splashTexture, true);
        _drawSplash.setOrigin(0, 0);
        _drawSplash.setScale(windowSize.x / 3200, windowSize.y / 1800);
        _drawSplash.setPosition(0, 0);
    }

    // Initialize the explosion sprite and texture.
    void Display::initializeTurret() {
        // Initialize mine texture.
        Vector2f windowSize{_window->getSize()};

        _turretTexture.loadFromFile("assets/turret.png");
        _drawTurret.setTexture(_turretTexture, true);
        _drawTurret.setOrigin(_drawTurret.getGlobalBounds().width - 168, _drawTurret.getGlobalBounds().height / 2);
        _drawTurret.setScale((float) (0.12 * windowSize.x / 1600), (float) (0.12 * windowSize.y / 900));
    }

}
