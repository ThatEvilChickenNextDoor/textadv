#ifndef GLOBALS
#define GLOBALS
#include <map>
#include <set>
#include "events.hpp"

inline std::map<std::string, event *> eventTree{}; // global variable, stores event name and points to the event
inline std::multiset<std::string> flags{"", "mTalk0"};            // global variable, stores flags
#endif