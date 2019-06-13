#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "TE/screen/screen.hpp"
#include "ball.hpp"
#include "pause_screen.hpp"
#include "player.hpp"

using namespace ta;

class GameScreen : public Screen {
 private:
  // all screen
  bool isLoaded = false;

  // pong game screen
  sf::Font font;
  const int paddle_p1_x_axis = 50;
  const int paddle_p2_x_axis = 750;

  const int game_width = 800;
  const int game_height = 600;
  bool round_active = false;
  int collisionCount = 0;
  Player p1;
  Player p2;
  Ball ball;
  PauseScreen* pause_screen;
  sf::SoundBuffer hit_sound_buffer;
  sf::SoundBuffer boom_sound_buffer;
  sf::Sound hit_sound;
  sf::Sound boom_sound;

 public:
  GameScreen() { this->transitionDurationSec = 0.0f; }

  bool load() {
    if (!font.loadFromFile("PressStart2P.ttf")) {
      this->isLoaded = false;
      return false;
    }
    if (!hit_sound_buffer.loadFromFile("hit.wav")) {
      this->isLoaded = false;
      return false;
    }
    hit_sound.setBuffer(hit_sound_buffer);

    if (!boom_sound_buffer.loadFromFile("boom.wav")) {
      this->isLoaded = false;
      return false;
    }
    boom_sound.setBuffer(boom_sound_buffer);

    p1 = Player(paddle_p1_x_axis, game_height / 2);
    p2 = Player(paddle_p2_x_axis, game_height / 2);
    ball = Ball(game_width / 2, game_height / 2);
    this->isLoaded = true;

    pause_screen = new PauseScreen();
    pause_screen->load();

    return this->isLoaded;
  }

  void update(const sf::Time& time) override {
    if (!isActive()) return;

    float elapsedSec = time.asSeconds();
    // Start the round is not already started when the player push the space bar
    if (!round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      round_active = true;
      ball.vector = angleToVec(160);
    } else if (round_active &&
               sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      ball.pos = vec2f(game_width / 2, game_height / 2);
      ball.pos_dest = ball.pos;
      ball.vector = angleToVec(160);
    }

    if (round_active) {
      // player 1 move handling
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        p1.pos_dest.y -= elapsedSec * Player::speed;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        p1.pos_dest.y += elapsedSec * Player::speed;
      }

      // Move the ball if round active
      if (round_active) {
        float ballSpeed = Ball::speed * (1 + (0.2 * collisionCount));
        ball.pos_dest.x = ball.pos.x + (ball.vector.x * elapsedSec * ballSpeed);
        ball.pos_dest.y = ball.pos.y + (ball.vector.y * elapsedSec * ballSpeed);
      }

      if (isMoveAllowed(p1.pos_dest)) {
        p1.setDestAsNewPos();
      } else {
        p1.resetDest();
      }

      // player 2 AI
      bool isBallComingToP2 = (ball.vector.x > 0);
      if (!isBallComingToP2) {
        // go back to the center of the screen, then idle
        if (p2.pos.y < (game_height / 2)) {
          p2.pos_dest.y += elapsedSec * Player::speed;
        } else if (p2.pos.y > (game_height / 2)) {
          p2.pos_dest.y -= elapsedSec * Player::speed;
        }
      } else {
        // dummy follow the ball
        if (ball.pos.y > p2.pos.y && ball.vector.y >= 0) {
          p2.pos_dest.y += elapsedSec * Player::speed;
        } else if (ball.pos.y < p2.pos.y && ball.vector.y <= 0) {
          p2.pos_dest.y -= elapsedSec * Player::speed;
        }
      }
      if (isMoveAllowed(p2.pos_dest)) {
        p2.setDestAsNewPos();
      } else {
        p2.resetDest();
      }

      // handle ball collision
      bool collideWithTop = ball.pos_dest.y < 0;
      bool collideWithBottom = ball.pos_dest.y + Ball::height > game_height;
      bool collideWithLeftGoal = ball.pos_dest.x < 0;
      bool collideWithRightGoal = ball.pos_dest.x + Ball::width > game_width;
      // collide with players
      if (ballCollideWithPlayer(ball, p1) || ballCollideWithPlayer(ball, p2)) {
        // should compute the exact place where the ball meet the paddle
        // otherwise bad thing could happens if time elapsed between 2 frames is
        // too big
        hit_sound.play();
        ball.resetDest();
        ball.vector.x = -ball.vector.x;
        collisionCount++;
      }
      // collide with top and bottom  border
      if (collideWithTop || collideWithBottom) {
        hit_sound.play();
        ball.resetDest();
        ball.vector.y = -ball.vector.y;
      } else {
        ball.setDestAsNewPos();
      }
      // collide with goals
      if (collideWithLeftGoal) {
        resetBallAndPlayersPosition(ball, p1, p2);
        p2.score++;
        collisionCount = 0;
        round_active = false;
        boom_sound.play();
      } else if (collideWithRightGoal) {
        resetBallAndPlayersPosition(ball, p1, p2);
        p1.score++;
        collisionCount = 0;
        round_active = false;
        boom_sound.play();
      }
    }
  }

  bool handleEvent(const sf::Event& event) override {
    if ((event.type == sf::Event::EventType::KeyPressed) &&
        (event.key.code == sf::Keyboard::Key::Escape)) {
      getOwner().addScreen(static_cast<Screen*>(pause_screen));
    }

    return false;
  }

  void render(sf::RenderTexture& target) override {
    drawPlayer(target, p1.pos);
    drawPlayer(target, p2.pos);
    drawBall(target, ball.pos);
    drawMiddleLine(target);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    if (!round_active) {
      text.setString("Press Space bar to begin !");
      target.draw(text);
    }

    text.setString(std::to_string(p1.score));
    text.setPosition((game_width / 2) - 30, 20);
    target.draw(text);

    text.setString(std::to_string(p2.score));
    text.setPosition((game_width / 2) + 30, 20);
    target.draw(text);
  }

 private:
  void resetBallAndPlayersPosition(Ball& ball, Player& player1,
                                   Player& player2) {
    player1.pos = vec2f(paddle_p1_x_axis, game_height / 2);
    player1.pos_dest = player1.pos;
    player2.pos = vec2f(paddle_p2_x_axis, game_height / 2);
    player2.pos_dest = player2.pos;
    ball = Ball(game_width / 2, game_height / 2);
  }

  bool ballCollideWithPlayer(Ball& ball, Player& player) {
    if (((ball.pos_dest.x > player.pos_dest.x) &&
         (ball.pos_dest.x < (player.pos_dest.x + Player::width))) ||
        (((ball.pos_dest.x + Ball::width) > player.pos_dest.x) &&
         ((ball.pos_dest.x + Ball::width) <
          (player.pos_dest.x + Player::width)))) {
      return !(ball.pos_dest.y + Ball::height < player.pos_dest.y ||
               ball.pos_dest.y > (player.pos_dest.y + Player::height));
    }
    return false;
  }

  bool isMoveAllowed(vec2f& paddle_pos) {
    vec2f area(game_width, game_height);
    vec2f paddle_right_corner(paddle_pos.x + Player::width,
                              paddle_pos.y + Player::height);

    return isInside(paddle_pos, area) && isInside(paddle_right_corner, area);
  }

  bool isInside(vec2f& pos, vec2f& area) {
    return !(pos.x < 0 || pos.y < 0 || pos.x > area.x || pos.y > area.y);
  }

  void drawPlayer(sf::RenderTexture& tex, vec2f& pos) {
    sf::RectangleShape shape(sf::Vector2f(Player::width, Player::height));
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(sf::Color::White);

    tex.draw(shape);
  }

  void drawMiddleLine(sf::RenderTexture& tex) {
    sf::RectangleShape shape(sf::Vector2f(2, game_height));
    shape.setPosition(game_width / 2, 0);
    shape.setFillColor(sf::Color::White);

    tex.draw(shape);
  }

  void drawBall(sf::RenderTexture& tex, vec2f& pos) {
    sf::CircleShape shape(Ball::width / 2);
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(sf::Color::White);

    tex.draw(shape);
  }
};

#endif
