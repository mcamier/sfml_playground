#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <vector>

#include "TE/math/math.hpp"
#include "TE/message/message.hpp"
#include "TE/message/message_service.hpp"
#include "TE/message/subscription.hpp"
#include "TE/resource/resource_service.hpp"
#include "TE/screen/ScreenService.hpp"
#include "TE/core/ServiceLocator.hpp"
#include "TE/core/core.hpp"
#include "../header/ball.hpp"
#include "../header/game_screen.hpp"
#include "../header/header.hpp"
#include "../header/load_screen.hpp"
#include "../header/menu_screen.hpp"
#include "../header/player.hpp"

#include "manifest.hpp"

#include <functional>
#include <string>

using namespace std;
using namespace ta;

int main() {
    /*std::cout << GetWorkingDir() << std::endl;
    vector<string> files = GetFileList(GetWorkingDir(), "*.exe");
    for (auto& file : files) {
        std::cout << file << std::endl;
    }*/

    sf::Event event;
    sf::Clock clock;
    sf::Sprite sprite;

    // Set window
    sf::RenderWindow window(sf::VideoMode(1280, 800), "ONG");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    vector<resource_info> gameScreenResources;
    gameScreenResources.push_back(ResourceManifest::BOOM);
    gameScreenResources.push_back(ResourceManifest::HIT);
    gameScreenResources.push_back(ResourceManifest::FONT);

    //LoadScreen load_screen(gameScreenResources);
    Screen* menuScreen = new MenuScreen();
    GetScreenService()->addScreen(menuScreen);
    //screenService.addScreen(static_cast<Screen*>(&load_screen));

    clock.restart();
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        // for debugging purpose only
        if (elapsed.asSeconds() >= 1.0f) {
            // if the elapsed time since the last frame is greater or equals than 1.5
            // seconds fix it at 16 milliseconds in order to not break the simulation
            elapsed = sf::milliseconds(500);
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            GetScreenService()->handleEvent(event);
        }

        GetScreenService()->update(elapsed);

        //msgService.update();

        window.clear(sf::Color::Black);
        RenderTexture render_tex;
        render_tex.create(1280, 800);

        GetScreenService()->render(render_tex);
        render_tex.display();
        sprite = sf::Sprite(render_tex.getTexture());
        window.draw(sprite);
        window.display();
    }
    return 0;
}
