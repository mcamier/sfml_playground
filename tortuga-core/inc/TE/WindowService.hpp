#ifndef TORTUGA_WINDOWSERVICE_HPP
#define TORTUGA_WINDOWSERVICE_HPP

#include "managers.hpp"

namespace ta {

using namespace utils;

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

public:
    void vUpdate() override {

    }

protected:
    void vInit(WindowServiceConf initStructArg) override {

    }

    void vDestroy() override {

    }

};

}

#endif //TORTUGA_WINDOWSERVICE_HPP
