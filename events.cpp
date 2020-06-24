#include <iostream>
#include "globals.hpp"
#include "events.hpp"

std::string event::getDesc() {
    return desc;
}

std::vector<option_t> event::getChildren() {
    return children;
}

event::event(std::string name, std::string desc, std::vector<option_t> children): desc(desc), children(children) {
    eventTree.insert({name, this}); // event constructor, adds event/pointer pair to eventTree on creation
}

void makeEvents() { // makes events
    std::cout << "Making events" << std::endl;
    new event(
        "event000",
        "This is the beginning of the story!",
        {
            option_t{
                .effects={},
                .text = "(1) Option 1",
                .next = "event001"
            },
            option_t{
                .effects={},
                .text = "(2) Option 2",
                .next = "event002"
            }
        }
        );
    new event(
        "event001",
        "You picked option 1!",
        {
            option_t{
                .effects={},
                .text = "(1) End story",
                .next = "event_end"
            }
        }
        );
    new event(
        "event002",
        "You picked option 2!",
        {
            option_t{
                .effects={},
                .text = "(1) End story",
                .next = "event_end"
            }
        }
        );
    new event(
        "event_end",
        "This is the end of the story. Goodbye!",
        {}
        );
}
