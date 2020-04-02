
#include <list>

#include "TE/screen/ScreenService.hpp"
#include "TE/GameApp.hpp"

#include "../header/menu_screen.hpp"

using namespace std;
using ta::GameApp;

class PongGame : public GameApp {
public:
    void vInitialize() override {
        Screen* menuScreen = new MenuScreen();
        ScreenService::get().addScreen(menuScreen);
    }
};

int main() {
    PongGame game;
    return game.run();
}
