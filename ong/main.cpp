#include <iostream>
#include <cmath>
#include <math.h>
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

#include "manifest.hpp"

using namespace std;

int main()
{
    sf::Event event;
    sf::Clock clock;
    sf::Sprite sprite;

    // Set window
    sf::RenderWindow window(sf::VideoMode(800, 800), "ONG");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    ScreenManager screen_mgr;
    /*MenuScreen menu_screen;
    menu_screen.load();*/
    GameScreen game_screen;
    game_screen.load();
    screen_mgr.addScreen(static_cast<Screen*>(&game_screen));

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
        RenderTexture render_tex;
        render_tex.create(200, 200);
        screen_mgr.render(render_tex);
        sprite = Sprite(render_tex.getTexture());
        RenderStates rdr_state = sf::RenderStates::Default;
        rdr_state.transform.scale(4, 4, 0, 0);
        window.draw(sprite, rdr_state);
        window.display();
    }
    return 0;
}
