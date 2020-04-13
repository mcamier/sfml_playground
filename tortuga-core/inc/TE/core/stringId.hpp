#ifndef TA_STRINGID_HPP
#define TA_STRINGID_HPP

#include <map>
#include <string>
#include <functional>

namespace ta {

using namespace std;

/**
 * stringId is used to create id's corresponding to given strings
 */
using stringId = size_t;

extern map<stringId, string>* gInternStrings;

stringId gInternString(const char * value);

const string& gStringFromStringId(stringId id);

}

#endif //GANESHENGINE_GHSTRINGID_H
