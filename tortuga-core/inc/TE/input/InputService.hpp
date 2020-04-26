#ifndef TORTUGA_INPUTSERVICE_HPP
#define TORTUGA_INPUTSERVICE_HPP

#include "../services/configuration.hpp"
#include "../services/service.hpp"
#include "inputs.hpp"

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>
#include <map>

namespace ta {

using namespace utils;
using namespace sf;
using namespace std;

class InputMapping {
    stringId actionName;
    InputCode inputCode;
};

class InputServiceConf : public IServiceConfiguration {
};

class InputService : public ISingletonService<InputService, InputServiceConf> {
    friend ISingletonService<InputService, InputServiceConf>;
public:
    bool shouldExit = false;
private:
    RenderWindow* window;
    map<stringId, list<InputMapping>> inputContexts;

public:
    void vUpdate(const Time& time) override;

    void mapCallback(stringId inputName, std::function<void()> callback);

protected:
    void vInit(InputServiceConf conf) override;
    void vDestroy() override;

};

}

#endif //TORTUGA_WINDOWSERVICE_HPP
