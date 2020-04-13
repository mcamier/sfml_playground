#ifndef TA_MSG_HPP
#define TA_MSG_HPP

#include "../ecs/entity.hpp"
#include "../core/stringId.hpp"
#include <stdexcept>

namespace ta {

using messageType = stringId ;

struct variant {
  enum class type_t { INT_T, UINT_T, FLOAT_T, DOUBLE_T, BOOL_T };

  type_t type;

  union {
    int intValue;
    unsigned int uintValue;
    float floatValue;
    double doubleValue;
    bool boolValue;
  };
};

#define VAR_SETTER_IMPL(STRUCTNAME, IDX) \
template<> void STRUCTNAME::setVar##IDX(int value) {\
    this->v##IDX.type = variant::type_t::INT_T;\
    this->v##IDX.intValue = value;\
}\
template<> int STRUCTNAME::getVar##IDX<int>() {\
    if(this->v##IDX.type != variant::type_t::INT_T) \
        throw std::runtime_error("Fatal error occured when getting #STRUCTNAME var from incompatible type"); \
    return this->v##IDX.intValue;\
}\
template<> void STRUCTNAME::setVar##IDX(bool value) {\
    this->v##IDX.type = variant::type_t::BOOL_T;\
    this->v##IDX.intValue = value;\
}\
template<> bool STRUCTNAME::getVar##IDX<bool>() {\
    if(this->v##IDX.type != variant::type_t::BOOL_T) \
        throw std::runtime_error("Fatal error occured when getting #STRUCTNAME var from incompatible type"); \
    return this->v##IDX.intValue;\
}\
template<> void STRUCTNAME::setVar##IDX(float value) {\
    this->v##IDX.type = variant::type_t::FLOAT_T;\
    this->v##IDX.intValue = value;\
}\
template<> float STRUCTNAME::getVar##IDX<float>() {\
    if(this->v##IDX.type != variant::type_t::FLOAT_T) \
        throw std::runtime_error("Fatal error occured when getting #STRUCTNAME var from incompatible type"); \
    return this->v##IDX.intValue;\
}\
template<> void STRUCTNAME::setVar##IDX(double value) {\
    this->v##IDX.type = variant::type_t::DOUBLE_T;\
    this->v##IDX.intValue = value;\
}\
template<> double STRUCTNAME::getVar##IDX<double>() {\
    if(this->v##IDX.type != variant::type_t::DOUBLE_T) \
        throw std::runtime_error("Fatal error occured when getting #STRUCTNAME var from incompatible type"); \
    return this->v##IDX.intValue;\
}\
template<> void STRUCTNAME::setVar##IDX(unsigned int value) {\
    this->v##IDX.type = variant::type_t::UINT_T;\
    this->v##IDX.intValue = value;\
}\
template<> unsigned int STRUCTNAME::getVar##IDX<unsigned int>() {\
    if(this->v##IDX.type != variant::type_t::UINT_T) \
        throw std::runtime_error("Fatal error occured when getting #STRUCTNAME var from incompatible type"); \
    return this->v##IDX.intValue;\
}


#define VAR_SETTER_DEF(IDX) \
variant v##IDX; \
template<typename T> void setVar##IDX(T value); \
template<typename T> T getVar##IDX();

struct message {
    messageType type = 0;

    VAR_SETTER_DEF(1)
    VAR_SETTER_DEF(2)
    VAR_SETTER_DEF(3)
    VAR_SETTER_DEF(4)
    VAR_SETTER_DEF(5)

};

struct ECSMessage {
    messageType type = 0;
    ECSMessage(messageType msgType) : type(msgType) {}

    VAR_SETTER_DEF(1)
    VAR_SETTER_DEF(2)
    VAR_SETTER_DEF(3)
    VAR_SETTER_DEF(4)
    VAR_SETTER_DEF(5)
};


}  // namespace ta

#endif  // TA_MSG_HPP