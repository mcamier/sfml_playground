#include <list>

#include "TE/screen/ScreenService.hpp"
#include "TE/resource/resource_service.hpp"
#include "TE/GameApp.hpp"

#include "../header/menu_screen.hpp"

using namespace std;
using ta::GameApp;

class PongGame : public GameApp {
public:
    void vInitialize() override {
        ResourceService::get().immediateLoad(ResourceManifest::FONT);

        Screen* screen = new GameScreen();
        ScreenService::get().addScreen(screen);
    }
};

int main() {
    PongGame game;
    return game.run();
}
