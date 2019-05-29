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
            srand((unsigned) elapsedSec);
        }
        else if (round_active && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            resetBall();
        }

        if (round_active) {
            // move the ball
            float ballSpeed = Ball::speed*(1+(0.15f*collision_count));
            ball.pos_dest.x = ball.pos.x+(ball.vector.x*elapsedSec*ballSpeed);
            ball.pos_dest.y = ball.pos.y+(ball.vector.y*elapsedSec*ballSpeed);

            if (ballLost(ball)) {
                collision_count = 0;
                resetBall();
                // resetPaddles();

                // update score
                if (last_hit_by==players_enum::p1) {
                    p1.score++;
                }
                else if (last_hit_by==players_enum::p2) {
                    p2.score++;
                }
            }
            if (ballCollideWithPaddle(ball, p1)) {
                collision_count++;
                ball.vector.x = -ball.vector.x;
                ball.vector.y = -ball.vector.y;
                ball.resetDest();
            }
                //else if (ballCollideWithPaddle(ball, p2)) {}
            else {
                ball.setDestAsNewPos();
            }

            // player 1 move handling
            int speed = Player::speed;
            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) {
                speed = Player::low_speed;
            }*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                p1.angle -= elapsedSec*speed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                p1.angle += elapsedSec*speed;
            }

            if (p1.angle>=360) {
                p1.angle = (int) p1.angle%360;
            }
            else if (p1.angle<0) {
                p1.angle = 360+p1.angle;
            }
        }
    }

    void resetBall()
    {
        this->ball = Ball(0, 0);
        this->ball.vector = angleToVec(180);
    }

    bool ballLost(Ball& ball)
    {
        return isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_defeat_radius);
    }

    bool isOutsideCircle(float x, float y, float radius)
    {
        return ((x*x)+(y*y))>square(radius);
    }

    bool isInsideCircle(float x, float y, float radius)
    {
        return ((x*x)+(y*y))<=square(radius);
    }

    bool ballCollideWithPaddle(Ball& ball, Player& player)
    {
        if (isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_radius-Ball::radius) &&
                isInsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_radius)) {
            if (collideWithArc(ball, player)) {
                return true;
            }
        }
        return false;
    }

    bool collideWithArc(Ball& ball, Player& player)
    {
        float phi, min, max;
        phi = min = max = .0f;

        vec2 p(ball.pos_dest.x, ball.pos_dest.y);
        p.normalize();
        p.y = -p.y;
        phi = vectorToDegrees(p);

        int half_angle = player.paddle_arc/2;
        min = player.angle-half_angle;
        max = player.angle+half_angle;

        bool res = phi>=min && phi<=max;
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

        std::string str = "player 1: "+std::to_string(p1.angle);
        std::cout << str << std::endl;
    }

private:
    void drawPlayer(sf::RenderTexture& tex, Player& player)
    {
        static float cos_half_pi = -0.999624217;
        static float sin_half_pi = -0.027412134;
        int segment_count = 3;
        float segment_arc_angle = (float) player.paddle_arc / segment_count;
        float segment_length = toRad(segment_arc_angle) * arena_radius;
        int min_angle = player.angle - player.paddle_arc/2;

        sf::RectangleShape rect(sf::Vector2f(segment_length, 4));
        rect.setFillColor(sf::Color::Red);

        for(int i = 0; i<segment_count; i++) {
            float angle = min_angle+i*segment_arc_angle;
            vec2 p = getPointOnArc(angle, arena_radius);

            vec2 v=angleToVec(angle);
            //v.x = -v.x;
            //v.y = -v.y;
            v.x = -v.x*cos_half_pi + v.y*sin_half_pi;
            v.y = -v.x*sin_half_pi - v.y*cos_half_pi;

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
        shape.setPosition(pos.x+game_width/2, pos.y+game_height/2);
        shape.setFillColor(sf::Color::White);
        tex.draw(shape);
    }
};

#endif
