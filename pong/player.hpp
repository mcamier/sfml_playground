#ifndef FOOBAR_PLAYER_HPP
#define FOOBAR_PLAYER_HPP

#include "../utils/vec2.hpp"

class Player {

public:
    static const int width = 20;
    static const int height = 100;
    static const int speed = 200;

    int score;
    vec2 pos;
    vec2 pos_dest;

    Player() {}

    Player(vec2 pos)
            :pos(pos), pos_dest(pos), score(0) { }

    Player(float x, float y)
            :pos(vec2(x, y)), pos_dest(vec2(x, y)), score(0) { }

    void setDestAsNewPos() {
        pos.x = pos_dest.x;
        pos.y = pos_dest.y;
    }

    void resetDest() {
        pos_dest.x = pos.x;
        pos_dest.y = pos.y;
    }

};

#endif //FOOBAR_PLAYER_HPP
