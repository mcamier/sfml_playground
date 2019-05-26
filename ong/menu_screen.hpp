#ifndef FOOBAR_MENUSCREEN_HPP
#define FOOBAR_MENUSCREEN_HPP

#include <iostream>
#include <SFML/System.hpp>

#include "../utils/math/vec2.hpp"
#include "../utils/math/math.hpp"
#include "../utils/screen/screen_manager.hpp"

class MenuScreen : public Screen {

private:
    bool isLoaded = false;

    sf::Font font;
    sf::Text title;
    vec2 title_from = vec2(280, -70);
    vec2 title_to = vec2(280, 180);

    sf::Text press_start;
    vec2 press_start_from = vec2(260, 600);
    vec2 press_start_to = vec2(260, 520);

    sf::Time time;

public:

    MenuScreen()
    {
        this->transitionDurationSec = 0.666f;
    }

    bool load()
    {
        if (!font.loadFromFile("PressStart2P.ttf")) {
            this->isLoaded = false;
        }

        title.setFont(font);
        title.setCharacterSize(70);
        title.setString("PONG");
        title.setFillColor(sf::Color::White);
        title.setPosition(title_from.x, title_from.y);

        press_start.setFont(font);
        press_start.setCharacterSize(25);
        press_start.setString("Press start !");
        press_start.setFillColor(sf::Color::White);

        this->isLoaded = true;

        return this->isLoaded;
    }

    bool handleEvent(const sf::Event& event) override
    {

        if ((event.type==sf::Event::EventType::KeyPressed) &&
                (event.key.code==sf::Keyboard::Key::Space || event.key.code==sf::Keyboard::Key::Enter)) {

            GameScreen* pong_screen = new GameScreen();
            pong_screen->load();
            ScreenManager& mgr = getOwner();
            mgr.addScreen(static_cast<Screen*>(pong_screen));
            close();
        }

        return false;
    }

    void update(const sf::Time& time) override
    {
        if (getIsEntering()) {
            float t = getTransition();
            vec2 pos = interpolate(title_from, title_to, t);
            title.setPosition(pos.x, pos.y);

            pos = interpolate(press_start_from, press_start_to, t);
            press_start.setPosition(pos.x, pos.y);
        }
        else if (getIsExiting()) {
            float t = getTransition();
            vec2 pos = interpolate(title_to, title_from, t);
            title.setPosition(pos.x, pos.y);

            pos = interpolate(press_start_to, press_start_from, t);
            press_start.setPosition(pos.x, pos.y);
        }
        else {
            this->time += time;
            float y = press_start_to.y+(cos(this->time.asSeconds())*10);
            press_start.setPosition(press_start_to.x, y);
        }
    }

    void render(sf::RenderTexture& target) override
    {
        target.draw(title);
        target.draw(press_start);
    }

};

#endif //FOOBAR_MENUSCREEN_HPP
