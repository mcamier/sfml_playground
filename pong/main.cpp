#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../utils/mat3.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "../utils/math.hpp"
#include "game_screen.hpp"
#include "menu_screen.hpp"
#include "../utils/screen_manager.hpp"

#define GAME_SCREEN_LOAD_FAILED -1
#define MENU_SCREEN_LOAD_FAILED -2

using namespace std;

int main()
{
    sf::Clock clock;
    ScreenManager screen_mgr;

    // Set window
    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    MenuScreen menu_screen;

    if (!menu_screen.load()) {
        return MENU_SCREEN_LOAD_FAILED;
    }

    screen_mgr.addScreen(static_cast<Screen*>(&menu_screen));

    clock.restart();
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if ((event.type==sf::Event::Closed) ||
                (event.type==sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)) {
                window.close();
            }

            screen_mgr.handleEvent(event);
        }

        screen_mgr.update(elapsed);

        window.clear(sf::Color::Black);
        screen_mgr.render(window);
        window.display();

       /*pong_screen.update(elapsed);
        menu_screen.update(elapsed);

        sf::RenderTexture render_tex;
        render_tex.create(800, 600);
        menu_screen.render(render_tex);
        sf::Sprite sprite(render_tex.getTexture());

        window.clear(sf::Color::Black);
        sf::RenderStates rdr_state = sf::RenderStates::Default;
        rdr_state.transform.scale(1, -1, 400, 300);
        window.draw(sprite, rdr_state);
        window.display();*/
    }
    return 0;
}
