#ifndef FOOBAR_SCREEN_HPP
#define FOOBAR_SCREEN_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using sf::Event;
using sf::Time;
using sf::RenderTexture;

// Forward declaration;
class ScreenManager;

class Screen {

friend class ScreenManager;

private:
    /*
     * is true if the screen is appearing
     */
    bool isEntering = true;

    /*
     * is true if the screen is disappearing
     */
    bool isExiting = false;

    /*
     * if true, the screen can be drawn
     * Should be false, when a non-translucent screen cover this screen
     */
    bool isCovered = false;

    /*
     *
     */
    float transitionTimeElapsed = 0;

    /*
     *
     */
    ScreenManager* owner = nullptr;

protected:
    /*
     * Duration of the transition expressed in seconds
     */
    float transitionDurationSec = 2;

    /*
     * True if the screen should mask the screen below in the stack of screen
     */
    bool isTranslucent = false;

public:
    virtual bool handleEvent(const Event& event) = 0;

    virtual void update(const Time&) = 0;

    virtual void render(RenderTexture&) = 0;

    float getTransition();

    float isActive();

    inline bool getIsEntering() {
        return isEntering;
    }

    inline bool getIsExiting() {
        return isExiting;
    }

    ScreenManager& getOwner();

    void close();

};

#endif //FOOBAR_SCREEN_HPP
