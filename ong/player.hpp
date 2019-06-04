#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

class Player {
 public:
  static const int speed = 150;     // degree per second
  static const int low_speed = 50;  // degree per second

  int score;
  int angle;
  int angle_dest;
  int paddle_arc = 30;  // degrees

  Player() : angle(0), angle_dest(0), score(0) {}

  Player(int angle) : angle(angle), angle_dest(angle), score(0) {}

  void setDestAsNewPos() { angle = angle_dest; }

  void resetDest() { angle_dest = angle; }

  void update(sf::Time& elapsedTime) {}
};

#endif  // FOOBAR_PLAYER_HPP
