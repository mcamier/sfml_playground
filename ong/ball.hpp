#ifndef FOOBAR_BALL_HPP
#define FOOBAR_BALL_HPP

class Ball {

public:
    static const int speed = 40;
    static const int radius = 4;

    vec2 pos;
    vec2 pos_dest;
    vec2 vector = vec2(0, 0);

    Ball() {}

    Ball(vec2 pos)
        :pos(pos), pos_dest(pos) { }

    Ball(float x, float y)
            :pos(vec2(x, y)), pos_dest(vec2(x, y)) { }

    void setDestAsNewPos() {
        pos.x = pos_dest.x;
        pos.y = pos_dest.y;
    }

    void resetDest() {
        pos_dest.x = pos.x;
        pos_dest.y = pos.y;
    }

};

#endif //FOOBAR_BALL_HPP
