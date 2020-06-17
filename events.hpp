#ifndef EVENTS
#define EVENTS
#include <string>
#include <vector>
struct event_t {
    std::string text;
    std::vector< std::vector<std::string> > children;
};
#endif