#ifndef FOOBAR_BALL_HPP
#define FOOBAR_BALL_HPP

#include "../utils/math/vec2.hpp"

class Ball {
 public:
  vec2f pos;
  vec2f pos_dest;
  vec2f vector = vec2f(0, 0);
  int speed;
  int radius;

  Ball() {}

  Ball(vec2f pos)
      : pos(pos),
        pos_dest(pos),
        speed(default_ball_speed),
        radius(default_ball_radius) {}

  Ball(float x, float y)
      : pos(vec2f(x, y)),
        pos_dest(vec2f(x, y)),
        speed(default_ball_speed),
        radius(default_ball_radius) {}

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
