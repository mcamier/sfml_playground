#ifndef FOOBAR_SCREEN_MANAGER_HPP
#define FOOBAR_SCREEN_MANAGER_HPP

#include <list>
#include <SFML/System.hpp>

#include "screen.hpp"

using std::list;

using sf::Event;
using sf::Time;
using sf::Sprite;
using sf::RenderWindow;
using sf::RenderTexture;
using sf::RenderStates;

class ScreenManager {

public:
    list<Screen*> screenList;

    void addScreen(Screen* screenPtr);

    void handleEvent(const Event& event);

    void update(const Time& time);

    void render(RenderTexture& target);

};

#endif //FOOBAR_SCREEN_MANAGER_HPP
