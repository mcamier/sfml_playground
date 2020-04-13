#ifndef FOOBAR_HEADER_ONG_HPP
#define FOOBAR_HEADER_ONG_HPP

#include "TE/core/stringId.hpp"
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
const messageType MSG_BALL_HIT = gInternString("MSG_BALL_HIT");
const messageType MSG_PLAYER_MOVE_LEFT = gInternString("MSG_PLAYER_MOVE_LEFT");
const messageType MSG_PLAYER_MOVE_RIGHT = gInternString("MSG_PLAYER_MOVE_RIGHT");

enum players {
    p1, p2
};

enum game_mode {
    one_player_vs_ai, one_player, two_players
};

#endif  // FOOBAR_HEADER_ONG_HPP