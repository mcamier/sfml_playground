#ifndef FOOBAR_MENUSCREEN_HPP
#define FOOBAR_MENUSCREEN_HPP

#include <TE/GameApp.hpp>
#include <TE/core/origin.hpp>
#include <TE/screen/ui/UIScreen.hpp>
#include <TE/screen/ui/element/UIElement.hpp>
#include <TE/message/message_service.hpp>
#include "game_screen.hpp"

using namespace ta;

class MenuScreen : public UIScreen {
private:
    sf::Font font;

public:
    MenuScreen() {
        void* fontPtr;
        long fontSize;
        ResourceService::get().getResource(ResourceManifest::FONT, &fontPtr, &fontSize);
        if (!font.loadFromMemory(fontPtr, fontSize)) {
            REP_FATAL("fail to load font from memory", LogChannelFlag::DEFAULT)
        }

        UIElement* title = UILabel::buildElement("ONG!", font, Origin::CENTER, 180, 0.5f, 0.3f);
        this->addItem(title);

        UIElement* subtitle = UILabel::buildElement("It's not Pong, but it's close...", font, Origin::CENTER, 20, 0.5f, 0.5f);
        this->addItem(subtitle);

        UIElement* playButton = UIButton::buildElement("Play", font, Origin::CENTER, 25, 0.5f, 0.7f,
                                                       [this]() { this->onPlayGame(); });
        this->addItem(playButton);
    }

private:
    void onPlayGame() {
        ScreenService::get().addScreen(new GameScreen());
        close();
    }

public:
    void update(const Time& time) override {}
};

#endif
