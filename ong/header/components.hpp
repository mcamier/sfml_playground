#ifndef TORTUGA_COMPONENTS_HPP
#define TORTUGA_COMPONENTS_HPP

#include "header.hpp"
#include <TE/ecs/component.hpp>


COMPONENT_DEF(COngBall)
public:
    int radius = default_ball_radius;
    // By default, player one have to hit the ball first
    players last_hit_by = players::p2;

    COngBall(players last_hit_by): last_hit_by(last_hit_by) {}

};

COMPONENT_DEF(COngPlayer)
public:
    players player_id;
    int score;
    int angle;
    int paddle_half_arc;

    COngPlayer(players p) {
        if (players::p1 == p) {
            this->angle = 180;
        } else {
            this->angle = 0;
        }
        this->player_id = p;
        this->paddle_half_arc = default_player_paddle_half_arc;
    }

    void clampAngle() {
        if (this->angle >= 360) {
            this->angle = this->angle % 360;
        } else if (angle < 0) {
            this->angle = 360 + this->angle;
        }
    }

};

#endif //TORTUGA_COMPONENTS_HPP
