#ifndef TORTUGA_GAMEAPP_HPP
#define TORTUGA_GAMEAPP_HPP

#include "message/message.hpp"
#include "screen/ScreenService.hpp"
#include "resource/resource_service.hpp"
#include "WindowService.hpp"
#include "message/message_service.hpp"
#include "profiler.hpp"
#include "logger.hpp"

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
    void readConfIni(LoggerServiceConf* loggerServiceConf,
                     WindowServiceConf* windowServiceConf,
                     ProfilerServiceConf* profilerServiceConf,
                     MessageServiceConf* messageServiceConf,
                     ScreenServiceConf* screenServiceConf,
                     ResourceServiceConf* resourceServiceConf);

    void initializeSubSystems();

    void destroySubSystems();

    // methods related to ini file reading
    void trim(string& line);
    bool isGroup(string& line);
    bool isValidGroup(const string& groupName);
    bool extract(const string& line, string* outKey, string* outValue);

};

}

#endif //TORTUGA_GAMEAPP_HPP
