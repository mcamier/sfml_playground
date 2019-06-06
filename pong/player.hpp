#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

#include "TE/math/vec2.hpp"

class Player {
 public:
  static const int width = 20;
  static const int height = 100;
  static const int speed = 200;

  int score;
  vec2f pos;
  vec2f pos_dest;

  Player() {}

  Player(vec2f pos) : pos(pos), pos_dest(pos), score(0) {}

  Player(float x, float y)
      : pos(vec2f(x, y)), pos_dest(vec2f(x, y)), score(0) {}

  void setDestAsNewPos() {
    pos.x = pos_dest.x;
    pos.y = pos_dest.y;
  }

  void resetDest() {
    pos_dest.x = pos.x;
    pos_dest.y = pos.y;
  }
};

#endif  // FOOBAR_PLAYER_HPP
