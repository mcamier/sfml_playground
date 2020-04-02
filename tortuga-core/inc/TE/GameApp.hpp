#ifndef TORTUGA_GAMEAPP_HPP
#define TORTUGA_GAMEAPP_HPP

#include "message/message.hpp"

namespace ta {

const messageType_t EXIT_GAME_REQUESTED = 0x0;

class GameApp {
private:
    bool shouldExit = false;

public:
    GameApp() = default;

    GameApp(const GameApp &) = delete;

    GameApp &operator=(const GameApp &) = delete;

    int run();

protected:
    virtual void vInitialize() {};

    virtual void vDestroy() {};

private:
    void readConfIni();

    void initializeSubSystems();

    void destroySubSystems();
};

}

#endif //TORTUGA_GAMEAPP_HPP
