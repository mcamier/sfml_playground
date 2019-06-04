#ifndef FOOBAR_BALL_HPP
#define FOOBAR_BALL_HPP

#include "../utils/math/vec2.hpp"
#include "header.hpp"

class Ball {
 public:
  vec2f pos;
  vec2f pos_dest;
  vec2f vector = vec2f(-1, 0);
  int speed = default_ball_speed;
  int radius = default_ball_radius;
  // By default, player one have to hit the ball first
  players last_hit_by = players::p2;

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
