#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../utils/math/mat3.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "../utils/math/math.hpp"
#include "game_screen.hpp"
#include "menu_screen.hpp"
#include "../utils/screen/screen_manager.hpp"

#define GAME_SCREEN_LOAD_FAILED -1
#define MENU_SCREEN_LOAD_FAILED -2

using namespace std;

int main()
{
    sf::Event event;
    sf::Clock clock;

    // Set window
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    ScreenManager screen_mgr;
    MenuScreen menu_screen;
    menu_screen.load();
    screen_mgr.addScreen(static_cast<Screen*>(&menu_screen));

    clock.restart();
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed)
                window.close();

            screen_mgr.handleEvent(event);
        }

        screen_mgr.update(elapsed);

        window.clear(sf::Color::Black);
        screen_mgr.render(window);
        window.display();
    }
    return 0;
}
