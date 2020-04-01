#ifndef TORTUGA_UISCREEN_HPP
#define TORTUGA_UISCREEN_HPP

#include "../Screen.hpp"
#include <list>

namespace ta {

using namespace std;

// forward declaration
class UIElement;

class UIScreen : public Screen {

private:
    list<UIElement*> elements;

public:
    void addItem(UIElement* pElement);

    void render(RenderTexture& renderTarget) override;

    bool handleEvent(const Event& event) override;

};

}

#endif //TORTUGA_UISCREEN_HPP
