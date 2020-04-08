#ifndef FOOBAR_HEADER_ONG_HPP
#define FOOBAR_HEADER_ONG_HPP

#include "TE/hash.hpp"
#include "TE/message/message.hpp"

using namespace ta;

const int game_width = 200;
const int game_height = 200;
const int arena_radius = 75;
const int arena_defeat_radius = 100;
const int default_player_speed = 150;
const int default_player_low_speed = 50;
const int default_player_paddle_half_arc = 15;  // degrees
const int default_ball_speed = 40;
const int default_ball_radius = 4;
const int ball_count_max = 3;

// events
const messageType MSG_BALL_HIT = makeHash("MSG_BALL_HIT");
const messageType MSG_PLAYER_MOVE_LEFT = makeHash("MSG_PLAYER_MOVE_LEFT");
const messageType MSG_PLAYER_MOVE_RIGHT = makeHash("MSG_PLAYER_MOVE_RIGHT");

const messageType MSG_BALL_LOST = makeHash("MSG_BALL_LOST");
const messageType MSG_PLAYER_WIN = makeHash("MSG_PLAYER_WIN");
const messageType MSG_POWER_UP_PICKED_UP = makeHash("MSG_POWER_UP_PICKED_UP");
const messageType MSG_PLAYER_COLLIDE_BALL = makeHash("MSG_PLAYER_COLLIDE_BALL");

enum players {
    p1, p2
};

enum game_mode {
    one_player_vs_ai, one_player, two_players
};

#endif  // FOOBAR_HEADER_ONG_HPP