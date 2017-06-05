// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - HUD.cpp

#include "HUD.h"

namespace game::display {

// Constructor:
    HUD::HUD(std::shared_ptr<RenderWindow> window) :
            _window{window} {
        _font.loadFromFile("assets/CRYSTAL-Regular.ttf");

        _description.setFont(_font);
        _description.setOrigin({0.f, 0.f});
        _description.setCharacterSize(20);
        _description.setStyle(Text::Regular);
        _description.setFillColor(Color::White);
    }

// Draw the UI for a particular player (Display remaining ammo for the tank).
    void HUD::DrawUI(Tank &tank, Score::PLAYER player) {
        int mines = tank.getAllowedMines();
        std::string tempString;
        Vector2f tempLocation;
        if (player == Score::PLAYER1) {
            tempLocation = Vector2f{10.f, (float) _window->getSize().y - 30.f};
            displayString("Tank 1 Mines: ", tempLocation);
            tempString = intToString(mines);
            tempLocation = Vector2f{160.f, (float) _window->getSize().y - 30.f};
            displayString(tempString, tempLocation);
        } else {
            tempLocation = Vector2f{(float) _window->getSize().x - 180.f, (float) _window->getSize().y - 30.f};
            displayString("Tank 2 Mines: ", tempLocation);
            tempString = intToString(mines);
            tempLocation = Vector2f{(float) _window->getSize().x - 20.f, (float) _window->getSize().y - 30.f};
            displayString(tempString, tempLocation);
        }
    }

// Draw the score of the game.
    void HUD::DrawScore(Score &score, bool isPaused) {
        Vector2f windowSize{_window->getSize()};
        std::string tempString;

        displayScore(score);

        // Display message:
        if (isPaused) {
            // Display this message if the score screen is in the pause menu.
            tempString = "Press ESC to resume game.";
            displayString(tempString, {windowSize.x / 16, windowSize.y * 8 / 9});
            tempString = "Press Q to quit game, or P to restart game.";
            displayString(tempString, {windowSize.x / 16, windowSize.y * 8 / 9 + 30});
        } else {
            // Display this message for end of game score screen.
            tempString = "Press Q to end game, or press P to play again.";
            displayString(tempString, {windowSize.x / 16, windowSize.y * 8 / 9});
        }
    }

// Display the score screen for the game, showing kills and deaths for each player.
    void HUD::displayScore(Score &score) {
        Vector2f windowSize{_window->getSize()};
        std::string tempString;

        displayString("SCORE:", {windowSize.x / 16, windowSize.y / 9}, 40);
        displayString("Kills", {windowSize.x / 16 + 200, windowSize.y / 9 + 120});
        displayString("Deaths", {windowSize.x / 16 + 300, windowSize.y / 9 + 120});
        // Player 1
        displayString("Player 1: ", {windowSize.x / 16, windowSize.y / 9 + 150});
        tempString = intToString(score.getKills(Score::PLAYER1));
        displayString(tempString, {windowSize.x / 16 + 200, windowSize.y / 9 + 150});
        tempString = intToString(score.getDeaths(Score::PLAYER1));
        displayString(tempString, {windowSize.x / 16 + 300, windowSize.y / 9 + 150});
        // Player 2
        displayString("Player 2: ", {windowSize.x / 16, windowSize.y / 9 + 180});
        tempString = intToString(score.getKills(Score::PLAYER2));
        displayString(tempString, {windowSize.x / 16 + 200, windowSize.y / 9 + 180});
        tempString = intToString(score.getDeaths(Score::PLAYER2));
        displayString(tempString, {windowSize.x / 16 + 300, windowSize.y / 9 + 180});
    }

// Draw the time remaining on the game screen.
    void HUD::DrawTimer(float remainingTime) {
        std::string tempString;

        displayString("Time Remaining: ", {10, 10});
        tempString = floatToString(remainingTime);
        displayString(tempString, {180, 10});
    }

    void HUD::DrawSplash() {
        Vector2f windowSize{_window->getSize()};
        std::string tempString = "Press Q to quit the game.";
        displayString(tempString, {windowSize.x / 16, windowSize.y * 8 / 9});
        tempString = "Or press P to start a new game. ";
        displayString(tempString, {windowSize.x / 16, windowSize.y * 8 / 9 + 30.f});
    }

// Convert float to string.
    std::string HUD::floatToString(float input) {
        std::ostringstream buffer;
        buffer << input;
        return buffer.str();
    }

// Convert int to string.
    std::string HUD::intToString(int input) {
        std::ostringstream buffer;
        buffer << input;
        return buffer.str();
    }

// Display a particular string on the screen.
    void HUD::displayString(std::string str, Vector2f location, unsigned int size) {
        _description.setCharacterSize(size);
        _description.setPosition(location);
        _description.setString(str);

        _window->draw(_description);
    }

}
