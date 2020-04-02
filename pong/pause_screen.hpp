#ifndef FOOBAR_PAUSESCREEN_HPP
#define FOOBAR_PAUSESCREEN_HPP

#include <SFML/System.hpp>
#include <iostream>

#include "TE/math/math.hpp"
#include "TE/math/vec2.hpp"
#include "TE/screen/ScreenService.hpp"

class PauseScreen : public Screen {
private:
    bool isLoaded = false;

    sf::Font font;
    sf::Text text;

public:
    PauseScreen() {
        this->transitionDurationSec = 0.2f;
        this->isBlocker = true;
        this->isTranslucent = true;
    }

    bool load() {
        if (!font.loadFromFile("PressStart2P.ttf")) {
            this->isLoaded = false;
        }

        text.setFont(font);
        text.setCharacterSize(60);
        text.setString("PAUSE");
        text.setFillColor(sf::Color::White);
        text.setOutlineThickness(4);
        text.setOutlineColor(sf::Color::Black);

        text.setPosition(280, 270);

        this->isLoaded = true;
        return this->isLoaded;
    }

    bool handleEvent(const sf::Event& event) override {
        if ((event.type == sf::Event::EventType::KeyPressed) &&
            (event.key.code == sf::Keyboard::Key::Escape)) {
            close();
        }

        return false;
    }

    void update(const sf::Time& time) override {}

    void render(sf::RenderTexture& target) override { target.draw(text); }
};

#endif  // FOOBAR_PAUSESCREEN_HPP
