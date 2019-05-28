#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

#include "math.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "player.hpp"
#include "../utils/screen/screen.hpp"
#include "../utils/math/math.hpp"
#include "ball.hpp"
#include "../pong/game_screen.hpp"

enum players_enum {
  p1, p2
};

enum game_mode {
  one_player_vs_ai,
  one_player,
  two_players
};

class GameScreen : public Screen {

private:
    // all screen
    bool isLoaded = false;

    // pong game screen
    sf::Font font;

    const int game_width = 200;
    const int game_height = 200;
    const int arena_radius = 75;
    const int arena_defeat_radius = 100;
    bool round_active = false;

    Player p1, p2;
    Ball ball;
    players_enum last_hit_by = players_enum::p2;
    int collision_count = 0;
    int ball_count = 1;
    const int ball_count_max = 3;

public:
    GameScreen()
    {
        this->transitionDurationSec = 0.0f;
        p1 = Player(180);
        p2 = Player(0);
        ball = Ball(0, 0);
    }

    bool load()
    {
        if (!font.loadFromFile("PressStart2P.ttf")) {
            this->isLoaded = false;
            return false;
        }

        ball = Ball(game_width/2-5, game_height/2-25);
        this->isLoaded = true;

        return this->isLoaded;
    }

    void update(const sf::Time& time) override
    {
        float elapsedSec = time.asSeconds();

        // Start the round is not already started when the player push the space bar
        if (!round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            round_active = true;
            ball.vector = angleToVec(180);
            srand((unsigned)elapsedSec);
        } else if (round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            resetBall();
        }

        if (round_active) {
            // move the ball
            float ballSpeed = Ball::speed*(1+(0.15f*collision_count));
            ball.pos_dest.x = ball.pos.x+(ball.vector.x*elapsedSec*ballSpeed);
            ball.pos_dest.y = ball.pos.y+(ball.vector.y*elapsedSec*ballSpeed);

            if(ballLost(ball)) {
                resetBall();
                // resetPaddles();

                // update score
                if(last_hit_by == players_enum::p1) {
                    p1.score++;
                } else if(last_hit_by == players_enum::p2){
                    p2.score++;
                }
            }
            if (ballCollideWithPaddle(ball, p1)) {
                // apply ball new position
                // update ball vector
                std::cout << "ball collide" << std::endl;
                ball.vector.x = -ball.vector.x;
                ball.vector.y = -ball.vector.y;
                ball.resetDest();
            }
            //else if (ballCollideWithPaddle(ball, p2)) {}
            else {
                // no collision, allow the move
                ball.setDestAsNewPos();
            }

            // player 1 move handling
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                p1.angle -= elapsedSec*Player::speed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                p1.angle += elapsedSec*Player::speed;
            }

            float decimal = p1.angle-(int) p1.angle;
            if (p1.angle>=360) {
                p1.angle = (int) p1.angle%360;  
                p1.angle += decimal;
            }
        }
    }

    void resetBall() {
        this->ball = Ball(0, 0);
        int start_angle = rand() % 360;
        this->ball.vector = angleToVec(start_angle);
    }

    bool ballLost(Ball& ball)
    {
        return isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y, 0, 0, arena_defeat_radius);
    }

    bool isOutsideCircle(float x, float y, float circle_x, float circle_y, float radius)
    {
        float delta_x = x - circle_x;
        float delta_y = y - circle_y;
        return (square(delta_x) + square(delta_y)) > square(radius);
    }

    bool ballCollideWithPaddle(Ball& ball, Player& player)
    {
        if(isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y, 0, 0, arena_radius - Ball::radius)) {
            if (collideWithArc(ball, player)) {
                return true;
            }
        }
        return false;
    }

    bool collideWithArc(Ball& ball, Player& player) {
        float phi, min, max;
        phi = min = max = .0f;

        vec2 p (ball.pos_dest.x, ball.pos_dest.y);
        p.normalize();
        p.y = -p.y;
        phi = vectorToDegrees(p);

        float arc_half_angle = toDeg(player.paddle_length / arena_radius) / 2;
        min = player.angle - arc_half_angle;
        max = player.angle + arc_half_angle;

        bool res = phi >= min && phi <= max;
        return res;
    }

    bool handleEvent(const sf::Event& event) override
    {
        return false;
    }

    void render(sf::RenderTexture& target) override
    {
        sf::RectangleShape vline(sf::Vector2f(1.f, game_height));
        vline.setPosition(game_width/2, 0);
        vline.setFillColor(sf::Color::Magenta);
        sf::RectangleShape hline(sf::Vector2f(game_width, 1.f));
        hline.setPosition(0, game_height/2);
        hline.setFillColor(sf::Color::Magenta);
        target.draw(vline);
        target.draw(hline);

        drawBall(target, ball.pos);
        drawPlayer(target, p1);
        
        std::string str = "player 1: " + std::to_string(p1.angle);
        std::cout << str << std::endl;
    }

private:
    void drawPlayer(sf::RenderTexture& tex, Player& player)
    {
        sf::CircleShape shape(3);
        shape.setFillColor(sf::Color::White);

        vec2 p = getPointOnArc(player.angle, arena_radius);
        shape.setPosition(p.x + game_width/2, p.y + game_height/2);
        tex.draw(shape);
    }

    vec2 getPointOnArc(float angle, float radius)
    {
        vec2 v = angleToVec(angle);
        v.y = -v.y;
        v.scale(radius);
        return v;
    }

    void drawBall(sf::RenderTexture& tex, vec2& pos)
    {
        sf::CircleShape shape(Ball::radius);
        shape.setPosition(pos.x + game_width / 2, pos.y + game_height / 2);
        shape.setFillColor(sf::Color::White);
        tex.draw(shape);
    }
};

#endif
