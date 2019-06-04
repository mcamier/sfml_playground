#ifndef FOOBAR_HEADER_ONG_HPP
#define FOOBAR_HEADER_ONG_HPP

const int game_width = 200;
const int game_height = 200;
const int arena_radius = 75;
const int arena_defeat_radius = 100;
const int default_player_speed = 150;
const int default_player_low_speed = 50;
const int default_player_paddle_arc = 30;  // degrees
const int default_ball_speed = 40;
const int default_ball_radius = 4;
const int ball_count_max = 3;

enum players { p1, p2 };

enum game_mode { one_player_vs_ai, one_player, two_players };

#endif  // FOOBAR_HEADER_ONG_HPP