#include "../../inc/TE/screen/screen.hpp"

namespace ta {

float Screen::getTransition() {
  float transition = transitionTimeElapsed / transitionDurationSec;
  return (transition > 1) ? 1 : transition;
}

float Screen::isActive() { return !isExiting && !isEntering; }

ScreenService& Screen::getOwner() { return *owner; }

void Screen::close() {
  this->transitionTimeElapsed = 0;
  this->isEntering = false;
  this->isExiting = true;
}

}  // namespace ta
