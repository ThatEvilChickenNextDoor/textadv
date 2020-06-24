#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "globals.hpp"
#include "events.hpp"

using namespace std;

int main() {
    makeEvents();
    string currentEvent = "event000"; // keep track of current event, start at the first event
    event * cur = eventTree.find("event000")->second; // create event pointer, point at first event
    while (cur != eventTree.end()->second) { // as long as cur points to a valid event, do game loop
        cout << cur->getDesc() << endl;
        auto children = cur->getChildren();
        if (children.empty()) { // if event has no children, end the story
            goto end; // look you code purists sometimes goto works just fine ok get off my back
        } 
        string in;
        bool valid = false;
        while (!valid) {
            cout << endl;
            for (option_t option : children) { // list option names
            cout << option.text << endl;
            }
            cin >> in; // read choice and sanitize input
            int choice;
            try {
                choice = stoi(in);
            } catch (const std::invalid_argument& ia) {
                cout << "why would you do this" << endl;
                continue;
            }
            choice--;
            if (choice >= 0 && choice < (long int)children.size()){
                valid = true;
                currentEvent = children[choice].next; // update currentEvent to the next event
                cur = eventTree.find(currentEvent)->second; // point cur to next event and loop
                // TODO: handle effects logic here
            } else{
                cout << "no" << endl;
            }
        }
    }
    cout << "event not found: " << currentEvent << endl; // if cur points to invalid event (event not found) loop exits and ends here, list event that wasn't found
    return 1;
    end: // end the story!
    return 0;
}
