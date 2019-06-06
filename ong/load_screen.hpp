#ifndef FOOBAR_LOADSCREEN_HPP
#define FOOBAR_LOADSCREEN_HPP

#include "manifest.hpp"

#include <vector>

#include "TE/resource/resource_service.hpp"
#include "TE/screen/screen.hpp"
#include "TE/screen/screen_manager.hpp"
#include "game_screen.hpp"

using namespace std;

class LoadScreen : public Screen {
 private:
  sf::Font font;
  bool is_loading = false;
  bool is_loaded = false;
  ResourceService &res_service;
  vector<resource_info> resources;

 public:
  LoadScreen(ResourceService &resource_service, vector<resource_info> resources)
      : res_service(resource_service), resources(resources) {}

  void update(const sf::Time &time) override {
    if (!is_loading) {
      is_loading = true;
      // request resources to be loaded
      const char *ptr;
      long size;
      // load the font immediately in order to display a loading message within
      // this screen
      res_service.immediateLoad(ResourceManifest::FONT, &ptr, &size);
      font.loadFromMemory(reinterpret_cast<const void *>(ptr), size);

      // ask the ResourceService to load all the resources needed for the next
      // screen
      for (auto r = resources.begin(); r != resources.end(); r++) {
        res_service.deferredLoad(*r);
      }
    } else if (!is_loaded) {
      // wait for all the resources to be loaded
    } else {
      // everything it loaded open up the game screen and close this one
      GameScreen *pong_screen = new GameScreen(res_service);
      ScreenManager &mgr = getOwner();
      mgr.addScreen(static_cast<Screen *>(pong_screen));
      close();
    }
  }

  bool handleEvent(const sf::Event &event) override { return false; }

  void render(sf::RenderTexture &target) override {
    sf::Text text;
    text.setString("Loading");
    text.setCharacterSize(16);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    target.draw(text);
  }
};

#endif
