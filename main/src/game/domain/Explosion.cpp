// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Explosion.cpp

#include "Explosion.h"

namespace game::domain {

  using std::chrono::high_resolution_clock;

// Constructor:
    Explosion::Explosion(Vector2D position) :
            DrawableObject{position, 0, {0, 0}},
            _explosionTimer{high_resolution_clock::now()} {
        _size.Width = 0;
        _size.Height = 0;
    }

// Return the time of the explosion.
  high_resolution_clock::time_point Explosion::getExplosionTime() {
        return _explosionTimer;
    }

}
