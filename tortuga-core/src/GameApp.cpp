#include "../inc/TE/GameApp.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <fstream>

#include "../inc/TE/message/message_service.hpp"
#include "../inc/TE/resource/resource_service.hpp"
#include "../inc/TE/screen/ScreenService.hpp"
#include "../inc/TE/logger.hpp"
#include "../inc/TE/profiler.hpp"
#include "../inc/TE/core/core.hpp"

namespace ta {

using namespace utils;

const int WIDTH = 800;
const int HEIGHT = 800;
const int FRAMERATE_LIMIT = 60;
const bool VSYNC = true;
const string title = "ONG!";

int GameApp::run() {
    sf::Event event;
    sf::Clock clock;
    sf::Sprite sprite;

    // Set window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), title);
    window.setFramerateLimit(FRAMERATE_LIMIT);
    window.setVerticalSyncEnabled(VSYNC);

    this->initializeSubSystems();
    this->vInitialize();

    clock.restart();
    while (!shouldExit) {
        sf::Time elapsed = clock.restart();

        // for debugging purpose only
        if (elapsed.asSeconds() >= 1.0f) {
            // if the elapsed time since the last frame is greater or equals than 1.5
            // seconds fix it at 16 milliseconds in order to not break the simulation
            elapsed = sf::milliseconds(500);
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                shouldExit = true;
            }
            ScreenService::get().handleEvent(event);
        }

        ScreenService::get().update(elapsed);
        MessageService::get().update(elapsed);

        BEGIN_PROFILING("drawing")
            window.clear(sf::Color::Black);
            RenderTexture render_tex;
            render_tex.create(WIDTH, HEIGHT);

            ScreenService::get().render(render_tex);
            render_tex.display();
            sprite = sf::Sprite(render_tex.getTexture());
            window.draw(sprite);
            window.display();
        END_PROFILING

        ProfilerService::get().vUpdate();
    }

    this->vDestroy();
    this->destroySubSystems();
    window.close();

    return 0;
}

void GameApp::initializeSubSystems() {
    BEGIN_PROFILING("Initialize all subsystems")
        this->readConfIni();

        LoggerServiceInitializeArgs_t loggerManagerInitArgs = {};
        loggerManagerInitArgs.fileLogEnabled = true;
        loggerManagerInitArgs.fileLogBaseName = "log";
        loggerManagerInitArgs.fileLogFolder = "D:\\workspace\\sfml_playground\\cmake-build-debug-mingw64\\ong";
        loggerManagerInitArgs.consoleLogEnabled = true;
        loggerManagerInitArgs.logLevel = LogLevelBitsFlag::DEBUG;
        loggerManagerInitArgs.logChannel = LogChannelBitsFlag::DEFAULT | LogChannelBitsFlag::RENDER;

        ProfilerServiceInitializeArgs_t profilerManagerInitArgs = {};
        MessageServiceConf_t messageServiceConf = {};
        ScreenServiceConf_t screenServiceConf = {};
        ResourceServiceConf_t resourceServiceConf = {};

        LoggerService::initialize(loggerManagerInitArgs);
        // LoggerService must be initialized before doing any logging
        REP_DEBUG("Initialize all subsystems", LogChannelBitsFlag::DEFAULT)
        ProfilerService::initialize(profilerManagerInitArgs);

        MessageService::initialize(messageServiceConf);
        ResourceService::initialize(resourceServiceConf);
        //WindowService::initialize();
        ScreenService::initialize(screenServiceConf);
    END_PROFILING

    MessageService::get().subscribe(EXIT_GAME_REQUESTED, [this](message msg) { this->shouldExit = true; });
}

void GameApp::destroySubSystems() {
    REP_DEBUG("Destroy all subsystems", LogChannelBitsFlag::DEFAULT)
    ScreenService::destroy();
    //WindowService::destroy();
    ResourceService::destroy();
    MessageService::destroy();
    ProfilerService::destroy();
    LoggerService::destroy();
}

void GameApp::readConfIni() {
    string path = GetWorkingDir() + string("conf.ini");

    ifstream file;
    string line;
    file.open(path.c_str(), std::ios::in);
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

}


}