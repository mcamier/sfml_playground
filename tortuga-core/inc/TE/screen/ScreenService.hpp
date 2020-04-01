#ifndef FOOBAR_SCREEN_SERVICE_HPP
#define FOOBAR_SCREEN_SERVICE_HPP

#include <list>
#include <memory>

#include "Screen.hpp"
#include "../core/IEventHandler.hpp"
#include "../core/IUpdatable.hpp"
#include "../core/IRenderable.hpp"

namespace ta {

using std::list;
using std::unique_ptr;

class ScreenService : public IEventHandler, public IUpdatable, public IRenderable {

private:
    list<Screen*> screenList;

public:
    void addScreen(Screen* screenPtr);

    bool handleEvent(const Event &event);

    void update(const Time &);

    void render(RenderTexture &);

};

}  // namespace ta

#endif  // FOOBAR_SCREEN_SERVICE_HPP
