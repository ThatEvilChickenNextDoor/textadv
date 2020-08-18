#ifndef CURSED
#define CURSED
#include <curses.h>
#include <vector>
#include <set>
#include <string>
#include "date.h"

void mvprintascii(int y, int x, std::vector<std::string> arr) {
    for (uint8_t i = 0; i < arr.size(); i++) {
        mvprintw(y+i, x, arr[i].c_str());
    }
    return;
}

void mvprintasciiright(int y, int x, std::vector<std::string> arr) {
    for (uint8_t i = 0; i < arr.size(); i++) {
        mvprintw(y+i, x-arr[i].size(), arr[i].c_str());
    }
    return;
}

void drawborder() {
    const std::vector<std::string> leftbrack = {"|            _..-~\"", "|     _..-~~\"", "| .-~/", "|/  |", "|  /", "| |", "|/", "|"};
    const std::vector<std::string> rightbrack = {"\"~-.._            |", "\"~~-.._     |", "\\~-. |", "|  \\|", "\\  |", "| |", "\\|"};
    mvprintascii(1,0,leftbrack);
    mvprintasciiright(1,getmaxx(stdscr),rightbrack);
    box(stdscr, 0, 0);
    return;
}

void mvprintwrap(int y, int x, int wrap, std::string text) {
    int offset = 0;
    for (char c : text) {
        move(y,x+offset);
        if (c == '\n') {
            offset = 0;
            y++;
            continue;
        }
        addch(c);
        if (++offset == wrap) {
            offset = 0;
            y++;
        }
    }
    return;
}

void drawdatetime(std::string date, std::string time) {
    mvprintw(1,2, date.c_str());
    printw(" ");
    mvprintw(2,2,time.c_str());
    printw(" ");
    return;
}

std::string dayssince(date::sys_days since, int offset) {
    since += date::days(offset);
    return date::format("%m/%d %a", since);
}
#endif
