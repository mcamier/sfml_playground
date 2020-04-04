#ifndef TORTUGA_COMPONENTS_HPP
#define TORTUGA_COMPONENTS_HPP

#include "header.hpp"
#include <TE/ecs/component.hpp>

class COngBall : public IComponent {
public:
    int radius = default_ball_radius;
    // By default, player one have to hit the ball first
    players last_hit_by = players::p2;

};

class COngPlayer : public IComponent {
public:
    players player_id;
    int score;
    int angle;
    int paddle_half_arc;

};

#endif //TORTUGA_COMPONENTS_HPP
