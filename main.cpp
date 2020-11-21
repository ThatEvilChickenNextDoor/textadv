#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <set>
#include "globals.hpp"
#include "events.hpp"
#include "cursed.hpp"

int X, Y; // global screen width and height

void startDay(int day){
    std::vector<option_t> optionsList{};
    std::string currentEvent = calendar[day]; // keep track of current event, start at the first event
    event * cur = eventTree.find(currentEvent)->second; // create event pointer, point at first event
    while (cur != eventTree.end()->second) { // as long as cur points to a valid event, do game loop
        mvprintwrap(10, 20, X-40, cur->getDesc());
        refresh();
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
            for (std::size_t i = 0; i < optionsList.size(); i++) {
                mvprintwrap(20+i, 20, X-40, optionsList[i].text);
            }
            refresh();
            flushinp();
            int key = getch();
            switch(key) {
                case KEY_UP :
                    printw("yee");
                    break;
                case KEY_ENTER :
                case '\n' :
                    valid = true;
                    currentEvent = "haha crash me";
                    cur = eventTree.find(currentEvent)->second;
                    optionsList.clear();
                    refresh();
                    break;
                case 'q' :
                    endwin();
                    exit(1);
                default :
                    break;
            }
            /*std::cin >> in; // read choice and sanitize input
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
            }*/
        }
    }
    throw currentEvent;
}

void init_ncurses(){
    // initialize ncurses window
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    getmaxyx(stdscr, Y, X);
    drawborder();
    refresh();
}

int main() {
    init_ncurses();    
    // initialize events and load into calendar
    makeEvents();
    flags.insert("");
    calendar.push_back("event000");
    calendar.push_back("event000");
    calendar.push_back("newthing");
    // play events from calendar
    for (std::size_t i = 0; i < calendar.size(); i++) {
        //printf("It's day %u.\n", i + 1);
        try{
            startDay(i);
        } catch (std::string e) {
            endwin();
            std::cout << "Crash happened on day " <<  i << std::endl;
            std::cout << "Event not found: " << e << std::endl;
            return 1;
        }
    }
    endwin();
    return 0;
}
