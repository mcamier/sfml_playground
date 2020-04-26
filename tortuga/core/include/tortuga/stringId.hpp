#ifndef TA_STRINGID_HPP
#define TA_STRINGID_HPP

#include <map>
#include <string>

namespace ta::core {

using std::string;
using std::map;

/**
 * stringId is used to create id's corresponding to given strings
 */
using stringId = size_t;

/**
 * Storage as a Map for all strings hashed into a StringId
 * The main purpose of it is to retrieve origin String from a StringId in order to
 * display it in a readable way
 * The usage of this storage may be deactivated in non debug run
 */
extern map<stringId, string>* gInternStrings;

/**
 * Return a hash from a string for efficient memory usage in the engine
 * Pair of hash and correspondant string are persisted during the runtime, but this should be deactivated
 * for any non debug run of the engine
 *
 * @param value string to hash
 * @return hash a the given string
 */
stringId gInternString(const char * value);

/**
 * Return the string corresponding to the given hash. For debug purpose only, in order to display
 * hash string in a readable fashion
 * This method does nothing if the flag _DEBUG is defined at compilation time
 *
 * @param id hash of the string to restrieve
 * @return string
 */
const string& gStringFromStringId(stringId id);

}

#endif //GANESHENGINE_GHSTRINGID_H
