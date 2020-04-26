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
#include "TE/input/InputService.hpp"
#include "TE/message/message_service.hpp"
#include "TE/message/subscription.hpp"
#include "TE/resource/resource_service.hpp"
#include "TE/screen/Screen.hpp"
#include "TE/physics/physics.hpp"
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
    sf::Font font;
    sf::RenderTexture renderTexture;

    EntityManager* entityManager;
    SystemManager* systemManager;
    EntityId id;
    EntityId id3;
    EntityId id2;
    vec3f anchorPosition = vec3f(0,0,0);

public:
    GameScreen() {
        std::function<void(const CPosition&, sf::RenderTexture&)> drawCallback = [](const CPosition& p, sf::RenderTexture& renderTex) {
            sf::CircleShape shape(default_ball_radius);
            shape.setPosition(p.position.x + game_width / 2, -p.position.y + game_height / 2);
            shape.setFillColor(sf::Color::Blue);
            renderTex.draw(shape);
        };

        std::function<void(const CPosition&, sf::RenderTexture&)> drawCallback2 = [](const CPosition& p, sf::RenderTexture& renderTex) {
            sf::CircleShape shape(default_ball_radius);
            shape.setPosition(p.position.x + game_width / 2, -p.position.y + game_height / 2);
            shape.setFillColor(sf::Color::Yellow);
            renderTex.draw(shape);
        };

        if (!renderTexture.create(800, 800)) { /* TODO check error */ }

        this->systemManager = new SystemManager();
        this->entityManager = new EntityManager(this->systemManager);
        BasicPhysicSystem* physicSystem = new BasicPhysicSystem();
        this->systemManager->addSystem(physicSystem);

        id = entityManager->addEntity();
        entityManager->addComponent(id, new CPosition(50, -90));
        entityManager->addComponent(id, new CParticule(5));
        entityManager->addComponent(id, new CRenderer(drawCallback));
        physicSystem->addGenerator(id, new AnchoredSpringForceGenerator(anchorPosition, 15.f, 200.f));
        physicSystem->addGenerator(id, new GravityForceGenerator(vec3f(0.0f, -100.0f, 0.0f)));

        id2 = entityManager->addEntity();
        entityManager->addComponent(id2, new CPosition(100, -90));
        entityManager->addComponent(id2, new CParticule(5));
        entityManager->addComponent(id2, new CRenderer(drawCallback2));
        physicSystem->addGenerator(id2, new GravityForceGenerator(vec3f(0.0f, -100.0f, 0.0f)));

        EntityId anchorId = entityManager->addEntity();;
        entityManager->addComponent(anchorId, new CPosition(anchorPosition.x, anchorPosition.y));
        entityManager->addComponent(anchorId, new CRenderer(drawCallback2));

        //InputService::get().mapCallback(MSG_PLAYER_MOVE_LEFT, [this]() { moveActivePlayerLeft(); });
        //InputService::get().mapCallback(MSG_PLAYER_MOVE_RIGHT, [this]() { moveActivePlayerRight(); });
        //InputService::get().mapCallback(MSG_CHANGE_ACTIVE_PLAYER, [this]() { changeActivePlayer(); });

        setInputCallback(MSG_PLAYER_MOVE_LEFT);
    }

    void update(const sf::Time& time) override {
        systemManager->update(time);
    }

    bool handleEvent(const sf::Event& event) override {
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

        auto* pos = entityManager->getComponent<CPosition>(id);
        auto* physic = entityManager->getComponent<CParticule>(id);

        REP_DEBUG("position \t" << pos->position.x << " ; " << pos->position.y, LogChannelFlag::ON_SCREEN)
        REP_DEBUG("velocity \t" << physic->velocity.x << " ; " << physic->velocity.y, LogChannelFlag::ON_SCREEN)
        REP_DEBUG("acceleration " << physic->acceleration.x << " ; " << physic->acceleration.y, LogChannelFlag::ON_SCREEN)

        // draw lines
        int linesAmount = 50;
        sf::VertexArray lines(sf::Lines, 2 * linesAmount);
        for(int i = 0; i < linesAmount ; i++) {
            lines[2*i].position = sf::Vector2f(-4000, 50 * i);
            lines[2*i].color = sf::Color(75, 75, 75, 255);
            lines[2*i+1].position = sf::Vector2f(4000, 50 * i);
            lines[2*i+1].color = sf::Color(75, 75, 75, 255);
        }
        renderTexture.draw(lines);


        sf::Sprite sprite(renderTexture.getTexture());
        target.draw(sprite);
    }

    void moveActivePlayerLeft() {

    }

    void moveActivePlayerRight() {

    }

    void changeActivePlayer() {

    }

};

#endif
