#ifndef FOOBAR_LOADSCREEN_HPP
#define FOOBAR_LOADSCREEN_HPP

#include "manifest.hpp"

#include <SFML/System.hpp>
#include <chrono>
#include <future>
#include <vector>

#include "TE/resource/resource_service.hpp"
#include "TE/screen/Screen.hpp"
#include "TE/screen/ScreenService.hpp"
#include "TE/core/ServiceLocator.hpp"
#include "game_screen.hpp"

using namespace std;
using ta::ServiceLocator;

class LoadScreen : public Screen {
private:
    sf::Font font;
    bool is_loading = false;
    bool is_loaded = false;

    vector<resource_info> resources;
    vector<future<raw_resource_handler>> futures;

    sf::Time interval = sf::seconds(1);
    int point = 0;

public:
    LoadScreen(vector<resource_info> resources) : resources(resources) {}

    void update(const sf::Time& time) override {
        if (!is_loading) {
            is_loading = true;
            // request resources to be loaded
            const char* ptr;
            long size;
            // load the font immediately in order to display a loading message within
            // this Screen
            GetResourceService()->immediateLoad(ResourceManifest::FONT, &ptr, &size);
            font.loadFromMemory(reinterpret_cast<const void*>(ptr), size);

            // ask the ResourceService to load all the resources needed for the next
            // Screen
            for (auto r = resources.begin(); r != resources.end(); r++) {
                auto fu = GetResourceService()->deferredLoad(*r);
                futures.push_back(std::move(fu));
            }
        } else if (!is_loaded) {
            // wait for all the resources to be loaded
            bool temp_is_loaded = true;
            for (auto it = futures.begin(); it != futures.end(); it++) {
                std::chrono::duration<int, std::milli> no_wait(0);
                if (it->wait_for(no_wait) != future_status::ready) {
                    temp_is_loaded = false;
                    break;
                }
            }

            is_loaded = temp_is_loaded;

            if (is_loaded) {
                GameScreen* game_screen = new GameScreen();
                GetScreenService()->addScreen(static_cast<Screen*>(game_screen));
                close();
            }

            interval -= time;
            if (interval.asMilliseconds() <= 0) {
                point++;
                interval = sf::seconds(1);
            }
        }
    }

    bool handleEvent(const sf::Event& event) override { return false; }

    void render(sf::RenderTexture& target) override {
        sf::Text text;
        string t = "Loading";
        text.setString(t);
        text.setCharacterSize(7);
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        target.draw(text);
    }
};

#endif
