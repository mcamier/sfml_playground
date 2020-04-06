#include "../../inc/TE/ecs/base.hpp"

namespace ta {

unsigned int ComponentBitMask::lastShift = 0;

ComponentBitMask operator|(const ComponentBitMask& op1, const ComponentBitMask& op2) {
    return ComponentBitMask(op1.value | op2.value);
}

ComponentBitMask operator&(const ComponentBitMask& op1, const ComponentBitMask& op2) {
    return ComponentBitMask(op1.value & op2.value);
}

ComponentBitMask operator!=(const ComponentBitMask& op1, const ComponentBitMask& op2) {
    return ComponentBitMask(op1.value != op2.value);
}

bool operator==(const ComponentBitMask& op1, const ComponentBitMask& op2) {
    return op1.value == op2.value;
}

ComponentBitMask operator|=(const ComponentBitMask& op1, const ComponentBitMask op2) {
    return ComponentBitMask(op1.value | op2.value);
}

}