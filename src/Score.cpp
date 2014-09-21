#include "Score.h"

Score::Score(const Score & score) :
 	 _player1Kills{score._player1Kills},
 	 _player1Deaths{score._player1Deaths},
 	 _player2Kills{score._player2Kills},
 	 _player2Deaths(score._player2Deaths)
{}

Score::Score(int player1Score, int player2Score) :
	_player1Kills{player1Score},
	_player1Deaths{player1Score},
	_player2Kills{player2Score},
	_player2Deaths{player2Score}
{}

Score & Score::operator=(const Score & rhs)
{
	this->_player1Kills = rhs._player1Kills;
	this->_player1Deaths = rhs._player1Deaths;
	this->_player2Kills = rhs._player2Kills;
	this->_player2Deaths = rhs._player2Deaths;

	return *this;
}

void Score::increaseKills(PLAYER player)
{
	if(player == PLAYER1)
		_player1Kills++;
	else
		_player2Kills++;
}

void Score::increaseDeaths(PLAYER player)
{
	if(player == PLAYER1)
		_player1Deaths++;
	else
		_player2Deaths++;
}

int Score::getKills(PLAYER player)
{
	if(player == PLAYER1)
		return _player1Kills;
	else
		return _player2Kills;
}

int Score::getDeaths(PLAYER player)
{
	if(player == PLAYER1)
		return _player1Deaths;
	else
		return _player2Deaths;
}
