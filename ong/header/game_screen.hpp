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


class GameScreen : public Screen {
private:
    // screen private draw target
    sf::RenderTexture renderTexture;

    EntityManager* entityManager;
    SystemManager* systemManager;

    EntityId playerOneId;
    EntityId playerTwoId;
    EntityId ballId;

    EntityId controlledPlayer = playerOneId;

public:
    GameScreen() {
        if (!renderTexture.create(200, 200)) { /* TODO check error */ }

        this->systemManager = new SystemManager();
        this->entityManager = new EntityManager(this->systemManager);

        playerOneId = createPlayer(players::p1);
        controlledPlayer = playerOneId;
        playerTwoId = createPlayer(players::p2);
        ballId = createBall();

        this->systemManager->addSystem(new OngPlayerSystem());
        this->systemManager->addSystem(new OngCollisionSystem(playerOneId, playerTwoId));
        this->systemManager->addSystem(new KineticSystem());

    }

    void update(const sf::Time& time) override {
        systemManager->update(time);
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Key::Left) {
                ECSMessage msg = ECSMessage(MSG_PLAYER_MOVE_LEFT);
                this->systemManager->sendMessage(controlledPlayer, msg);
            }
            else if(event.key.code == sf::Keyboard::Key::Right) {
                ECSMessage msg = ECSMessage(MSG_PLAYER_MOVE_RIGHT);
                this->systemManager->sendMessage(controlledPlayer, msg);
            }
            else if(event.key.code == sf::Keyboard::Key::LShift) {
                controlledPlayer = (controlledPlayer == playerOneId) ? playerTwoId : playerOneId;
            }
            else if (event.key.code == sf::Keyboard::Key::Space) {
                /*if (!logic->isRoundActive()) {
                    logic->setRoundActive(true);;
                    logic->resetBall();
                } else {
                    logic->resetBall();
                }*/
            }
        }
        return false;
    }

    /**
     * @brief  Render the game Screen in the rendering target
     * @param  target: rendering target
     */
    void render(sf::RenderTexture& target) override {
        renderTexture.clear();

        this->systemManager->render(renderTexture);

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
        CRenderer* prendered = new CRenderer([](const CPosition& p, sf::RenderTexture& renderTex) {
            sf::CircleShape c(3);
            c.setFillColor(sf::Color::Red);
            c.setPosition(p.position.x + game_width / 2, p.position.y + game_height / 2);
            renderTex.draw(c);
            /*p = getPointOnArc(player.angle - player.paddle_half_arc, arena_radius);
            c.setPosition(p.position.x + game_width / 2, p.position.y + game_height / 2);
            renderTex.draw(c);

            p = getPointOnArc(player.angle + player.paddle_half_arc, arena_radius);
            c.setPosition(p.position.x + game_width / 2, p.position.y + game_height / 2);
            renderTex.draw(c);*/
        });
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
        CKinetic* bkinetic = new CKinetic(-1, 0, default_ball_speed);
        CHitbox* bhitbox = new CHitbox();
        CRenderer* brendered = new CRenderer([](const CPosition& p, sf::RenderTexture& renderTex) {
            sf::CircleShape shape(default_ball_radius);
            shape.setPosition(p.position.x + game_width / 2, p.position.y + game_height / 2);
            shape.setFillColor(sf::Color::Red);
            renderTex.draw(shape);
        });

        entityManager->addComponent(id, bball);
        entityManager->addComponent(id, bposition);
        entityManager->addComponent(id, bkinetic);
        entityManager->addComponent(id, bhitbox);
        entityManager->addComponent(id, brendered);

        return id;
    }
};

#endif
