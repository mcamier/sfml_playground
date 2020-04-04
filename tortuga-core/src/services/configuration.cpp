#include "../../inc/TE/services/configuration.hpp"
#include "../../inc/TE/log_utils.hpp"

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

template<>
std::string IServiceConfiguration::getCastedProperty(const std::string& value) {
    return value;
}

template<>
LogLevelFlag IServiceConfiguration::getCastedProperty(const std::string& value) {
    return LogLevelFlag::DEBUG;
}

template<>
LogChannelFlag IServiceConfiguration::getCastedProperty(const std::string& value) {
    return LogChannelFlag::DEFAULT;
}

}