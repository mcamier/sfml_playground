#include "../../inc/TE/ecs/system.hpp"

#include <iostream>

#include "../../inc/TE/ecs/entity.hpp"
#include "../../inc/TE/logger.hpp"
#include "../../inc/TE/log_utils.hpp"

namespace ta {

using utils::LogChannelFlag;

//
//
void RenderingSystem::update(const Time & time) {
    //std::cout << "update rendering system" << std::endl;
}

const string& RenderingSystem::getName() {
    return name;
}


//
//
void CollisionSystem::update(const Time & time) {
}

const string& CollisionSystem::getName() {
    return name;
}


//
//
void KineticSystem::update(const Time & time) {
}

const string& KineticSystem::getName() {
    return name;
}

}