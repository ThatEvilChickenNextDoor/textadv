#include <iostream>
#include "globals.hpp"
#include "events.hpp"

std::string event::getDesc() {
    return desc;
}

std::vector< std::vector<std::string> > event::getChildren() {
    return children;
}

event::event(std::string name, std::string desc, std::vector< std::vector<std::string> > children): desc(desc), children(children) {
    eventTree.insert({name, this});
}

void makeEvents() {
    std::cout << "Making events" << std::endl;
    event * beginning = new event("event000", "This is the beginning of the story", {{"Option 1", "event001"}, {"Option 2", "event002"}});
}
