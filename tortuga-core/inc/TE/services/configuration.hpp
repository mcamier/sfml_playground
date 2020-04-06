#ifndef TORTUGA_CONFIGURATION_HPP
#define TORTUGA_CONFIGURATION_HPP

#include <string>
#include <map>
#include "../hash.hpp"

namespace ta::utils {

using std::string;
using std::map;

class IServiceConfiguration {
protected:
    map<unsigned int, string> properties;

    template<typename T> T getCastedProperty(const std::string& value);

public:
    void setProperty(const string& property, const string value) {
        properties.insert(std::make_pair(makeHash(property), value));
    };
};

}
#endif //TORTUGA_CONFIGURATION_HPP
