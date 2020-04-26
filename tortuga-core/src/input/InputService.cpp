#include "../../inc/TE/input/InputService.hpp"

#include "../../inc/TE/screen/ScreenService.hpp"
#include "../../inc/TE/WindowService.hpp"

namespace ta {

void InputService::vInit(InputServiceConf conf) {
    ASSERT_FLAG(WindowService::_state(), INITIALIZED);
    window = WindowService::get().window;
}

void InputService::vDestroy() {

}


void InputService::mapCallback(stringId inputName, std::function<void()> callback) {

}

void InputService::vUpdate(const Time& time) {
    sf::Event event;
    while (window->pollEvent(event)) {
/*switch (event.type) {
    case sf::Event::Closed: REP_DEBUG("Closed received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::KeyPressed: REP_DEBUG("KeyPressed received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::KeyReleased: REP_DEBUG("KeyReleased received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::MouseMoved: REP_DEBUG("MouseMoved received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::MouseButtonPressed: REP_DEBUG("MouseButtonPressed received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::MouseButtonReleased: REP_DEBUG("MouseButtonReleased received", LogChannelFlag::DEFAULT)
        break;
    case sf::Event::MouseWheelScrolled: REP_DEBUG("MouseWheelScrolled received", LogChannelFlag::DEFAULT)
        break;
}*/
        if (event.type == sf::Event::Closed) {
            shouldExit = true;
        }
        ScreenService::get().handleEvent(event);
    }
}

}