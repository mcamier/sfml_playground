#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

#include "../utils/math/vec2.hpp"

class Player {

public:
    // degree per second
    static const int speed = 90;
    static const int arc_paddle_angle_half = 4;

    int score;
    float angle;
    float angle_dest;

    Player() : angle(0), score(0) {}

    Player(float angle) : angle(angle), score(0) {}

    void setDestAsNewPos() {
        angle = angle_dest;
    }

    void resetDest() {
        angle_dest = angle;
    }
};

#endif //FOOBAR_PLAYER_HPP
