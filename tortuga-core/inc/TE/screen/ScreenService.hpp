#ifndef FOOBAR_SCREEN_SERVICE_HPP
#define FOOBAR_SCREEN_SERVICE_HPP

#include <list>
#include <memory>

#include "Screen.hpp"
#include "../core/IEventHandler.hpp"
#include "../core/IUpdatable.hpp"
#include "../core/IRenderable.hpp"
#include "../managers.hpp"

namespace ta {

using std::list;
using std::unique_ptr;
using namespace utils;

struct ScreenServiceConf : public IServiceConfiguration {
};

class ScreenService : public ISingletonService<ScreenService, ScreenServiceConf> {
    friend ISingletonService<ScreenService, ScreenServiceConf>;

private:
    list<Screen*> screenList;

public:
    ScreenService &operator=(const ScreenService &) = delete;

    void addScreen(Screen* screenPtr);

    bool handleEvent(const Event &event);

    void render(RenderTexture &);

protected:
    void vInit(ScreenServiceConf initStructArg) override {};

    void vDestroy() override {};

public:
    /**
     * @brief Forward all the messages to the observers
     */
    void vUpdate() override {}

    void update(const Time &time);

};

}  // namespace ta

#endif  // FOOBAR_SCREEN_SERVICE_HPP
