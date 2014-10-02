// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Score.h

#ifndef PLAYERS_H_
#define PLAYERS_H_

class Score
{
public:
	// Which player the score is for.
	enum PLAYER{PLAYER1 = 1, PLAYER2, NONPLAYER};
	Score(const Score & score);
	Score(int player1Score = 0, int player2Score = 0);
	// Return the score for a certain player.
	int getKills(PLAYER player);
	int getDeaths(PLAYER player);
	// Increase kills or deaths for a player.
	void increaseKills(PLAYER player);
	void increaseDeaths(PLAYER player);
	// Copy operator.
	Score & operator=(const Score & rhs);
private:
	// Private member variables.
	int _player1Kills;
	int _player1Deaths;
	int _player2Kills;
	int _player2Deaths;
};

#endif /* PLAYERS_H_ */
