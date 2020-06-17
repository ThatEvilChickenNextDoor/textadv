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
    eventTree.insert({name, this}); // event constructor, adds event/pointer pair to eventTree on creation
}

void makeEvents() { // makes events
    std::cout << "Making events" << std::endl;
    new event(
        "event000",
        "This is the beginning of the story!",
        {{"(1) Option 1", "event001"},
        {"(2) Option 2", "event002"}}
        );
    new event(
        "event001",
        "You picked option 1!",
        {{"(1) End story", "event_end"}}
        );
    new event(
        "event002",
        "You picked option 2!",
        {{"(1) End story", "event_end"}}
        );
    new event(
        "event_end",
        "This is the end of the story. Goodbye!",
        {{}}
        );
}
