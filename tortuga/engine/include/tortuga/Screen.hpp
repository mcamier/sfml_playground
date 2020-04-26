#ifndef FOOBAR_SCREEN_HPP
#define FOOBAR_SCREEN_HPP

#include <tortuga/stringId.hpp>

namespace ta {

using namespace core;

// Forward declaration;
class ScreenService;

/**
 * Abstract class for any Screen displaying in the game like a pause menu, the menu Screen, the loading Screen or the
 * gameplay.
 */
class Screen /*: public IEventHandler, public IUpdatable, public IRenderable*/ {
    // Allow the ScreenService to access private fields or methods of a Screen object
    friend class ScreenService;

private:
    /* is true if the Screen is appearing
     */
    bool isEntering;

    /* is true if the Screen is disappearing
     */
    bool isExiting;

    /* Elapsed time of the transition in seconds
     */
    float transitionTimeElapsed;

    /* Computed value, is true the Screen must be drawn
     */
    bool _isRenderable;

    /* Blocker Screen doesnt allow Screen below to be updated
     */
    bool isBlocker;

    /* Translucent Screen allow Screen below to be drawn
     */
    bool isTranslucent;

    /* Duration of the transition expressed in seconds
     */
    float transitionDurationSec;

public:
    Screen();

    float getTransition();

    float isActive();

    inline bool getIsEntering() { return isEntering; }

    inline bool getIsExiting() { return isExiting; }

    void close();

    //void _update(const Time& time);

    virtual void onEntering(const float transitionInterpolation) {}

    virtual void onExiting(const float transitionInterpolation) {}

    virtual void handleInput() {}

    void setInputCallback(stringId inputName, std::function<void()> callback);

};

}  // namespace ta

#endif  // FOOBAR_SCREEN_HPP
