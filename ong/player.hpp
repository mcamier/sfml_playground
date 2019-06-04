#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

#include "header.hpp"

class Player {
 public:
  players player_id;
  int score;
  int angle;
  int paddle_arc;

  Player(players p) {
    if (players::p1 == p) {
      this->angle = 180;
    } else {
      this->angle = 0;
    }
    this->player_id = p;
    this->paddle_arc = default_player_paddle_arc;
  }

  void clampAngle() {
    if (this->angle >= 360) {
      this->angle = this->angle % 360;
    } else if (angle < 0) {
      this->angle = 360 + this->angle;
    }
  }

  void update(sf::Time& elapsedTime) {}
};

#endif  // FOOBAR_PLAYER_HPP
