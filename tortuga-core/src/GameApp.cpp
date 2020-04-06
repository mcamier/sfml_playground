#include "../inc/TE/GameApp.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <algorithm>

#include "../inc/TE/logger.hpp"
#include "../inc/TE/core/core.hpp"
#include "../inc/TE/InputService.hpp"

namespace ta {

using namespace utils;

int GameApp::run() {
    sf::Event event;
    sf::Clock clock;
    sf::Sprite sprite;

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

        ResourceService::get().vUpdate(elapsed);
        InputService::get().vUpdate(elapsed);
        ScreenService::get().vUpdate(elapsed);
        MessageService::get().vUpdate(elapsed);

        BEGIN_PROFILING("drawing")
            RenderTexture& target = WindowService::get().getCurrentTarget();
            ScreenService::get().render(target);
            WindowService::get().draw();
        END_PROFILING

        ProfilerService::get().vUpdate(elapsed);
    }

    this->vDestroy();
    this->destroySubSystems();

    return 0;
}

void GameApp::initializeSubSystems() {
    BEGIN_PROFILING("Initialize all subsystems")
        LoggerServiceConf loggerServiceConf;
        WindowServiceConf windowServiceConf;
        ProfilerServiceConf profilerServiceConf;
        MessageServiceConf messageServiceConf;
        ScreenServiceConf screenServiceConf;
        ResourceServiceConf resourceServiceConf;
        this->readConfIni(&loggerServiceConf, &windowServiceConf, &profilerServiceConf, &messageServiceConf,
                          &screenServiceConf, &resourceServiceConf);

        // LoggerService must be initialized before doing any logging
        LoggerService::initialize(loggerServiceConf);
        REP_DEBUG("Initialize all subsystems", LogChannelFlag::DEFAULT)
        ProfilerService::initialize(profilerServiceConf);
        MessageService::initialize(messageServiceConf);
        WindowService::initialize(windowServiceConf);
        InputService::initialize();
        ResourceService::initialize(resourceServiceConf);
        ScreenService::initialize(screenServiceConf);
        REP_DEBUG("All subsystems initialized", LogChannelFlag::DEFAULT)
    END_PROFILING

    MessageService::get().subscribe(EXIT_GAME_REQUESTED, [this](message msg) { this->shouldExit = true; });
}

void GameApp::destroySubSystems() {
    REP_DEBUG("Destroy all subsystems", LogChannelFlag::DEFAULT)
    ScreenService::destroy();
    ResourceService::destroy();
    WindowService::destroy();
    MessageService::destroy();
    ProfilerService::destroy();
    LoggerService::destroy();
}

void GameApp::readConfIni(LoggerServiceConf* loggerServiceConf,
                          WindowServiceConf* windowServiceConf,
                          ProfilerServiceConf* profilerServiceConf,
                          MessageServiceConf* messageServiceConf,
                          ScreenServiceConf* screenServiceConf,
                          ResourceServiceConf* resourceServiceConf) {

    string path = GetWorkingDir() + string("conf.ini");
    string loggerName = "logger";
    string windowName = "window";
    string profilerName = "profiler";
    string messageName = "message";
    string screenName = "screen";
    string resourceName = "resource";

    ifstream file;
    string line;
    file.open(path.c_str(), std::ios::in);

    string lastGroupName = "";
    bool skipToNextGroup = false;

    while (std::getline(file, line)) {
        // ignore white line
        if (line.length() == 0) { continue; }
        trim(line);

        if (this->isGroup(line)) {
            lastGroupName = string(line);
            skipToNextGroup = !this->isValidGroup(lastGroupName);
        } else if (!lastGroupName.empty() && !skipToNextGroup) {
            string key, value;

            if (extract(line, &key, &value)) {
                if (std::equal(loggerName.begin(), loggerName.end(), lastGroupName.begin())) {
                    loggerServiceConf->setProperty(key, std::move(value));
                } else if (std::equal(windowName.begin(), windowName.end(), lastGroupName.begin())) {
                    windowServiceConf->setProperty(key, std::move(value));
                } else if (std::equal(profilerName.begin(), profilerName.end(), lastGroupName.begin())) {
                    profilerServiceConf->setProperty(key, std::move(value));
                } else if (std::equal(messageName.begin(), messageName.end(), lastGroupName.begin())) {
                    messageServiceConf->setProperty(key, std::move(value));
                } else if (std::equal(screenName.begin(), screenName.end(), lastGroupName.begin())) {
                    screenServiceConf->setProperty(key, std::move(value));
                } else if (std::equal(resourceName.begin(), resourceName.end(), lastGroupName.begin())) {
                    resourceServiceConf->setProperty(key, std::move(value));
                }
            }
        }
    }
}

void GameApp::trim(string& line) {
    if (line.length() == 0) return;

    while (line[0] == ' ') {
        line.erase(line.begin());
    }
    while (line[line.length() - 1] == ' ') {
        line.pop_back();
    }
}

bool GameApp::isGroup(string& line) {
    if (line.length() == 0) return false;
    if (line[0] == '[' && line[line.length() - 1] == ']') {
        line.erase(line.begin());
        line.pop_back();
        return true;
    } else {
        return false;
    }
}

bool GameApp::isValidGroup(const string& groupName) {
    //todo implement me
    return true;
}

bool GameApp::extract(const string& line, string* outKey, string* outValue) {
    bool equalCharReached = false;
    for (int i = 0; i < line.length(); ++i) {
        if (!equalCharReached) {
            if (line[i] == '=') {
                equalCharReached = true;
            } else {
                outKey->push_back(line[i]);
            }
        } else {
            outValue->push_back(line[i]);
        }
    }

    trim(*outKey);
    trim(*outValue);

    outKey->length();
    outValue->length();

    return !(outKey->length() == 0 || outValue->length() == 0);
}

}