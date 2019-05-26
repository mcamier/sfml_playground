#include "screen.hpp"

float Screen::getTransition() {
    float transition = transitionTimeElapsed / transitionDurationSec;
    return (transition > 1) ? 1 : transition;
}

float Screen::isActive() {
    return !isCovered && !isExiting && !isEntering;
}

ScreenManager& Screen::getOwner() {
    return *owner;
}

void Screen::close() {
    this->transitionTimeElapsed = 0;
    this->isEntering = false;
    this->isExiting = true;
}
