#ifndef EVENTS
#define EVENTS
#include <string>
#include <vector>
#include <iostream>

class event { // event structure forward declaration
    public:
        std::string getDesc();
        std::vector< std::vector<std::string> > getChildren();
        event(std::string name, std::string desc, std::vector< std::vector<std::string> > children);
    private:
        std::string desc;
        std::vector< std::vector<std::string> > children;
};

void makeEvents();
#endif