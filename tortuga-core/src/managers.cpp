#include "../inc/TE/managers.hpp"

namespace ta::utils {


template<>
bool IServiceConfiguration::getCastedProperty(const std::string& value) {
    // todo
    return true;
}

template<>
int IServiceConfiguration::getCastedProperty(const std::string& value) {
    // todo
    return 1;
}

template<>
float IServiceConfiguration::getCastedProperty(const std::string& value) {
    // todo
    return 1.f;
}

template<>
double IServiceConfiguration::getCastedProperty(const std::string& value) {
    // todo
    return 1.f;
}

template<>
char IServiceConfiguration::getCastedProperty(const std::string& value) {
    // todo
    return 'a';
}
}