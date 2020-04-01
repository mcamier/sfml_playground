#include "../../../inc/TE/screen/ui/UIScreen.hpp"

#include "../../../inc/TE/screen/ui/element/UIElement.hpp"
#include "../../../inc/TE/math/rect.hpp"

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace ta {

using namespace std;

void UIScreen::addItem(UIElement* pElement) {
    elements.push_back(pElement);
}

void UIScreen::render(RenderTexture& renderTarget) {
    auto itr = elements.begin();
    while (itr != elements.end()) {
        UIElement* elt = (*itr);
        elt->render(renderTarget);
        itr++;
    }
}


bool UIScreen::handleEvent(const Event& event) {
    for (auto& element : elements) {
        if(!element->handleEvent(event)) break;
    }
    return false;
}

}

