// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Obstacle.cpp

#include "Obstacle.h"

// Constructor
Obstacle::Obstacle(Vector2D position, Vector2D windowSize, TEXTURE texture) :
        AxisAligned{position, 0, {windowSize.x / 32, windowSize.y / 18}},
        _remainingHits{3},
        _texture{texture} {}

// Return number of remaining hits.
int Obstacle::remainingHits() {
    return _remainingHits;
}

// Check if the obstacle is destroyable and decrement remaining hits if it is.
bool Obstacle::isDestroyable() {
    _remainingHits--;
    return _remainingHits < 0;
}

// Return which texture to use for display.
Obstacle::TEXTURE Obstacle::getTexture() {
    return _texture;
}

Vector2D Obstacle::getTopLeft() {
    return DrawableObject::getPosition();
}

Vector2D Obstacle::getBottomRight() {
    Vector2D tempPos{DrawableObject::getPosition()};
    RectSize tempRect{DrawableObject::getSize()};

    tempPos.x += tempRect.Width;
    tempPos.y += tempRect.Height;

    return tempPos;
}
