// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - HUD.h

#ifndef HUD_H_
#define HUD_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <memory>
#include "../gameplay/Battle.h"
#include "../gameplay/Score.h"

namespace game::display {

    using namespace sf;

    //! HUD class to display text.
    /*!
     * This class is used as a sub class of Display in order to
     * draw any text onto the sf::RenderWindow.
     */
    class HUD {
    public:
        // Initializer.
        //! HUD Constructor.
        /*!
         * Initializes the sf::RenderWindow pointer and the fonts
         * required for display.
         * \param window The pointer to the sf::RenderWindow.
         */
        HUD(std::shared_ptr<RenderWindow> window);
        // DrawUI for a tank.
        //! Draw the UI for the tank.
        /*!
         * This displays remaining ammunitions during the game (Mines)
         * belonging to a particular tank.
         * \param tank The tank that the remaining ammunition belongs to.
         * \param player The player that the tank belongs to.
         */
        void DrawUI(Tank &tank, Score::PLAYER player);
        //! Draw score screen.
        /*!
         * This displays the score screen on the sf::RenderWindow,
         * it requires the score and checks to display the pause
         * screen or end game screen.
         * \param score The Score of the current game.
         * \param isPaused This boolean is to check if the HUD should display the end game screen or pause screen.
         */
        void DrawScore(Score &score, bool isPaused);
        //! Displays the remaining time on the display.
        /*!
         * Displays remaining time on sf::DisplayWindow.
         * \param remainingTime The amount of time left in the game.
         */
        void DrawTimer(float remainingTime);
        //! Displays the splash screen text.
        /*!
         * This function is used to display the text for the splash screen.
         */
        void DrawSplash();

    private:
        // Private member variables.
        //! Shared pointer to the RenderWindow.
        std::shared_ptr<RenderWindow> _window;
        //! Font file for display.
        Font _font;
        //! The text that will be displayed.
        Text _description;

        // Converts a float to a string.
        //! Convert from a float to a string.
        //! \param input The float to be converted to string.
        std::string floatToString(float input);

        //! Convert from an int to a string.
        //! \param input The int to be converted to string.
        std::string intToString(int input);

        // Display the score screen.
        //! Display the score on the screen.
        //! \param score The in game score.
        void displayScore(Score &score);
        // Display a string in a particular location.
        //! Display any string.
        /*!
         * Displays the string in a particular location and with a defined font size.
         * \param str The string to be displayed.
         * \param location The location of the top left corner of the string.
         * \param size The font size.
         */
        void displayString(std::string str, Vector2f location, unsigned int size = 20);
    };
}

#endif /* HUD_H_ */
