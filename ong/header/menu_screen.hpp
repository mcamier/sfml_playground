#ifndef FOOBAR_MENUSCREEN_HPP
#define FOOBAR_MENUSCREEN_HPP

#include <TE/screen/ui/UIScreen.hpp>
#include <TE/screen/ui/element/UIElement.hpp>

using namespace ta;

class MenuScreen : public UIScreen {
private:
    sf::Font font;

public:
    MenuScreen() {
        if (!font.loadFromFile("font.ttf")) {
            cout << "fail to load the font file" << endl;
        }

        UIElement* title = UILabel::buildElement("ONG!", font, UIOrigin::BOTTOM_RIGHT, 130, 0.99f, 0.99f);
        this->addItem(title);

        UIElement* playButton = UIButton::buildElement("Play", font, UIOrigin::TOP_LEFT, 20, 0.02, 0.05f,
                                                       [this]() { this->onPlayGame(); });
        this->addItem(playButton);

        UIElement* exitButton = UIButton::buildElement("Exit", font, UIOrigin::TOP_LEFT, 20, 0.02, 0.1f,
                                                       [this]() { this->onExitApp(); });
        this->addItem(exitButton);
    }

private:
    void onPlayGame() {
        GetScreenService()->addScreen(new GameScreen());
    }

    void onExitApp() {}

public:
    void update(const Time& time) override {}
};

#endif
