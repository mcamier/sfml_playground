#ifndef TORTUGA_SYSTEM_HPP
#define TORTUGA_SYSTEM_HPP

#include <SFML/Graphics/RenderTexture.hpp>

namespace ta {

class ISystem {

};

class RenderSystem : public ISystem {

public:
    void render(sf::RenderTexture& target) {

    }
};

}

#endif //TORTUGA_SYSTEM_HPP
