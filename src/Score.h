#ifndef PLAYERS_H_
#define PLAYERS_H_

class Score
{
public:
	enum PLAYER{PLAYER1 = 1, PLAYER2};
	Score(const Score & score);
	Score(int player1Score = 0, int player2Score = 0);
	// Return the score for a certain player.
	int getKills(PLAYER player);
	int getDeaths(PLAYER player);
	void increaseKills(PLAYER player);
	void increaseDeaths(PLAYER player);

	Score & operator=(const Score & rhs);
private:
	int _player1Kills;
	int _player1Deaths;
	int _player2Kills;
	int _player2Deaths;
};

#endif /* PLAYERS_H_ */
