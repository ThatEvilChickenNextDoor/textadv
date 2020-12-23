#ifndef CURSED
#define CURSED
#ifdef _WIN64
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <vector>
#include <string>
#include <cstring>
#include "date.h"
#include <cstdlib>
#include <thread>
#include <chrono>

void mvprintascii(int y, int x, const std::vector<std::string> &arr)
{
    for (std::size_t i = 0; i < arr.size(); i++)
    {
        mvprintw(y + i, x, arr[i].c_str());
    }
    return;
}

void mvprintasciiright(int y, int x, const std::vector<std::string> &arr)
{
    for (std::size_t i = 0; i < arr.size(); i++)
    {
        mvprintw(y + i, x - arr[i].size(), arr[i].c_str());
    }
    return;
}

void drawborder()
{
    const std::vector<std::string> leftbrack = {"|            _..-~\"", "|     _..-~~\"", "| .-~/", "|/  |", "|  /", "| |", "|/", "|"};
    const std::vector<std::string> rightbrack = {"\"~-.._            |", "\"~~-.._     |", "\\~-. |", "|  \\|", "\\  |", "| |", "\\|"};
    mvprintascii(1, 0, leftbrack);
    mvprintasciiright(1, getmaxx(stdscr), rightbrack);
    box(stdscr, 0, 0);
    return;
}

void mvprintwrap(int y, int x, int wrap, const std::string &text)
{
    bool skip = false;
    bool special = false;
    int offset = 0;
    flushinp();
    for (char c : text)
    {
        // check for special directive
        if (c == '#' && !special) {
            special = true; // set special flag and look at next character
            continue;
        }
        // execute special action
        if (special) {
            special = false; // reset the special flag
            switch(c) {
                case 'R':
                    attron(COLOR_PAIR(1));
                    continue;
                case 'G':
                    attron(COLOR_PAIR(2));
                    continue;
                case 'B':
                    attron(COLOR_PAIR(3));
                    continue;
                case 'W':
                    attroff(COLOR_PAIR(1));
                    continue;
                default: break; // not valid directive, continue to print the character
            }
        }
        move(y, x + offset); // move cursor to next space
        // handle newlines
        if (c == '\n')
        {
            offset = 0;
            y++;
            continue;
        }
        addch(c);
        // handle wrapping
        if (++offset == wrap)
        {
            offset = 0;
            y++;
        }
        // handle animation
        if (!skip){
            nodelay(stdscr, true);
            skip = (getch() == '\n');
            nodelay(stdscr, false);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            refresh();
        }
    }
    attroff(COLOR_PAIR(1));
    refresh();
    return;
}

void drawdatetime(const std::string &date, const std::string &time)
{
    mvprintw(1, 2, date.c_str());
    printw(" ");
    mvprintw(2, 2, time.c_str());
    printw(" ");
    return;
}

std::string dayssince(date::sys_days since, int offset)
{
    since += date::days(offset);
    return date::format("%m/%d %a", since);
}

void randdatetime(const std::string &target, const std::string &time)
{
    bool skip = false;
    flushinp();
    int timer = 0;
    while (timer < 2500)
    {
        drawdatetime(target, time);
        if (timer < 500)
        {
            mvaddch(1, 2, '0' + std::rand() % 9);
        }
        if (timer < 1000)
        {
            mvaddch(1, 3, '0' + std::rand() % 9);
        }
        if (timer < 1500)
        {
            mvaddch(1, 5, '0' + std::rand() % 9);
        }
        if (timer < 2000)
        {
            mvaddch(1, 6, '0' + std::rand() % 9);
        }
        char day[4];
        switch (std::rand() % 6)
        {
        case 0:
            strcpy(day, "Mon");
            break;
        case 1:
            strcpy(day, "Tue");
            break;
        case 2:
            strcpy(day, "Wed");
            break;
        case 3:
            strcpy(day, "Thu");
            break;
        case 4:
            strcpy(day, "Fri");
            break;
        case 5:
            strcpy(day, "Sat");
            break;
        case 6:
            strcpy(day, "Sun");
            break;
        }
        mvprintw(1, 8, day);
        refresh();

        nodelay(stdscr, true);
        skip = (getch() == '\n');
        nodelay(stdscr, false);
        if (skip)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        timer += 10;
    }
    drawdatetime(target, time);
    return;
}
#endif