#ifndef FOOBAR_BALL_HPP
#define FOOBAR_BALL_HPP

#include "TE/math/vec2.hpp"

using namespace ta;

class Ball {
 public:
  static const int width = 20;
  static const int height = 20;
  static const int speed = 200;

  vec2f pos;
  vec2f pos_dest;
  vec2f vector = vec2f(0, 0);

  Ball() {}

  Ball(vec2f pos) : pos(pos), pos_dest(pos) {}

  Ball(float x, float y) : pos(vec2f(x, y)), pos_dest(vec2f(x, y)) {}

  void setDestAsNewPos() {
    pos.x = pos_dest.x;
    pos.y = pos_dest.y;
  }

  void resetDest() {
    pos_dest.x = pos.x;
    pos_dest.y = pos.y;
  }
};

#endif  // FOOBAR_BALL_HPP
