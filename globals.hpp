#ifndef GLOBALS
#define GLOBALS
#include <map>
#include <iterator>
#include <list>
#include "events.hpp"

inline std::map<std::string, event*> eventTree; // global variable, stores event name and points to the event
inline std::list<std::string> flags; // global variable, stores flags (not implemented)
#endif