// Anthony Farquharson - 563648
// Frederick Nieuwoudt - 386372
// ELEN3009 Game - Turret.cpp

#include "Turret.h"

namespace game::domain {

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  Turret::Turret(Vector2D position, Vector2D range, Vector2D screenSize) :
    AxisAligned{position, (range.x + range.y) / 2, {40.f * screenSize.x / 1600.f, 40.f * screenSize.y / 900.f}},
    _range{range},
    _pi{(const float) (atan(1) * 4)},
    _isClockwise{true},
    _fireTime{high_resolution_clock::now()},
    _lockDistance{500 * screenSize.x / 1600} {}

  bool Turret::canFollowTarget(DrawableObject &target, bool TargetInvisible) {
    float distance = (float) sqrt(pow(target.getPosition().x - _position.x, 2) +
                                  pow(target.getPosition().y - _position.y, 2));
    Angle direction = (float) atan2(_position.y - target.getPosition().y,
                                    _position.x - target.getPosition().x) / _pi * 180;

    if (distance < _lockDistance && (direction.getAngle() - DrawableObject::_direction.getAngle() < 5
                                     && direction.getAngle() - DrawableObject::_direction.getAngle() > -5)
        && (direction > _range.x && direction < _range.y)
        && !TargetInvisible) {
      DrawableObject::_direction = direction;
      return true;
    } else
      return false;
  }

  bool Turret::canFireMissile() {
    if (duration_cast<milliseconds>( high_resolution_clock::now() - _fireTime ).count()  > 500) {
      _fireTime = high_resolution_clock::now();
      return true;
    } else return false;
  }

  void Turret::update() {
    if (DrawableObject::_direction.getAngle() >= _range.y)
      _isClockwise = false;
    else if (DrawableObject::_direction.getAngle() <= _range.x)
      _isClockwise = true;

    if (_isClockwise)
      DrawableObject::_direction += 0.5;
    else if (!_isClockwise)
      DrawableObject::_direction -= 0.5;
  }

  Vector2D Turret::getFirePosition() {
    float cornerDist = (float) sqrt(pow(_size.Height / 2, 2) + pow(_size.Width / 2, 2));
    Vector2D firePosition{_position};

    firePosition.x -= cornerDist * (cos(DrawableObject::_direction.getAngleRadians()));
    firePosition.y -= cornerDist * (sin(DrawableObject::_direction.getAngleRadians()));

    return firePosition;
  }
}
