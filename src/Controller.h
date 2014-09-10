#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller
{
public:
	// Enum of the players in the game.
	enum Players{Player1 = 0, Player2, Player3, Player4};

private:
	Players _player;
	std::vector<sf::Keyboard::Key> _controls;
};



#endif /* PLAYER_H_ */
