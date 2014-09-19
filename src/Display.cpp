#include "Display.h"

Display::Display(RenderWindow * window) :
	_window{window},
	_hud{window}
{
	initializeTank();
	initializeMissile();
	initializeExplosion();
	initializeObstacle();
	initializeMine();

	std::cout << "Tank Size: " << _drawPlayer1Tank.getGlobalBounds().width << "  -  " << _drawPlayer1Tank.getGlobalBounds().height << std::endl;
//	std::cout << "Missile Size: " << _drawMissile.getGlobalBounds().width << "  -  " << _drawMissile.getGlobalBounds().height << std::endl;
}

void Display::draw(Tank & tank, Battle::Player player)
{
	if (player == Battle::Player1)
	{
		_drawPlayer1Tank.setPosition(tank.getPosition());
		_drawPlayer1Tank.setRotation(tank.getDirection());

		_window->draw(_drawPlayer1Tank);

		_hud.DrawUI(tank, player);
	}
	else
	{
		_drawPlayer2Tank.setPosition(tank.getPosition());
		_drawPlayer2Tank.setRotation(tank.getDirection());

		_window->draw(_drawPlayer2Tank);
	}
	_hud.DrawUI(tank, player);
}

void Display::draw(std::list<std::unique_ptr<Missile>> * missile)
{
	auto _missileIterator = missile->begin();
	while(_missileIterator != missile->end())
	{
		_drawMissile.setPosition((*_missileIterator)->getPosition());
		_drawMissile.setRotation((*_missileIterator)->getDirection());

		_window->draw(_drawMissile);
		++_missileIterator;
	}

}

void Display::draw(std::list<std::unique_ptr<Explosion>> * explosion)
{
	auto _explosionIterator = explosion->begin();
	while(_explosionIterator != explosion->end())
	{
		_drawExplosion.setPosition((*_explosionIterator)->getPosition());

		_window->draw(_drawExplosion);
		++_explosionIterator;
	}
}

void Display::draw(std::list<std::unique_ptr<Obstacle>> * obstacle)
{
	auto _obstacleIterator = obstacle->begin();
	while (_obstacleIterator != obstacle->end())
	{
		_drawObstacle.setPosition((*_obstacleIterator)->getPosition());

		if((*_obstacleIterator)->remainingHits() == 0)
			_drawObstacle.setFillColor(Color::Blue);
		else
			_drawObstacle.setFillColor(Color::Red);

		_window->draw(_drawObstacle);
		++_obstacleIterator;
	}
}

void Display::draw(std::list<std::unique_ptr<Mine>> * mine)
{
	auto _mineIterator = mine->begin();
	while (_mineIterator != mine->end())
	{
		_drawMine.setPosition((*_mineIterator)->getPosition());

		_window->draw(_drawMine);
		++_mineIterator;
	}
}

void Display::initializeTank()
{
	_player1TankTexture.loadFromFile("assets/tank1.png");
	_drawPlayer1Tank.setTexture(_player1TankTexture, true);
	_player2TankTexture.loadFromFile("assets/tank2.png");
	_drawPlayer2Tank.setTexture(_player2TankTexture, true);

	_drawPlayer1Tank.setOrigin(_drawPlayer1Tank.getGlobalBounds().width/2, _drawPlayer1Tank.getGlobalBounds().height/2);
	_drawPlayer1Tank.setScale(0.05, 0.05);
	_drawPlayer2Tank.setOrigin(_drawPlayer2Tank.getGlobalBounds().width/2, _drawPlayer2Tank.getGlobalBounds().height/2);
	_drawPlayer2Tank.setScale(0.05, 0.05);
}

void Display::initializeMissile()
{
	_missileTexture.loadFromFile("assets/projectile1.png");
	_drawMissile.setTexture(_missileTexture, true);
	_drawMissile.setOrigin(_drawMissile.getGlobalBounds().width/2, _drawMissile.getGlobalBounds().height/2);
	_drawMissile.setScale(0.025,0.025);
}

void Display::initializeExplosion()
{
	_explosionTexture.loadFromFile("assets/explosion.png");
	_drawExplosion.setTexture(_explosionTexture);
	_drawExplosion.setOrigin(_drawExplosion.getGlobalBounds().width/2, _drawExplosion.getGlobalBounds().height/2);
	_drawExplosion.setScale(0.06, 0.06);
}

void Display::initializeObstacle()
{
	// Need to initialize texture here.
	_drawObstacle.setFillColor(Color::Red);
	_drawObstacle.setRotation(0);
	Vector2f windowSize{_window->getSize()};
	_drawObstacle.setSize({windowSize.x/32, windowSize.y/18});
	_drawObstacle.setOrigin({0.f, 0.f});
}

void Display::initializeMine()
{
	// Initialize mine texture.
	_mineTexture.loadFromFile("assets/mine.png");
	_drawMine.setTexture(_mineTexture);
	_drawMine.setOrigin(_drawMine.getGlobalBounds().width/2, _drawMine.getGlobalBounds().height/2);
	_drawMine.setScale(0.05,0.05);
}
