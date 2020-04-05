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
        ResourceService::get().deferredLoad(ResourceManifest::BOOM);
        ResourceService::get().deferredLoad(ResourceManifest::HIT);

        REP_DEBUG("add menu screen", LogChannelFlag::DEFAULT)
        Screen* menuScreen = new MenuScreen();
        ScreenService::get().addScreen(menuScreen);
    }
};

int main() {
    PongGame game;
    return game.run();
}
