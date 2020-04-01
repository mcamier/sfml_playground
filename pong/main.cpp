#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <list>
#include <string>

#include "TE/math/math.hpp"
#include "TE/screen/ScreenService.hpp"
#include "ball.hpp"
#include "game_screen.hpp"
#include "menu_screen.hpp"
#include "player.hpp"

#define GAME_SCREEN_LOAD_FAILED -1
#define MENU_SCREEN_LOAD_FAILED -2

using namespace std;

int main() {
  sf::Event event;
  sf::Clock clock;
  sf::Sprite sprite;

  // Set window
  sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  ScreenService screenService;
  MenuScreen menu_screen;
  menu_screen.load();
  screenService.addScreen(static_cast<Screen*>(&menu_screen));

  clock.restart();
  while (window.isOpen()) {
    sf::Time elapsed = clock.restart();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      screenService.handleEvent(event);
    }

    screenService.update(elapsed);

    window.clear(sf::Color::Black);
    RenderTexture render_tex;
    render_tex.create(800, 600);
    screenService.render(render_tex);
    sprite = sf::Sprite(render_tex.getTexture());
    window.draw(sprite);
    window.display();
  }
  return 0;
}
