#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <set>
#include "globals.hpp"
#include "events.hpp"

int main() {
    makeEvents();
    flags.insert("");
    std::vector<option_t> optionsList;
    std::string currentEvent = "event000"; // keep track of current event, start at the first event
    event * cur = eventTree.find("event000")->second; // create event pointer, point at first event
    while (cur != eventTree.end()->second) { // as long as cur points to a valid event, do game loop
        std::cout << cur->getDesc() << std::endl;
        auto children = cur->getChildren();
        if (children.empty()) { // if event has no children, end the story
            goto end; // look you code purists sometimes goto works just fine ok get off my back
        } 
        std::string in;
        bool valid = false;
        for (option_t option : children) { // populate valid options
            if (flags.count(option.prereq)){
                optionsList.push_back(option);
            }
        }
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
    return 1;
    end: // end the story!
    return 0;
}
