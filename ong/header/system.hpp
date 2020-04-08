#ifndef TORTUGA_SYSTEM_HPP
#define TORTUGA_SYSTEM_HPP

#include <TE/ecs/ecs.hpp>
#include "components.hpp"

#include <string>

using namespace ta;

class OngPlayerSystem : public AbstractSystem<CPosition, COngPlayer> {
private:
    const string name = "OngPlayerSystem";

public:
    OngPlayerSystem() {}

    void update(const Time& time, EntityId entityId) override;

    void handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) override;

    const string& getName() override;
};

//
//
class OngCollisionSystem : public AbstractSystem<CPosition, COngBall> {
private:
    const string name = "OngCollisionSystem";
    const EntityId playerOneId;
    const EntityId playerTwoId;
    COngPlayer* p1;
    COngPlayer* p2;

public:
    OngCollisionSystem(EntityId playerOneId, EntityId playerTwoId) : playerOneId(playerOneId), playerTwoId(playerTwoId) {}

    void preUpdate(const Time& time) override;

    void update(const Time& time, EntityId entityId) override;

    void handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) override;

    const string& getName() override;

private:
    static bool ballCollideWithPaddle(CPosition* ballPos, COngPlayer* player);

    static bool collideWithArc(CPosition* ballPos, COngPlayer* player);
};


//
//
class KineticSystem : public AbstractSystem<CPosition, CKinetic> {
private:
    const string name = "KineticSystem";

public:
    void update(const Time& time, EntityId entityId) override;

    void handleEvent(const sf::Time& time, EntityId target, ECSMessage msg) override;

    const string& getName() override;
};

#endif //TORTUGA_SYSTEM_HPP