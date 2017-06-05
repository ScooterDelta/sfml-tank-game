// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Score.h

#ifndef PLAYERS_H_
#define PLAYERS_H_

namespace game::gameplay {

//! Class to store the Score of the game.
/*!
 * The class will hold the number of deaths and kills
 * for each player active in the game.
 */
    class Score {
    public:
        // Which player the score is for.
        //! enum defining which player has a particular score.
        enum PLAYER {
            PLAYER1 = 1,    //!< Player 1.
            PLAYER2,        //!< Player 2.
            NONPLAYER        //!< Non player Character (NPC).
        };
        //! Copy constructor.
        /*!
         * Copies the number of deaths, and kills for each player in the
         * score object.
         * \param score Score object to be copied.
         */
        Score(const Score &score);
        //! Overloaded Constructor.
        /*!
         * Initializes all members of the Score class to 0,
         * unless other values are given.
         * \param player1Score Number of kills belonging to player 1.
         * \param player2Score Number of kills belonging to player 2.
         */
        Score(int player1Score = 0, int player2Score = 0);

        // Return the score for a certain player.
        //! Return the number of kills belonging to player.
        //! \param player The player that the kills must be fetched for.
        int getKills(PLAYER player);

        //! Return the number of deaths belonging to player.
        //! \param player The player that the deaths must be fetched for.
        int getDeaths(PLAYER player);

        // Increase kills or deaths for a player.
        //! Increase the kills for a particular player.
        //! \param player The PLAYER that the kills must be increased for.
        void increaseKills(PLAYER player);

        //! Increase the deaths for a particular player.
        //! \param player The PLAYER that the deaths must be increased for.
        void increaseDeaths(PLAYER player);
        // Copy operator.
        //! Copy operator.
        /*!
         * The number of kills and deaths of each player are copied into the
         * object from the Score object passed in.
         * \param rhs The object that is being copied.
         */
        Score &operator=(const Score &rhs);

    private:
        // Private member variables.
        //! Amount of kills for PLAYER1
        int _player1Kills;
        //! Amount of kills for PLAYER2
        int _player1Deaths;
        //! Amount of deaths for PLAYER1
        int _player2Kills;
        //! Amount of deaths for PLAYER2
        int _player2Deaths;
    };
}

#endif /* PLAYERS_H_ */
