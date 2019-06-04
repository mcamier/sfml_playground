#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

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

 public:
  GameScreen() {
    this->transitionDurationSec = 0.0f;
    balls[0] = Ball(0, 0);
  }

  bool load() {
    if (!font.loadFromFile("PressStart2P.ttf")) {
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

    for (int i = 0; i < ball_count; i++) {
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
      if (ballCollideWithPaddle(ball, p1)) {
        collision_count++;
        ball.vector.x = -ball.vector.x;
        ball.vector.y = -ball.vector.y;
        ball.resetDest();
      }
      // else if (ballCollideWithPaddle(ball, p2)) {}
      else {
        ball.setDestAsNewPos();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      p1.angle -= elapsedSec * default_player_speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      p1.angle += elapsedSec * default_player_speed;
    }
    p1.clampAngle();
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
    }

    return false;
  }

  /**
   * @brief  Render the game screen in the rendering target
   * @param  target: rendering target
   */
  void render(sf::RenderTexture& target) override {
    drawDebug(target);
    drawBall(target, balls[0]);
    drawPlayer(target, p1);
  }

 private:
  void resetBall() {
    this->ball_count = 1;
    this->balls[0] = Ball(0, 0);
    this->balls[0].vector = angleToVec(180);
  }

  bool ballLost(Ball& ball) {
    return isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y,
                           arena_defeat_radius);
  }

  bool ballCollideWithPaddle(Ball& ball, Player& player) {
    if (isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y,
                        arena_radius - ball.radius) &&
        isInsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_radius)) {
      if (collideWithArc(ball, player)) {
        return true;
      }
    }
    return false;
  }

  bool collideWithArc(Ball& ball, Player& player) {
    float phi, min, max;
    phi = min = max = .0f;

    vec2f p(ball.pos_dest.x, ball.pos_dest.y);
    p.normalize();
    p.y = -p.y;
    phi = vectorToDegrees(p);

    int half_angle = player.paddle_arc / 2;
    min = player.angle - half_angle;
    max = player.angle + half_angle;

    bool res = phi >= min && phi <= max;
    return res;
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
  }

  void drawPlayer(sf::RenderTexture& tex, Player& player) {
    static float cos_half_pi = -0.999624217;
    static float sin_half_pi = -0.027412134;
    int segment_count = 3;
    float segment_arc_angle = (float)player.paddle_arc / segment_count;
    float segment_length = toRad(segment_arc_angle) * arena_radius;
    int min_angle = player.angle - player.paddle_arc / 2;

    sf::RectangleShape rect(sf::Vector2f(segment_length, 4));
    rect.setFillColor(sf::Color::Red);

    for (int i = 0; i < segment_count; i++) {
      float angle = min_angle + i * segment_arc_angle;
      vec2f p = getPointOnArc(angle, arena_radius);

      vec2f v = angleToVec(angle);
      // v.x = -v.x;
      // v.y = -v.y;
      v.x = -v.x * cos_half_pi + v.y * sin_half_pi;
      v.y = -v.x * sin_half_pi - v.y * cos_half_pi;

      rect.setPosition(p.x + game_width / 2, p.y + game_height / 2);
      float pouet = vectorToDegrees(v);
      rect.rotate(pouet);
      tex.draw(rect);
    }

    /*sf::CircleShape shape(3);
    shape.setFillColor(sf::Color::White);

    vec2 p = getPointOnArc(player.angle-half_angle, arena_radius);
    shape.setPosition(p.x+game_width/2, p.y+game_height/2);
    tex.draw(shape);

    p = getPointOnArc(player.angle+half_angle, arena_radius);
    shape.setPosition(p.x+game_width/2, p.y+game_height/2);
    tex.draw(shape);*/
  }

  void drawBall(sf::RenderTexture& tex, const Ball& ball) {
    sf::CircleShape shape(ball.radius);
    shape.setPosition(ball.pos.x + game_width / 2,
                      ball.pos.y + game_height / 2);
    shape.setFillColor(sf::Color::White);
    tex.draw(shape);
  }
};

#endif
