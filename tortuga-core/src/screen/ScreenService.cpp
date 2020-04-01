#include "../../inc/TE/screen/ScreenService.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ta {

using sf::RenderStates;
using sf::Sprite;

void ScreenService::addScreen(Screen* screenPtr) {
    screenPtr->isEntering = true;
    screenPtr->isExiting = false;
    screenPtr->transitionTimeElapsed = 0;

    screenList.push_front(screenPtr);
}

bool ScreenService::handleEvent(const Event &event) {
    auto itr = screenList.begin();
    while (itr != screenList.end()) {
        Screen* screen = (*itr);

        // make the Screen handle the event only of it is active
        if (screen->isActive()) {
            bool propagateEvent = !screen->handleEvent(event);

            // do not propagate to the next Screen is handleEvent return false;
            if(!propagateEvent) break;
        }
        itr++;
    }
    return false;
}

void ScreenService::update(const Time &time) {
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

void ScreenService::render(RenderTexture &target) {
    auto itr = screenList.rbegin();
    while (itr != screenList.rend()) {
        Screen* screen = (*itr);
        screen->render(target);
        itr++;
    }
}

}  // namespace ta