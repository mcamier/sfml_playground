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
#include "header.hpp"
#include "components.hpp"
#include "system.hpp"
#include "TE/ecs/ecs.hpp"

#include "TE/message/message.hpp"

using namespace std;
using namespace ta;

const messageType PLAYER_MOVE = 1;
const messageType BALL_LOST = 2;
const messageType BALL_COLLIDE = 2;

class GameScreen : public Screen {
private:
    // screen private draw target
    sf::RenderTexture renderTexture;

    EntityManager* entityManager;
    SystemManager* systemManager;

    EntityId playerOneId;
    EntityId playerTwoId;
    EntityId ballId;

public:
    GameScreen() {
        if (!renderTexture.create(200, 200)) { /* TODO check error */ }

        this->systemManager = new SystemManager();
        this->entityManager = new EntityManager(this->systemManager);

        playerOneId = createPlayer(players::p1);
        playerTwoId = createPlayer(players::p2);
        ballId = createBall();

        this->systemManager->addSystem(new CollisionSystem(playerOneId, playerTwoId));
        this->systemManager->addSystem(new KineticSystem());
    }

    void update(const sf::Time& time) override {
        systemManager->update(time);
    }

    bool handleEvent(const sf::Event& event) override {
        /*if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Key::Space) {
            if (!logic->isRoundActive()) {
                logic->setRoundActive(true);;
                logic->resetBall();
            } else {
                logic->resetBall();
            }
        } else if (event.type == sf::Event::KeyPressed &&
                   event.key.code == sf::Keyboard::Key::LShift) {
            logic->switchControlledPlayer();
        }*/

        return false;
    }

    /**
     * @brief  Render the game Screen in the rendering target
     * @param  target: rendering target
     */
    void render(sf::RenderTexture& target) override {
        renderTexture.clear();

        //this->renderer->render(renderTexture);

        renderTexture.display();

        sf::Sprite sprite(renderTexture.getTexture());

        sf::Transform transform;
        transform.scale(4, 4);
        target.draw(sprite, sf::RenderStates(transform));
    }

private:
    EntityId createPlayer(players playerId) {
        EntityId id = entityManager->addEntity();

        COngPlayer* pplayer = new COngPlayer(playerId);
        CPosition* pposition = new CPosition();
        CRenderer* prendered = new CRenderer();
        CHitbox* phitbox = new CHitbox();

        entityManager->addComponent(id, pplayer);
        entityManager->addComponent(id, pposition);
        entityManager->addComponent(id, prendered);
        entityManager->addComponent(id, phitbox);

        return id;
    }

    EntityId createBall() {
        EntityId id = entityManager->addEntity();

        COngBall* bball = new COngBall();
        CPosition* bposition = new CPosition(0, 20);
        CKinetic* bkinetic = new CKinetic(0, -1, default_ball_speed);
        CHitbox* bhitbox = new CHitbox();
        CRenderer* brendered = new CRenderer();

        entityManager->addComponent(id, bball);
        entityManager->addComponent(id, bposition);
        entityManager->addComponent(id, bkinetic);
        entityManager->addComponent(id, bhitbox);
        entityManager->addComponent(id, brendered);

        return id;
    }
};



class GameLogic : public IUpdatable {

private:
    bool round_active = false;
    int collision_count = 0;
    int ball_count = 1;
    players controllable_player = players::p1;

    Subscription subBallLost;
    Subscription subPlayerWin;
    Subscription subPlayerCollideBall;

public:
    GameLogic() {
        // todo
        void* bytes;
        long size;
        ResourceService::get().getResource(ResourceManifest::FONT, &bytes, &size);
        ResourceService::get().getResource(ResourceManifest::BOOM, &bytes, &size);

        /*subBallLost = MessageService::get().subscribe(MSG_BALL_LOST, &GameLogic::onBallLost, this);
        subPlayerWin = MessageService::get().subscribe(MSG_PLAYER_WIN, &GameLogic::onPlayerWin, this);
        subPlayerCollideBall = MessageService::get().subscribe(MSG_PLAYER_COLLIDE_BALL,
                                                               &GameLogic::onPlayerCollidesBall, this);*/
    }

    void update(const Time& time) override {
        /*float elapsedSec = time.asSeconds();

        if (!round_active) {
            return;
        }

        // update each ball consecutively
        for (int i = 0; i < ball_count; i++) {
            // move ball
            /////////////////////////////////////////////////Ball& ball = balls[0];
            /////////////////////////////////////////////////float ballSpeed = ball.speed * (1 + (0.15f * collision_count));
            /////////////////////////////////////////////////ball.pos_dest.x = ball.pos.x + (ball.vector.x * elapsedSec * ballSpeed);
            /////////////////////////////////////////////////ball.pos_dest.y = ball.pos.y + (ball.vector.y * elapsedSec * ballSpeed);

            if (ballLost(ball)) {
                message msg;
                msg.type = MSG_BALL_LOST;
                msg.v1.type = variant::type_t::INT_T;
                msg.v1.intValue = i;
                MessageService::get().sendMessage(msg);
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
                MessageService::get().sendMessage(msg);
            } else if (ball.last_hit_by != players::p2 &&
                       ballCollideWithPaddle(ball, p2, collision_response)) {
                collision_count++;
                ball.last_hit_by = players::p2;
                ball.vector = collision_response;
                ball.resetDest();

                message msg;
                msg.type = MSG_PLAYER_COLLIDE_BALL;
                MessageService::get().sendMessage(msg);
            } else {
                ball.setDestAsNewPos();
            }
        }

        Player* controlled_player = (controllable_player == players::p1) ? &p1 : &p2;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            controlled_player->angle -= elapsedSec * default_player_speed;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            controlled_player->angle += elapsedSec * default_player_speed;
        }
        controlled_player->clampAngle();*/
    };

    /*void resetBall() {
        this->ball_count = 1;
        this->balls[0] = Ball(0, 20);
        this->balls[0].vector = angleToVec(180);
    }*/

    /*bool ballLost(Ball& ball) {
        return isOutsideCircle(ball.pos_dest.x, ball.pos_dest.y, arena_defeat_radius);
    }*/

    /*bool ballCollideWithPaddle(const Ball& ball, const Player& player,
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
    }*/

    /*void switchControlledPlayer() {
        controllable_player = (controllable_player == players::p1) ? players::p2 : players::p1;
    }*/

    /*bool collideWithArc(const Ball& ball, const Player& player) {
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
    }*/

    /*void onBallLost(message msg) {
        int ballIdx = msg.getVar1<int>();
        collision_count = 0;
        resetBall();
        // update scores
        // TODO reference to game obj
        if (balls[ballIdx].last_hit_by == players::p1) {
            p1.score++;
        } else if (balls[ballIdx].last_hit_by == players::p2) {
            p2.score++;
        }
    }*/
};


/* void drawPlayer(sf::RenderTexture& tex, const Player& player) {
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
 */

#endif
