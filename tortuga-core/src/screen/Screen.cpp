#include "../../inc/TE/screen/Screen.hpp"

namespace ta {

Screen::Screen() {
    this->isEntering = true;
    this->isExiting = false;
    this->isTranslucent = false;
    this->transitionTimeElapsed = 0.0;
    this->transitionDurationSec = 1.0;
    this->isBlocker = true;
}

float Screen::getTransition() {
    float transition = transitionTimeElapsed / transitionDurationSec;
    return (transition >= 1) ? 1 : transition;
}

float Screen::isActive() { return !isExiting && !isEntering; }

void Screen::close() {
    this->transitionTimeElapsed = 0;
    this->isEntering = false;
    this->isExiting = true;
}

}  // namespace ta
