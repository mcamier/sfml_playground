#ifndef TORTUGA_CONFIGURATION_HPP
#define TORTUGA_CONFIGURATION_HPP

#include <string>
#include <map>
#include "hash.hpp"
#include "stringId.hpp"

namespace ta::core {

using std::string;
using std::map;
using std::make_pair;

/**
 *
 */
class IServiceConfiguration {
protected:
    map<stringId, string> properties;

    template<typename T> T getCastedProperty(const std::string& value);

public:
    void setProperty(const string& property, const string value) {
        properties.insert(make_pair(gInternString(property.c_str()), value));
    };
};

}
#endif //TORTUGA_CONFIGURATION_HPP
