#include "Battle.h"

Battle::Battle(RenderWindow * window) :
	_window{window}
{
	// Initialization code goes here.
}

void Battle::setControls(Controller::Players & player)
{
	std::vector<Keyboard::Key> controls1{Keyboard::W, Keyboard::A, Keyboard::S, Keyboard::D, Keyboard::Space};
	std::vector<Keyboard::Key> controls2{Keyboard::Up, Keyboard::Left, Keyboard::Down, Keyboard::Right, Keyboard::RControl};
	switch (player)
	{
	case 0:
		_playerControls.push_back(controls1);
		break;
	case 1:
		_playerControls.push_back(controls2);
		break;
	case 2:
	case 3:
		break;
	}
}

void Battle::addTank(Vector2f position, Controller::Players player, Color color)
{
	unique_ptr<Tank> newTank(new Tank{_window, &_missiles, position});
	unique_ptr<HUD> newHUD(new HUD{_window, player});
	_tanks.push_back(std::move(newTank));
	setControls(player);
	_HUDs.push_back(std::move(newHUD));
}

void Battle::update()
{
	// Update all missile objects (delete if they leave the bounds of the screen)
	auto _missileIterator = _missiles.begin();
	while(_missileIterator != _missiles.end())
	{
		if((*_missileIterator)->updateIsDestroyed())
			_missileIterator = _missiles.erase(_missileIterator);
		else
			++_missileIterator;
	}

	auto _tankIterator = _tanks.begin();
	auto _tankRevIterator = _tanks.end();
	auto _controlIterator = _playerControls.begin();
	auto _hudIterator = _HUDs.begin();

	while (_tankIterator != _tanks.end())
	{
		--_tankRevIterator;

		missileHit(_tankIterator);

		if(Keyboard::isKeyPressed((*_controlIterator)[0]) && !isFrontWallCollision(_tankIterator)
				&& !isFrontTankCollision(_tankIterator, _tankRevIterator))
			(*_tankIterator)->setMovement(Tank::FORWARD);

		else if(Keyboard::isKeyPressed((*_controlIterator)[2]) && !isBackWallCollision(_tankIterator)
				&& !isBackTankCollision(_tankIterator, _tankRevIterator))
			(*_tankIterator)->setMovement(Tank::BACKWARD);

		else (*_tankIterator)->setMovement(Tank::NONE);

		if(Keyboard::isKeyPressed((*_controlIterator)[1]))
			(*_tankIterator)->setMovement(Tank::ANTICLOCKWISE);
		else if(Keyboard::isKeyPressed((*_controlIterator)[3]))
			(*_tankIterator)->setMovement(Tank::CLOCKWISE);
		else (*_tankIterator)->setMovement(Tank::STRAIGHT);

		if(Keyboard::isKeyPressed((*_controlIterator)[4])) (*_tankIterator)->fireWeapon();

		(*_tankIterator)->update();

		if((*_tankIterator)->getLife() <= 0)
		{
			(*_tankIterator)->respawn();
		}

		(*_hudIterator)->update((*_tankIterator)->getLife());

		++_tankIterator;
		++_controlIterator;
		++_hudIterator;
	}
}

bool Battle::isFrontWallCollision(Tank_iter & tankIterator)
{
	Vector2f tempContainerFL = (*tankIterator)->frontLeft();
	Vector2f tempContainerFR = (*tankIterator)->frontRight();

	if (tempContainerFL.x < 0 || tempContainerFL.y < 0 || tempContainerFL.x > _window->getSize().x || tempContainerFL.y > _window->getSize().y)
		return true;
	else if (tempContainerFR.x < 0 || tempContainerFR.y < 0 || tempContainerFR.x > _window->getSize().x || tempContainerFR.y > _window->getSize().y)
		return true;
	else
		return false;
}

bool Battle::isBackWallCollision(Tank_iter & tankIterator)
{

	Vector2f tempContainerBL = (*tankIterator)->backLeft();
	Vector2f tempContainerBR = (*tankIterator)->backRight();

	if (tempContainerBL.x < 0 || tempContainerBL.y < 0 || tempContainerBL.x > _window->getSize().x || tempContainerBL.y > _window->getSize().y)
		return true;
	else if (tempContainerBR.x < 0 || tempContainerBR.y < 0 || tempContainerBR.x > _window->getSize().x || tempContainerBR.y > _window->getSize().y)
		return true;
	else
		return false;
}

void Battle::missileHit(Tank_iter & tankIterator)
{
	std::vector<Vector2f> tankVertex;
	tankVertex.push_back((*tankIterator)->frontLeft());	// 0 - Front Left
	tankVertex.push_back((*tankIterator)->frontRight()); // 1 - Front Right
	tankVertex.push_back((*tankIterator)->backRight()); // 2 - back Right
	tankVertex.push_back((*tankIterator)->backLeft()); // 3 - back left

	Vector2f _missileCenter;
	std::vector<Vector2f> _missileVertex;

	auto _missileIterator = _missiles.begin();
	while(_missileIterator != _missiles.end())
	{
		_missileCenter.x = (*_missileIterator)->getPosition().x;
		_missileCenter.y = (*_missileIterator)->getPosition().y;
		_missileVertex.clear();
		_missileVertex.push_back(_missileCenter);
		if(isPolyCollision(tankVertex, _missileVertex))
		{
			_missileIterator = _missiles.erase(_missileIterator);
			(*tankIterator)->takeDamage(10.f);
		}
		else
			++_missileIterator;
	}
}

bool Battle::isFrontTankCollision(Tank_iter & aTank, Tank_iter & bTank)
{
	std::vector<Vector2f> aTankVertex, bTankVertex;
	aTankVertex.push_back((*aTank)->frontLeft());	// 0 - Front Left
	aTankVertex.push_back((*aTank)->frontRight()); // 1 - Front Right
	aTankVertex.push_back((*aTank)->backRight()); // 2 - back Right
	aTankVertex.push_back((*aTank)->backLeft()); // 3 - back left

	bTankVertex.push_back((*bTank)->frontLeft());	// 0 - Front Left
	bTankVertex.push_back((*bTank)->frontRight()); // 1 - Front Right
	bTankVertex.push_back((*bTank)->backRight()); // 2 - back Right
	bTankVertex.push_back((*bTank)->backLeft()); // 3 - back left

	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2f aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2f aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2f bTankCenter{(*bTank)->getPosition()};

		double frontDistance = sqrt(pow(aTankFront.x - bTankCenter.x, 2) + pow(aTankFront.y - bTankCenter.y, 2));
		double backDistance = sqrt(pow(aTankBack.x - bTankCenter.x, 2) + pow(aTankBack.y - bTankCenter.y, 2));

		if(frontDistance < backDistance)
			return true;
		else return false;
	}
	else
		return false;
}

bool Battle::isBackTankCollision(Tank_iter & aTank, Tank_iter & bTank)
{
	std::vector<Vector2f> aTankVertex, bTankVertex;
	aTankVertex.push_back((*aTank)->frontLeft());	// 0 - Front Left
	aTankVertex.push_back((*aTank)->frontRight()); // 1 - Front Right
	aTankVertex.push_back((*aTank)->backRight()); // 2 - back Right
	aTankVertex.push_back((*aTank)->backLeft()); // 3 - back left

	bTankVertex.push_back((*bTank)->frontLeft());	// 0 - Front Left
	bTankVertex.push_back((*bTank)->frontRight()); // 1 - Front Right
	bTankVertex.push_back((*bTank)->backRight()); // 2 - back Right
	bTankVertex.push_back((*bTank)->backLeft()); // 3 - back left

	if(isPolyCollision(aTankVertex, bTankVertex))
	{
		Vector2f aTankFront{(aTankVertex[0].x + aTankVertex[1].x)/2, (aTankVertex[0].y + aTankVertex[1].y)/2};
		Vector2f aTankBack{(aTankVertex[2].x + aTankVertex[3].x)/2, (aTankVertex[2].y + aTankVertex[3].y)/2};
		Vector2f bTankCenter{(*bTank)->getPosition()};

		double frontDistance = sqrt(pow(aTankFront.x - bTankCenter.x, 2) + pow(aTankFront.y - bTankCenter.y, 2));
		double backDistance = sqrt(pow(aTankBack.x - bTankCenter.x, 2) + pow(aTankBack.y - bTankCenter.y, 2));

		if(frontDistance > backDistance)
			return true;
		else return false;
	}
	else
		return false;
}

bool Battle::isPolyCollision(std::vector<Vector2f> & aVertex, std::vector<Vector2f> & bVertex)
{
	Vector2f polyAxis{0,0};
	double tmp, minA, maxA, minB, maxB;

	for (unsigned int polySide = 0; polySide < aVertex.size(); polySide++)
	{
		// Get the axis that we will project onto.
		if (polySide == 0)
		{
			polyAxis.y = aVertex[aVertex.size() - 1].y - aVertex[0].y;
			polyAxis.x = aVertex[aVertex.size() - 1].x - aVertex[0].x;
		}
		else
		{
			polyAxis.y = aVertex[polySide].y - aVertex[polySide - 1].y;
			polyAxis.x = aVertex[polySide].x - aVertex[polySide - 1].x;
		}
		// Project A onto axis. (Dot product)
		minA = maxA = aVertex[0].x * polyAxis.x + aVertex[0].y * polyAxis.y;
		for(unsigned int i = 1; i < aVertex.size(); i++)
		{
			tmp = aVertex[i].x * polyAxis.x + aVertex[i].y * polyAxis.y;
			if(tmp > maxA)
				maxA = tmp;
			else if (tmp < minA)
				minA = tmp;
		}

		// Project B onto axis.

		minB = maxB = bVertex[0].x * polyAxis.x + bVertex[0].y * polyAxis.y;
		for(unsigned int i = 1; i < bVertex.size(); i++)
		{
			tmp = bVertex[i].x * polyAxis.x + bVertex[i].y * polyAxis.y;
			if(tmp > maxB)
				maxB = tmp;
			else if (tmp < minB)
				minB = tmp;
		}

		if(maxA < minB || minA > maxB)
			return false;
	}

	if(bVertex.size() > 1)
	{
		for (unsigned int polySide = 0; polySide < bVertex.size(); polySide++)
		{
			// Get projection axis.
			if (polySide == 0)
			{
				polyAxis.y = bVertex[bVertex.size() - 1].y - bVertex[0].y;
				polyAxis.x = bVertex[bVertex.size() - 1].x - bVertex[0].x;
			}
			else
			{
				polyAxis.y = bVertex[polySide].y - bVertex[polySide - 1].y;
				polyAxis.x = bVertex[polySide].x - bVertex[polySide - 1].x;
			}
			// Project A onto axis. (Dot product)
			minA = maxA = aVertex[0].x * polyAxis.x + aVertex[0].y * polyAxis.y;
			for(unsigned int i = 1; i < aVertex.size(); i++)
			{
				tmp = aVertex[i].x * polyAxis.x + aVertex[i].y * polyAxis.y;
				if(tmp > maxA)
					maxA = tmp;
				else if (tmp < minA)
					minA = tmp;
			}

			// Project B onto axis.
			minB = maxB = bVertex[0].x * polyAxis.x + bVertex[0].y * polyAxis.y;
			for(unsigned int i = 1; i < bVertex.size(); i++)
			{
				tmp = bVertex[i].x * polyAxis.x + bVertex[i].y * polyAxis.y;
				if(tmp > maxB)
					maxB = tmp;
				else if (tmp < minB)
					minB = tmp;
			}

			if(maxA < minB || minA > maxB)
				return false;
		}
	}

	return true;
}
