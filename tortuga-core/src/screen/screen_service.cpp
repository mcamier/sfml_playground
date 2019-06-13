#include "../../inc/TE/screen/screen_service.hpp"

namespace ta {

void ScreenService::addScreen(Screen* screenPtr) {
  screenPtr->isEntering = true;
  screenPtr->isExiting = false;
  screenPtr->owner = this;
  screenPtr->transitionTimeElapsed = 0;

  screenList.push_front(screenPtr);
}

void ScreenService::handleEvent(const Event& event) {
  auto itr = screenList.begin();
  while (itr != screenList.end()) {
    Screen* screen = (*itr);

    if (screen->isActive() && !screen->handleEvent(event)) {
      // do not propagate to the next screen is handleEvent return false;
      break;
    }
    itr++;
  }
}

void ScreenService::update(const Time& time) {
  bool isBlocked = false;

  auto itr = screenList.begin();
  while (itr != screenList.end()) {
    Screen* screen = (*itr);

    if (screen->isEntering) {
      if (screen->getTransition() < 1) {
        screen->transitionTimeElapsed += time.asSeconds();
      } else {
        screen->isEntering = false;
        screen->transitionTimeElapsed = 0;
      }

      if (!isBlocked) screen->update(time);

      itr++;
    } else if (screen->isExiting) {
      if (screen->getTransition() < 1) {
        screen->transitionTimeElapsed += time.asSeconds();
        screen->update(time);
        itr++;
      } else {
        itr = screenList.erase(itr);
      }
    } else {
      if (!isBlocked) screen->update(time);
      itr++;
    }

    isBlocked = screen->isBlocker;
  }
}

void ScreenService::render(RenderTexture& target) {
  RenderTexture render_tex;
  Sprite sprite;
  RenderStates rdr_state = sf::RenderStates::Default;
  rdr_state.transform.scale(1, -1, 100, 100);
  render_tex.create(200, 200);
  render_tex.clear(sf::Color::Black);

  auto itr = screenList.rbegin();
  while (itr != screenList.rend()) {
    Screen* screen = (*itr);

    if (!screen->_isRenderable) {
      screen->render(render_tex);
      sprite = Sprite(render_tex.getTexture());
      target.draw(sprite, rdr_state);
    }
    itr++;
  }
}

}  // namespace ta