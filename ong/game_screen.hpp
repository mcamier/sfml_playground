#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

#include <iostream>

#include "math.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "../utils/math/math.hpp"
#include "../utils/screen/screen.hpp"
#include "ball.hpp"
#include "header.hpp"
#include "player.hpp"

using namespace std;

class GameScreen : public Screen {
 private:
  // all screen
  bool isLoaded = false;
  // pong game screen
  sf::Font font;
  bool round_active = false;

  Player p1 = Player(players::p1);
  Player p2 = Player(players::p2);
  Ball balls[ball_count_max];
  int collision_count = 0;
  int ball_count = 1;
  players controllable_player = players::p1;

 public:
  GameScreen() {
    this->transitionDurationSec = 0.0f;
    balls[0] = Ball(0, 20);
  }

  bool load() {
    if (!font.loadFromFile(
            "/Users/doudou/Workspaces/sfml_playground/build/ong/font.ttf")) {
      this->isLoaded = false;
      return false;
    }
    this->isLoaded = true;
    return this->isLoaded;
  }

  /**
   * @brief  Update the Game screen
   * @param  time: amount of elapsed time since the last update
   */
  void update(const sf::Time& time) override {
    float elapsedSec = time.asSeconds();

    if (!round_active) {
      return;
    }

    // update each ball consecutively
    for (int i = 0; i < ball_count; i++) {
      // move ball
      Ball& ball = balls[0];
      float ballSpeed = ball.speed * (1 + (0.15f * collision_count));
      ball.pos_dest.x = ball.pos.x + (ball.vector.x * elapsedSec * ballSpeed);
      ball.pos_dest.y = ball.pos.y + (ball.vector.y * elapsedSec * ballSpeed);

      if (ballLost(ball)) {
        collision_count = 0;
        resetBall();
        // update scores
        if (ball.last_hit_by == players::p1) {
          p1.score++;
        } else if (ball.last_hit_by == players::p2) {
          p2.score++;
        }
      }

      vec2f collision_response;
      if (ball.last_hit_by != players::p1 &&
          ballCollideWithPaddle(ball, p1, collision_response)) {
        collision_count++;
        ball.last_hit_by = players::p1;
        ball.vector = collision_response;
        // put the ball in the last non-colliding position
        ball.resetDest();
      } else if (ball.last_hit_by != players::p2 &&
                 ballCollideWithPaddle(ball, p2, collision_response)) {
        collision_count++;
        ball.last_hit_by = players::p2;
        ball.vector = collision_response;
        ball.resetDest();
      } else {
        ball.setDestAsNewPos();
      }
    }

    Player* controlled_player =
        (controllable_player == players::p1) ? &p1 : &p2;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      controlled_player->angle -= elapsedSec * default_player_speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      controlled_player->angle += elapsedSec * default_player_speed;
    }
    controlled_player->clampAngle();
  }

  /**
   * @brief Handle inputs event
   * @param  event: event to handle
   * @retval false if the event should not be propagated to the underneath scene
   */
  bool handleEvent(const sf::Event& event) override {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Key::Space) {
      if (!round_active) {
        round_active = true;
        resetBall();
      } else {
        resetBall();
      }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::Key::LShift) {
      controllable_player =
          (controllable_player == players::p1) ? players::p2 : players::p1;
    }

    return false;
  }

  /**
   * @brief  Render the game screen in the rendering target
   * @param  target: rendering target
   */
  void render(sf::RenderTexture& target) override {
    drawDebug(target);
    drawPlayer(target, p1);
    drawPlayer(target, p2);
    drawBall(target, balls[0]);
  }

 private:
  void resetBall() {
    this->ball_count = 1;
    this->balls[0] = Ball(0, 20);
    this->balls[0].vector = angleToVec(180);
  }

  bool ballLost(Ball& ball) {
    return isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y,
                           arena_defeat_radius);
  }

  bool ballCollideWithPaddle(const Ball& ball, const Player& player,
                             vec2f& collision_response) {
    if (isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y,
                        arena_radius - ball.radius) &&
        isInsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_radius)) {
      if (collideWithArc(ball, player)) {
        // if collision occurs then compute the collision response
        vec2f norm = angleToVec(player.angle);
        vec2f incidence = ball.vector;
        float x = vec2f::dot(norm, incidence);

        vec2f reflect = incidence - (2 * (incidence - (x * norm)));
        collision_response = -reflect;
        return true;
      }
    }
    return false;
  }

  bool collideWithArc(const Ball& ball, const Player& player) {
    vec2f ball_pos(ball.pos_dest);
    ball_pos.normalize();
    int ball_degrees = vectorToDegrees(ball_pos);
    int player_degrees = player.angle;

    if (player_degrees <= player.paddle_half_arc) {
      float max = player_degrees + player.paddle_half_arc;
      float sub_360 = 360 - (player_degrees - player.paddle_half_arc);
      return ball_degrees <= max &&
             (ball_degrees >= 0 || ball_degrees >= sub_360);
    } else if (player_degrees >= (360 - player.paddle_half_arc)) {
      float min = player_degrees - player.paddle_half_arc;
      float up_0 = 360 - player_degrees;
      return ball_degrees >= min &&
             (ball_degrees <= 360 || ball_degrees <= up_0);
    } else {
      float min = player_degrees - player.paddle_half_arc;
      float max = player_degrees + player.paddle_half_arc;
      return ball_degrees >= min && ball_degrees <= max;
    }
  }

  void drawDebug(sf::RenderTexture& tex) {
    sf::RectangleShape vline(sf::Vector2f(1.f, game_height));
    vline.setPosition(game_width / 2, 0);
    vline.setFillColor(sf::Color::Magenta);
    sf::RectangleShape hline(sf::Vector2f(game_width, 1.f));
    hline.setPosition(0, game_height / 2);
    hline.setFillColor(sf::Color::Magenta);
    tex.draw(vline);
    tex.draw(hline);

    sf::CircleShape arena(arena_radius);
    arena.setFillColor(sf::Color::Transparent);
    arena.setOutlineColor(sf::Color::Magenta);
    arena.setOutlineThickness(1);
    arena.setOrigin(0, 0);
    arena.setPosition(25, 25);
    tex.draw(arena);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(8);
    text.setFillColor(sf::Color::White);
    text.setString("test");
    tex.draw(text);
  }

  void drawPlayer(sf::RenderTexture& tex, Player& player) {
    static float cos_half_pi = -0.999624217;
    static float sin_half_pi = -0.027412134;
    int segment_count = 3;
    float segment_arc_angle =
        (float)(player.paddle_half_arc * 2) / segment_count;
    float segment_length = toRad(segment_arc_angle) * arena_radius;
    int min_angle = player.angle - player.paddle_half_arc;

    sf::RectangleShape rect(sf::Vector2f(segment_length, 4));

    if (player.player_id == players::p1) {
      rect.setFillColor(sf::Color::Red);
    } else {
      rect.setFillColor(sf::Color::Blue);
    }

    for (int i = 0; i < segment_count; i++) {
      float angle = min_angle + i * segment_arc_angle;
      vec2f p = getPointOnArc(angle, arena_radius);

      vec2f v = angleToVec(angle);
      v.x = -v.x * cos_half_pi + v.y * sin_half_pi;
      v.y = -v.x * sin_half_pi - v.y * cos_half_pi;

      rect.setPosition(p.x + game_width / 2, p.y + game_height / 2);
      float pouet = vectorToDegrees(v);
      rect.rotate(pouet);
      tex.draw(rect);
    }
  }

  void drawBall(sf::RenderTexture& tex, const Ball& ball) {
    sf::CircleShape shape(ball.radius);
    shape.setPosition(ball.pos.x + game_width / 2,
                      ball.pos.y + game_height / 2);
    if (ball.last_hit_by == players::p1) {
      shape.setFillColor(sf::Color::Red);
    } else {
      shape.setFillColor(sf::Color::Blue);
    }
    tex.draw(shape);
  }
};

#endif
