#ifndef GLOBALS
#define GLOBALS
#include <map>
#include <iterator>
#include <list>
#include "events.hpp"

inline std::map<std::string, event*> eventTree;
inline std::list<std::string> flags;
#endif