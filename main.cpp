#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <set>
#include "globals.hpp"
#include "events.hpp"

void startDay(int day){
    std::vector<option_t> optionsList{};
    std::string currentEvent = calendar[day]; // keep track of current event, start at the first event
    event * cur = eventTree.find(currentEvent)->second; // create event pointer, point at first event
    while (cur != eventTree.end()->second) { // as long as cur points to a valid event, do game loop
        std::cout << cur->getDesc() << std::endl;
        auto children = cur->getChildren();
        if (children.empty()) { // if event has no children, end the day
            return;
        }
        for (option_t option : children) { // populate valid options
            if (flags.count(option.prereq)){
                optionsList.push_back(option);
            }
        }
        // Handle input
        std::string in;
        bool valid = false;
        while (!valid) {
            std::cout << std::endl;
            for (uint8_t i = 0; i < optionsList.size(); i++) {
                printf("(%u) ", i + 1);
                std::cout << optionsList[i].text << std::endl;
            }
            std::cin >> in; // read choice and sanitize input
            int choice;
            try {
                choice = stoi(in);
            } catch (const std::invalid_argument& ia) {
                std::cout << "why would you do this" << std::endl;
                continue;
            }
            choice--;
            if (choice >= 0 && choice < (long int)optionsList.size()){
                valid = true;
                currentEvent = optionsList[choice].next; // update currentEvent to the next event
                cur = eventTree.find(currentEvent)->second; // point cur to next event and loop
                for (std::string flag : optionsList[choice].effects) {
                    flags.insert(flag);
                }
                std::cout << optionsList[choice].onClickText << std::endl;
                optionsList.clear();
            } else{
                std::cout << "no" << std::endl;
            }
        }
    }
    std::cout << "event not found: " << currentEvent << std::endl; // if cur points to invalid event (event not found) loop exits and ends here, list event that wasn't found
    throw 404;
}

int main() {
    // initialize events and load into calendar
    makeEvents();
    flags.insert("");
    calendar.push_back("event000");
    calendar.push_back("event000");
    calendar.push_back("newthing");
    // play events from calendar
    for (uint8_t i = 0; i < calendar.size(); i++) {
        printf("It's day %u.\n", i + 1);
        try{
            startDay(i);
        } catch (...) {
            printf("Crash happened on day %u\n", i);
            return 1;
        }
    }
    
    return 0;
}
