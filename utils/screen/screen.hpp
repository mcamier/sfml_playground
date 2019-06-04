#ifndef FOOBAR_SCREEN_HPP
#define FOOBAR_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using sf::Event;
using sf::RenderTexture;
using sf::Time;

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
   * Elapsed time of the transition in seconds
   */
  float transitionTimeElapsed = 0;

  /*
   * Instance of the screenManager managing the screen
   */
  ScreenManager* owner = nullptr;

  /*
   * Computed value, is true the screen must be drawn
   */
  bool _isRenderable = false;

 protected:
  /*
   * Blocker screen doesnt allow screen below to be updated
   */
  bool isBlocker = true;

  /*
   * Translucent screen allow screen below to be drawn
   */
  bool isTranslucent = false;

  /*
   * Duration of the transition expressed in seconds
   */
  float transitionDurationSec = 2.0f;

 public:
  virtual bool handleEvent(const Event& event) = 0;

  virtual void update(const Time&) = 0;

  virtual void render(RenderTexture&) = 0;

  float getTransition();

  float isActive();

  inline bool getIsEntering() { return isEntering; }

  inline bool getIsExiting() { return isExiting; }

  ScreenManager& getOwner();

  void close();
};

#endif  // FOOBAR_SCREEN_HPP
