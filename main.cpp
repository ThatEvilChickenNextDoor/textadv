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
    for (std::size_t i = 0; i < optionsList.size(); i++)
    {
        mvprintwrap(20 + i, 20, X - 40, optionsList[i].text);
    }
    while (1)
    {
        for (std::size_t i = 0; i < optionsList.size(); i++)
        {
            mvaddch(20 + i, 18, ' ');
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
    std::string time = "Morning";
    erase();
    drawborder();
    if (!unknownTime)
        randdatetime(dayssince(date::August / 1 / 2019, day), time);
    else
        randdatetime("\?\?/\?\? \?\?\?", "Unknown");
    while (cur != eventTree.end()->second) // as long as cur points to a valid event, do game loop
    {
        if (cur->time != "")
        {
            if (!unknownTime)
            {
                time = cur->time;
                erase();
                drawborder();
                drawdatetime(dayssince(date::August / 1 / 2019, day), time);
                refresh();
            }
        }
        mvprintwrap(10, 20, X - 40, cur->getDesc());
        refresh();
        auto children = cur->getChildren();
        if (children.empty()) // if event has no children, end the day
        {
            getch();
            return;
        }
        for (option_t option : children) // populate valid options
        {
            // check for prereqs
            bool prereqs_met = true;
            for (std::string req : option.prereq)
            {
                // if first character is -, check that the flag is NOT set instead
                if (req[0] == '-')
                {
                    req.erase(req.begin()); // remove the first -
                    if (flags.count(req) != 0)
                    {
                        prereqs_met = false;
                        break;
                    }
                }
                else
                {
                    if (flags.count(req) == 0)
                    {
                        prereqs_met = false;
                        break;
                    }
                }
            }
            if (prereqs_met)
            {
                optionsList.push_back(option);
            }
        }
        // Handle input
        int choice = handle_input(optionsList);
        currentEvent = optionsList[choice].next;
        cur = eventTree.find(currentEvent)->second;
        // set flags
        for (std::string flag : optionsList[choice].effects)
        {
            // if first character is -, try to REMOVE the flag instead
            if (flag[0] == '-')
            {
                flag.erase(flag.begin());
                flags.erase(flag);
            }
            else
            {
                flags.insert(flag);
            }
        }
        // display onclick text if any
        if (optionsList[choice].onClickText != "")
        {
            erase();
            drawborder();
            if (!unknownTime)
                drawdatetime(dayssince(date::August / 1 / 2019, day), time);
            else
                drawdatetime("\?\?/\?\? \?\?\?", "Unknown");
            mvprintwrap(10, 20, X - 40, optionsList[choice].onClickText);
            refresh();
            getch();
        }
        optionsList.clear();
        erase();
        drawborder();
        if (!unknownTime)
            drawdatetime(dayssince(date::August / 1 / 2019, day), time);
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
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
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
    std::vector<std::string> introCalendar, calendar, testCalendar;
    makeCommon();
    makeIntroCalendar();
    introCalendar.push_back("intro000");
    // startCalendar(introCalendar, true);
    /*std::string chara;
    if (flags.count("m"))
        chara = "Michael";
    else if (flags.count("t"))
        chara = "Taylor";
    else if (flags.count("r"))
        chara = "Reehan";
    else
        chara = "Julia";*/
    // initialize events and load into calendar
    /*makeEvents(chara);
    calendar.push_back("event000");
    calendar.push_back("event000");
    calendar.push_back("newthing");*/

    calendar.push_back("intro112");
    // play events from calendar
    startCalendar(calendar, false);
    int academics = flags.count("academics");
    new event(
        "test000",
        "Your academics is " + std::to_string(academics),
        {},
        "Judgement"
    );
    testCalendar.push_back("test000");
    startCalendar(testCalendar,false);
    endwin();
    return 0;
}
