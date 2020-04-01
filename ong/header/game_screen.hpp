#ifndef FOOBAR_GAMESCREEN_HPP
#define FOOBAR_GAMESCREEN_HPP

#include <iostream>

#include "manifest.hpp"
#include "math.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "TE/math/math.hpp"
#include "TE/message/message.hpp"
#include "TE/message/message_service.hpp"
#include "TE/message/subscription.hpp"
#include "TE/resource/resource_service.hpp"
#include "TE/screen/Screen.hpp"
#include "TE/core/ServiceLocator.hpp"
#include "ball.hpp"
#include "header.hpp"
#include "player.hpp"

using namespace std;
using namespace ta;

class GameScreen : public Screen {
private:
    // all Screen
    bool isLoaded = false;
    // pong game Screen
    sf::Font font;
    bool round_active = false;

    Player p1 = Player(players::p1);
    Player p2 = Player(players::p2);
    Ball balls[ball_count_max];
    int collision_count = 0;
    int ball_count = 1;
    players controllable_player = players::p1;

    Subscription subBallLost;
    Subscription subPlayerWin;
    Subscription subPlayerCollideBall;

public:
    GameScreen() {
        this->transitionDurationSec = 0.0f;
        balls[0] = Ball(0, 20);
        // todo
        const char* bytes;
        long size;
        GetResourceService()->get(ResourceManifest::FONT, &bytes, &size);
        GetResourceService()->get(ResourceManifest::BOOM, &bytes, &size);

        subBallLost = GetMessageService()->subscribe(
                MSG_BALL_LOST, &GameScreen::onBallLost, this);

        subPlayerWin = GetMessageService()->subscribe(
                MSG_PLAYER_WIN, &GameScreen::onPlayerWin, this);

        subPlayerCollideBall = GetMessageService()->subscribe(
                MSG_PLAYER_COLLIDE_BALL, &GameScreen::onPlayerCollidesBall, this);
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
     * @brief  Update the Game Screen
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
                message msg;
                msg.type = MSG_BALL_LOST;
                msg.v0.type = variant::type_t::INT_T;
                msg.v0.intValue = i;
                GetMessageService()->sendMessage(msg);
            }

            vec2f collision_response;
            if (ball.last_hit_by != players::p1 &&
                ballCollideWithPaddle(ball, p1, collision_response)) {
                collision_count++;
                ball.last_hit_by = players::p1;
                ball.vector = collision_response;
                // put the ball in the last non-colliding position
                ball.resetDest();

                message msg;
                msg.type = MSG_PLAYER_COLLIDE_BALL;
                GetMessageService()->sendMessage(msg);
            } else if (ball.last_hit_by != players::p2 &&
                       ballCollideWithPaddle(ball, p2, collision_response)) {
                collision_count++;
                ball.last_hit_by = players::p2;
                ball.vector = collision_response;
                ball.resetDest();

                message msg;
                msg.type = MSG_PLAYER_COLLIDE_BALL;
                GetMessageService()->sendMessage(msg);
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
     * @brief  Render the game Screen in the rendering target
     * @param  target: rendering target
     */
    void render(sf::RenderTexture& target) override {
        drawDebug(target);
        drawPlayer(target, p1);
        drawPlayer(target, p2);
        drawBall(target, balls[0]);
    }

private:
    void onPlayerCollidesBall(message msg) {
        cout << "player collides with ball" << endl;
    }

    void onBallLost(message msg) {
        int ballIdx = msg.v0.intValue;
        collision_count = 0;
        resetBall();
        // update scores
        // TODO reference to game obj
        if (balls[ballIdx].last_hit_by == players::p1) {
            p1.score++;
        } else if (balls[ballIdx].last_hit_by == players::p2) {
            p2.score++;
        }
    }

    void onPlayerWin(message msg) { cout << "player win" << endl; }

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
        vec2f p = getPointOnArc(player.angle, arena_radius);
        sf::Color color;
        if (player.player_id == players::p1) {
            color = sf::Color::Red;
        } else {
            color = sf::Color::Blue;
        }

        sf::CircleShape c(3);
        c.setFillColor(color);
        c.setPosition(p.x + game_width / 2, p.y + game_height / 2);
        tex.draw(c);

        p = getPointOnArc(player.angle - player.paddle_half_arc, arena_radius);
        c.setPosition(p.x + game_width / 2, p.y + game_height / 2);
        tex.draw(c);

        p = getPointOnArc(player.angle + player.paddle_half_arc, arena_radius);
        c.setPosition(p.x + game_width / 2, p.y + game_height / 2);
        tex.draw(c);
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
