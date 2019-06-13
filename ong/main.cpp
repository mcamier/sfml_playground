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
#include "TE/screen/screen_service.hpp"
#include "TE/service_locator.hpp"
#include "ball.hpp"
#include "game_screen.hpp"
#include "header.hpp"
#include "load_screen.hpp"
#include "player.hpp"

#include "manifest.hpp"

#include <functional>
#include <string>

using namespace std;
using namespace ta;

int main() {
  sf::Event event;
  sf::Clock clock;
  sf::Sprite sprite;

  // Set window
  sf::RenderWindow window(sf::VideoMode(800, 800), "ONG");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  MessageService msgService;
  ResourceService resourceService;
  ScreenService screenService;

  ServiceLocator::messageService = &msgService;
  ServiceLocator::resourceService = &resourceService;
  ServiceLocator::screenService = &screenService;

  vector<resource_info> gameScreenResources;
  gameScreenResources.push_back(ResourceManifest::BOOM);
  gameScreenResources.push_back(ResourceManifest::HIT);
  // gameScreenResources.push_back(ResourceManifest::FONT);

  LoadScreen load_screen(gameScreenResources);
  screenService.addScreen(static_cast<Screen*>(&load_screen));

  clock.restart();
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();

    // for debugging purpose only
    if (elapsed.asSeconds() >= 1.5f) {
      // if the elapsed time since the last frame is greater or equals than 1.5
      // seconds fix it at 16 milliseconds in order to not break the simulation
      elapsed = sf::milliseconds(10);
    }

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      screenService.handleEvent(event);
    }

    screenService.update(elapsed);
    msgService.update();

    window.clear(sf::Color::Black);
    RenderTexture render_tex;
    render_tex.create(200, 200);
    screenService.render(render_tex);
    sprite = Sprite(render_tex.getTexture());
    RenderStates rdr_state = sf::RenderStates::Default;
    rdr_state.transform.translate(0, 800);
    rdr_state.transform.scale(4, -4, 0, 0);
    window.draw(sprite, rdr_state);
    window.display();
  }
  return 0;
}
