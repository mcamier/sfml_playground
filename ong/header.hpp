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
messageType_t MSG_BALL_LOST = makeHash("MSG_BALL_LOST");
messageType_t MSG_PLAYER_WIN = makeHash("MSG_PLAYER_WIN");
messageType_t MSG_POWER_UP_PICKED_UP = makeHash("MSG_POWER_UP_PICKED_UP");
messageType_t MSG_PLAYER_COLLIDE_BALL = makeHash("MSG_PLAYER_COLLIDE_BALL");

enum players { p1, p2 };

enum game_mode { one_player_vs_ai, one_player, two_players };

#endif  // FOOBAR_HEADER_ONG_HPP