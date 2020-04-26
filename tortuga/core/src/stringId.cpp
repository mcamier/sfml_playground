#include "../include/tortuga/stringId.hpp"

using std::pair;

namespace ta::core {

map<stringId, string>* gInternStrings = nullptr;

stringId gInternString(const char * value) {
	size_t hash = std::hash<string>{}(value);
#ifdef _DEBUG
	if(gInternStrings == nullptr) {
		gInternStrings = new map<stringId, string>();
	}

	map<stringId, string>::const_iterator itr = gInternStrings->find(hash);
	if(itr == gInternStrings->end()) {
		gInternStrings->insert(pair<stringId, string>(hash, string(value)));
	}
#endif
	return hash;
}

#ifdef _DEBUG
const string& gStringFromStringId(stringId id) {
	static const string noStringFound = "no String Found";
	map<stringId, string>::const_iterator itr = gInternStrings->find(id);
	if(itr == gInternStrings->end()) {
		return noStringFound;
	}
	return itr->second;
}
#else
#include <exception>
using std::logic_error;

const string& gStringFromStringId(stringId id) {
    throw new logic_error("gStringFromStringId must not be used in not debugging purpose");
}
#endif

}