#include "../include/tortuga/Screen.hpp"

//#include "../../include/tortuga/input/InputService.hpp"

/*
#include <SFML/System/Time.hpp>
*/

namespace ta {

/*using namespace sf;*/

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

/*void Screen::_update(const Time& time) {
    if(isEntering) {
        this->onEntering(getTransition());
    }
    else if(isExiting) {
        this->onExiting(getTransition());
    }
    this->handleInput();
    this->update(time);
}*/

void Screen::setInputCallback(stringId inputName, std::function<void()> callback) {

}

}  // namespace ta
