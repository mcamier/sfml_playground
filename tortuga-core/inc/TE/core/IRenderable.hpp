#ifndef TORTUGA_UPDATABLE_HPP
#define TORTUGA_UPDATABLE_HPP


#include <SFML/Graphics/RenderTexture.hpp>

namespace ta {

using sf::RenderTexture;

class IRenderable {
public:
    virtual void render(RenderTexture &) = 0;
};

}

#endif //TORTUGA_UPDATABLE_HPP
