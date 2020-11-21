#ifndef CURSED
#define CURSED
#ifdef _WIN64
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include "date.h"
#include <cstdlib>
#include <thread>
#include <chrono>

void mvprintascii(int y, int x, std::vector<std::string> arr) {
    for (std::size_t i = 0; i < arr.size(); i++) {
        mvprintw(y+i, x, arr[i].c_str());
    }
    return;
}

void mvprintasciiright(int y, int x, std::vector<std::string> arr) {
    for (std::size_t i = 0; i < arr.size(); i++) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    refresh();
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

void randdatetime(const std::string &target, std::string time) {
    int timer = 0;
    while (timer < 2500) {
        drawdatetime(target, time);
        if (timer < 500) {
            mvaddch(1,2,'0' + std::rand() % 9);
        }
        if (timer < 1000) {
            mvaddch(1,3,'0' + std::rand() % 9);
        }
        if (timer < 1500) {
            mvaddch(1,5,'0' + std::rand() % 9);
        }
        if (timer < 2000) {
            mvaddch(1,6,'0' + std::rand() % 9);
        }
        char day[4];
        switch ( std::rand() % 6) {
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
        mvprintw(1,8,day);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        timer += 10;
    }
    drawdatetime(target, time);
    return;
}
#endif