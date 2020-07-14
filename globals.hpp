#ifndef GLOBALS
#define GLOBALS
#include <map>
#include <iterator>
#include <set>
#include "events.hpp"

inline std::map<std::string, event*> eventTree; // global variable, stores event name and points to the event
inline std::set<std::string> flags; // global variable, stores flags
inline std::vector<std::string> calendar; //holds starting event of each day
#endif