#include "screen_manager.hpp"

void ScreenManager::addScreen(Screen* screenPtr)
{
    screenPtr->isEntering = true;
    screenPtr->isExiting = false;
    screenPtr->owner = this;
    screenPtr->transitionTimeElapsed = 0;

    screenList.push_back(screenPtr);
}

void ScreenManager::handleEvent(const Event& event) {
    auto itr = screenList.begin();
    while(itr != screenList.end()) {
        Screen* screen = (*itr);


        if(screen->isActive() && !screen->handleEvent(event)) {
            // do not propagate to the next screen is handleEvent return false;
            break;
        }
        itr++;
    }
}

void ScreenManager::update(const Time& time)
{
    bool isCovered = false;

    auto itr = screenList.begin();
    while(itr != screenList.end()) {
        Screen* screen = (*itr);

        if (isCovered) {
            screen->isCovered = true;

            itr++;
        }
        else {
            if (screen->isEntering) {
                if (screen->getTransition() < 1) {
                    screen->transitionTimeElapsed += time.asSeconds();
                }
                else {
                    screen->isEntering = false;
                    screen->transitionTimeElapsed = 0;

                    if(!screen->isTranslucent) {
                        isCovered = true;
                    }
                }
                screen->update(time);
                itr++;
            }
            else if (screen->isExiting) {
                if (screen->getTransition() < 1) {
                    screen->transitionTimeElapsed += time.asSeconds();
                    screen->update(time);
                    itr++;
                }
                else {
                    // TODO cleaner solution: release asset, memory, etc.. then erase it from the list
                    itr = screenList.erase(itr);
                }
            }
            else {
                screen->update(time);
                itr++;
            }
        }
    }
}


void ScreenManager::render(RenderWindow& target)
{
    RenderTexture render_tex;
    Sprite sprite;
    RenderStates rdr_state = sf::RenderStates::Default;
    rdr_state.transform.scale(1, -1, 400, 300);
    render_tex.create(800, 600);

    auto itr = screenList.rbegin();
    while(itr != screenList.rend()) {
        Screen* screen = (*itr);

        if(!screen->isCovered) {
            screen->render(render_tex);
            sprite = Sprite(render_tex.getTexture());
            target.draw(sprite, rdr_state);
        }
        itr++;
    }
}