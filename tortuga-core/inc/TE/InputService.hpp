#ifndef TORTUGA_INPUTSERVICE_HPP
#define TORTUGA_INPUTSERVICE_HPP

#include "services/configuration.hpp"
#include "services/service.hpp"
#include "WindowService.hpp"

#include <SFML/Window.hpp>

namespace ta {

using namespace utils;
using namespace sf;

class InputServiceConf : public IServiceConfiguration {
};

class InputService : public ISingletonService<InputService, WindowServiceConf> {
    friend ISingletonService<InputService, InputServiceConf>;

private:
    RenderWindow *window;

public:
    void vUpdate(const Time& time) override {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                //shouldExit = true;
            }
            ScreenService::get().handleEvent(event);
        }
    }

protected:
    void vInit(WindowServiceConf conf) override {
        ASSERT_FLAG(WindowService::_state(), INITIALIZED);
        window = WindowService::get().window;
    }

    void vDestroy() override {

    }

};

}

#endif //TORTUGA_WINDOWSERVICE_HPP
