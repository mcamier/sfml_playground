#ifndef TORTUGA_UIELEMENT_HPP
#define TORTUGA_UIELEMENT_HPP

#include <string>
#include <iostream>
#include <functional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../../../math/vec2.hpp"
#include "../../../core/IEventHandler.hpp"
#include "../../../core/IRenderable.hpp"
#include "../../../math/math.hpp"

namespace ta {


using sf::Font;
using sf::Text;
using ta::vec2;
using std::string;
using std::function;

enum class UIOrigin {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER
};

class UIElement : public IEventHandler, public IRenderable {

protected:
    UIOrigin origin;
    vec2f position;

public:
    //virtual void getBoundingBox() = 0;
};


class UILabel : public UIElement {
private:
    Text text;

public:
    bool handleEvent(const Event& event) override {
        // do nothing
        return true;
    }

    void render(RenderTexture& renderTarget) override {
        float x = this->position.x * renderTarget.getSize().x;
        float y = this->position.y * renderTarget.getSize().y;

        if (origin == UIOrigin::TOP_RIGHT || origin == UIOrigin::BOTTOM_RIGHT) {
            x -= text.getLocalBounds().width;
        }
        if (origin == UIOrigin::BOTTOM_RIGHT || origin == UIOrigin::BOTTOM_LEFT) {
            y -= text.getLocalBounds().height;
        }
        if (origin == UIOrigin::CENTER) {
            x -= text.getLocalBounds().width / 2;
            y -= text.getLocalBounds().height / 2;
        }

        this->text.setPosition(x, y);
        renderTarget.draw(this->text);
    }

    static UIElement*
    buildElement(const string& label, const Font& font, UIOrigin origin, int fontSize, float x, float y) {
        UILabel* element = new UILabel();
        element->origin = origin;
        element->position.x = x;
        element->position.y = y;
        element->text.setString(label);
        element->text.setCharacterSize(fontSize);
        element->text.setFont(font);
        element->text.setFillColor(sf::Color::Red);
        element->text.setPosition(0, 0);
        return element;
    }
};

class UIButton : public UIElement {
private:
    Text text;
    std::function<void()> callback;

public:
    bool handleEvent(const Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            vec2f point = vec2f(event.mouseButton.x, event.mouseButton.y);
            rectf rect = rectf(text.getPosition().x, text.getPosition().y, text.getLocalBounds().width, text.getLocalBounds().height);
            if (isPointInsideRect(point, rect)) {
                std::cout << "poouet" << std::endl;
                callback();
            }
        }

        return true;
    }

    void render(RenderTexture& renderTarget) override {
        float x = this->position.x * renderTarget.getSize().x;
        float y = this->position.y * renderTarget.getSize().y;

        if (origin == UIOrigin::TOP_RIGHT || origin == UIOrigin::BOTTOM_RIGHT) {
            x -= text.getLocalBounds().width;
        }
        if (origin == UIOrigin::BOTTOM_RIGHT || origin == UIOrigin::BOTTOM_LEFT) {
            y -= text.getLocalBounds().height;
        }
        if (origin == UIOrigin::CENTER) {
            x -= text.getLocalBounds().width / 2;
            y -= text.getLocalBounds().height / 2;
        }

        this->text.setPosition(x, y);
        renderTarget.draw(this->text);
    }

    static UIElement* buildElement(const string& label, const Font& font, UIOrigin origin, int fontSize, float x, float y, std::function<void()> callback) {
        UIButton* element = new UIButton();
        element->callback = callback;
        element->origin = origin;
        element->position.x = x;
        element->position.y = y;
        element->text.setString(label);
        element->text.setCharacterSize(fontSize);
        element->text.setFont(font);
        element->text.setFillColor(sf::Color::Red);
        element->text.setPosition(0, 0);
        return element;
    }
};

}

#endif //TORTUGA_UIELEMENT_HPP
