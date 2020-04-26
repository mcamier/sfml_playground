#include "../include/tortuga/configuration.hpp"
#include "../include/tortuga/log_utils.hpp"

#include <stdlib.h>

namespace ta::core {

template<>
bool IServiceConfiguration::getCastedProperty(const std::string& value) {
    if(value.length()>1) return false;
    return (value[0] == '1');
}

template<>
int IServiceConfiguration::getCastedProperty(const std::string& value) {
    return strtol(value.c_str(), nullptr, 10);
}

template<>
float IServiceConfiguration::getCastedProperty(const std::string& value) {
    return strtof(value.c_str(), nullptr);
}

template<>
double IServiceConfiguration::getCastedProperty(const std::string& value) {
    return strtod(value.c_str(), nullptr);
}

template<>
char IServiceConfiguration::getCastedProperty(const std::string& value) {
    return value.c_str()[0];
}

template<>
std::string IServiceConfiguration::getCastedProperty(const std::string& value) {
    return value;
}

template<>
LogLevelFlag IServiceConfiguration::getCastedProperty(const std::string& value) {
    int v = strtol(value.c_str(), nullptr, 10);
    LogLevelFlag f = static_cast<LogLevelFlag>(v);
    return f;
}

template<>
LogChannelFlag IServiceConfiguration::getCastedProperty(const std::string& value) {
    int v = strtol(value.c_str(), nullptr, 10);
    LogChannelFlag f = static_cast<LogChannelFlag>(v);
    return f;
}

}