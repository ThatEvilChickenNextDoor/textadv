#include <iostream>
#include <string>
#include <vector>
#include "globals.hpp"
#include "events.hpp"
#include "cursed.hpp"

int X, Y; // global screen width and height

int handle_input(std::vector<option_t> &optionsList)
{
    unsigned int choice = 0;
    while (1)
    {
        for (std::size_t i = 0; i < optionsList.size(); i++)
        {
            mvaddch(20 + i, 18, ' ');
            mvprintwrap(20 + i, 20, X - 40, optionsList[i].text);
        }
        mvaddch(20 + choice, 18, '>');
        refresh();
        flushinp();
        int key = getch();
        switch (key)
        {
        case KEY_UP:
            if (choice > 0)
                choice--;
            break;
        case KEY_DOWN:
            if (choice < optionsList.size() - 1)
                choice++;
            break;
        case KEY_ENTER:
        case '\n':
            return choice;
        case 'q':
            endwin();
            exit(0);
        default:
            break;
        }
    }
}

void startDay(const std::vector<std::string> &calendar, int day, bool unknownTime)
{
    std::vector<option_t> optionsList{};
    std::string currentEvent = calendar[day];          // keep track of current event, start at the first event
    event *cur = eventTree.find(currentEvent)->second; // create event pointer, point at first event
    erase();
    drawborder();
    if (!unknownTime)
        randdatetime(dayssince(date::August / 1 / 2019, day), "After School");
    else
        randdatetime("\?\?/\?\? \?\?\?", "Unknown");
    while (cur != eventTree.end()->second)
    { // as long as cur points to a valid event, do game loop
        mvprintwrap(10, 20, X - 40, cur->getDesc());
        refresh();
        auto children = cur->getChildren();
        if (children.empty())
        { // if event has no children, end the day
            getch();
            return;
        }
        for (option_t option : children)
        { // populate valid options
            if (flags.count(option.prereq))
            {
                optionsList.push_back(option);
            }
        }
        // Handle input
        int choice = handle_input(optionsList);
        currentEvent = optionsList[choice].next;
        cur = eventTree.find(currentEvent)->second;
        for (std::string flag : optionsList[choice].effects)
        {
            flags.insert(flag);
        }
        optionsList.clear();
        if (optionsList[choice].onClickText != "")
        {
            erase();
            drawborder();
            if (!unknownTime)
                drawdatetime(dayssince(date::August / 1 / 2019, day), "After School");
            else
                drawdatetime("\?\?/\?\? \?\?\?", "Unknown");
            mvprintwrap(10, 20, X - 40, optionsList[choice].onClickText);
            getch();
        }
        erase();
        drawborder();
        if (!unknownTime)
            drawdatetime(dayssince(date::August / 1 / 2019, day), "After School");
        else
            drawdatetime("\?\?/\?\? \?\?\?", "Unknown");
        refresh();
    }
    throw currentEvent;
}

void init_ncurses()
{
    // initialize ncurses window
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, Y, X);
    refresh();
}

void startCalendar(const std::vector<std::string> &calendar, bool unknownTime)
{
    for (std::size_t i = 0; i < calendar.size(); i++)
    {
        try
        {
            startDay(calendar, i, unknownTime);
        }
        catch (const std::string &e)
        {
            endwin();
            std::cout << "Crash happened on day " << i << std::endl;
            std::cout << "Event not found: " << e << std::endl;
            exit(1);
        }
    }
}
int main()
{
    init_ncurses();
    std::vector<std::string> introCalendar, calendar;
    // intro event
    new event("intro000", "You awake to find yourself standing in a vast, boundless desert.", {option_t{.text{"..."}, .next{"intro001"}}});
    new event("intro001", "Every so often, the wind picks up a handful of sand and throws it across the dunes.", {option_t{.text{"..."}, .next{"intro001"}}});
    new event("introEnd", "The winds shift.", {});
    introCalendar.push_back("intro000");
    introCalendar.push_back("intro000");
    // startCalendar(introCalendar, true);
    // initialize events and load into calendar
    makeEvents();
    calendar.push_back("event000");
    calendar.push_back("event000");
    calendar.push_back("newthing");
    // play events from calendar
    startCalendar(calendar, false);
    endwin();
    return 0;
}
