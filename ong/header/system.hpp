#ifndef TORTUGA_SYSTEM_HPP
#define TORTUGA_SYSTEM_HPP

#include <TE/ecs/ecs.hpp>
#include "components.hpp"

#include <string>

using namespace ta;

//
//
class CollisionSystem : public AbstractSystem<CPosition, COngBall> {
private:
    const string name = "CollisionSystem";
    const EntityId playerOneId;
    const EntityId playerTwoId;
    COngPlayer* p1;
    COngPlayer* p2;

public:
    CollisionSystem(EntityId playerOneId, EntityId playerTwoId) : playerOneId(playerOneId), playerTwoId(playerTwoId) {}

    void preUpdate(const Time& time) override;

    void update(const Time& time, EntityId entityId) override;

    const string& getName() override;

private:
    bool ballCollideWithPaddle(CPosition* ballPos, COngPlayer* player);

    bool collideWithArc(CPosition* ballPos, COngPlayer* player);
};


//
//
class KineticSystem : public AbstractSystem<CPosition, CKinetic> {
private:
    const string name = "KineticSystem";

public:
    void update(const Time& time, EntityId entityId) override;

    const string& getName() override;
};



#endif //TORTUGA_SYSTEM_HPP