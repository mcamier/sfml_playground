#ifndef TORTUGA_UIELEMENT_HPP
#define TORTUGA_UIELEMENT_HPP

#include <string>
#include <iostream>
#include <functional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../../math/vec2.hpp"
#include "../../../core/origin.hpp"
#include "../../../core/IEventHandler.hpp"
#include "../../../core/IRenderable.hpp"
#include "../../../math/math.hpp"

namespace ta {

using sf::Font;
using sf::Text;
using ta::vec2;
using std::string;
using std::function;

class UIElement : public IEventHandler, public IRenderable {

protected:
    Origin origin;
    vec2f position;

};

class UITextElement : public UIElement {

protected:
    Text text;

public:
    void render(RenderTexture& renderTarget) override {
        float x = this->position.x * renderTarget.getSize().x;
        float y = this->position.y * renderTarget.getSize().y;

        if (origin == Origin::TOP_RIGHT || origin == Origin::BOTTOM_RIGHT) {
            x -= text.getLocalBounds().width;
        }
        if (origin == Origin::BOTTOM_RIGHT || origin == Origin::BOTTOM_LEFT) {
            y -= text.getLocalBounds().height;
        }
        if (origin == Origin::CENTER) {
            x -= text.getLocalBounds().width / 2;
            y -= text.getLocalBounds().height / 2;
        }

        this->text.setPosition(x, y);
        renderTarget.draw(this->text);
    }

};


class UILabel : public UITextElement {

public:
    bool handleEvent(const Event& event) override {
        // do nothing
        return true;
    }

    static UIElement* buildElement(const string& label, const Font& font, Origin origin, int fontSize, float x, float y) {
        UILabel* element = new UILabel();
        element->origin = origin;
        element->position.x = x;
        element->position.y = y;
        element->text.setString(label);
        element->text.setCharacterSize(fontSize);
        element->text.setFont(font);
        element->text.setFillColor(sf::Color::Red);
        return element;
    }
};

class UIButton : public UITextElement {
private:
    std::function<void()> callback;

public:
    bool handleEvent(const Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            vec2f point = vec2f(event.mouseButton.x, event.mouseButton.y);
            rectf rect = rectf(text.getPosition().x, text.getPosition().y, text.getLocalBounds().width, text.getLocalBounds().height);
            if (isPointInsideRect(point, rect)) {
                callback();
                return false;
            }
        }
        return true;
    }

    static UIElement* buildElement(const string& label, const Font& font, Origin origin, int fontSize, float x, float y, std::function<void()> callback) {
        UIButton* element = new UIButton();
        element->callback = callback;
        element->origin = origin;
        element->position.x = x;
        element->position.y = y;
        element->text.setString(label);
        element->text.setCharacterSize(fontSize);
        element->text.setFont(font);
        element->text.setFillColor(sf::Color::Red);
        return element;
    }
};

}

#endif //TORTUGA_UIELEMENT_HPP
