#ifndef TORTUGA_BASE_ENTITY_HPP
#define TORTUGA_BASE_ENTITY_HPP

#include <map>
#include <list>

namespace ta {

typedef unsigned int EntityId;

class ComponentBitMask {
private:
    static unsigned int lastShift;

    explicit ComponentBitMask(unsigned int value) : value(value) {}

    unsigned int value;

public:
    ComponentBitMask() : value(0) {}

    ComponentBitMask(const ComponentBitMask & other) : value(other.value) {}

    ComponentBitMask& operator=(const ComponentBitMask & other) {
        if(&other == this) return *this;
        value = other.value;
        return *this;
    }

    static ComponentBitMask getNext() {
        if(ComponentBitMask::lastShift==32) {
            throw std::runtime_error("ComponentBitMask size overflow");
        }
        return ComponentBitMask(1 << ComponentBitMask::lastShift++);
    }

    friend ComponentBitMask operator|(const ComponentBitMask&, const ComponentBitMask&);
    friend ComponentBitMask operator&(const ComponentBitMask&, const ComponentBitMask&);
    friend bool operator==(const ComponentBitMask&, const ComponentBitMask&);
    friend ComponentBitMask operator!=(const ComponentBitMask&, const ComponentBitMask&);
    friend ComponentBitMask operator|=(const ComponentBitMask&, const ComponentBitMask);
    operator int() const { return this->value; }
};

#define COMPONENT_DEF(CLASS) \
class CLASS : public IComponent { \
public: \
    static const char* name; \
    CLASS() {} \
    static const ComponentBitMask bitmask; \
    ComponentBitMask getType() override; \
private:


#define COMPONENT_IMPL(CLASS) \
const char* CLASS::name = #CLASS; \
const ComponentBitMask CLASS::bitmask = ComponentBitMask::getNext(); \
ComponentBitMask CLASS::getType() { \
    return CLASS::bitmask; \
};


}

#endif //TORTUGA_ENTITY_HPP
