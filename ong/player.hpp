#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

#include "../utils/math/vec2.hpp"

class Player {

public:

    static const int speed = 75; // degree per second

    int score;
    float angle;
    float angle_dest;
    float paddle_length = 25;

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
