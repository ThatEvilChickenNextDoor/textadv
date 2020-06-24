#ifndef EVENTS
#define EVENTS
#include <string>
#include <vector>
#include <iostream>

struct option_t {
    std::vector<std::string> effects; //currently does nothing
    std::string text;
    std::string next;
};

class event { // event structure forward declaration
    public:
        std::string getDesc();
        std::vector<option_t> getChildren();
        event(std::string name, std::string desc, std::vector<option_t> children);
    private:
        std::string desc;
        std::vector<option_t> children;
};

void makeEvents();
#endif