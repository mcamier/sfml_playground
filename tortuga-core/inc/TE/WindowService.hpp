#ifndef TORTUGA_WINDOWSERVICE_HPP
#define TORTUGA_WINDOWSERVICE_HPP

#include "services/configuration.hpp"
#include "services/service.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ta {

using namespace utils;
using namespace sf;

class InputService;

class WindowServiceConf : public IServiceConfiguration {
    CONF_PROPERTY(string, title)
    CONF_PROPERTY(int, width)
    CONF_PROPERTY(int, height)
    CONF_PROPERTY(bool, vsync)
    CONF_PROPERTY(bool, fullscreen)
    CONF_PROPERTY(int, frameratelimit)
};

class WindowService : public ISingletonService<WindowService, WindowServiceConf> {
    friend ISingletonService<WindowService, WindowServiceConf>;
    friend InputService;

private:
    RenderWindow* window;
    RenderTexture renderTarget;
    int width;
    int height;
    int framerateLimit;
    bool fullscreen;
    bool vsync;

public:
    void vUpdate(const Time& time) override {}

    void draw() {
        window->clear();
        renderTarget.display();
        sf::Sprite sprite = sf::Sprite(renderTarget.getTexture());
        window->draw(sprite);
        window->display();
        renderTarget.clear();
    }

    RenderTexture& getCurrentTarget() {
        return renderTarget;
    }

protected:
    void vInit(WindowServiceConf conf) override {
        width = conf.get_width();
        height = conf.get_height();
        framerateLimit = conf.get_frameratelimit();
        vsync = conf.get_vsync();
        fullscreen = conf.get_fullscreen();

        window = new sf::RenderWindow(sf::VideoMode(width, height), conf.get_title().c_str(), (fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
        window->setFramerateLimit(framerateLimit);
        window->setVerticalSyncEnabled(vsync);

        renderTarget.create(width, height);
    }

    void vDestroy() override {
        window->close();
    }

};

}

#endif //TORTUGA_WINDOWSERVICE_HPP
