#include "cursed.hpp"
#include <locale.h>
#include <thread>
#include <chrono>

// Test program to test cursed methods

int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, true);
    int y, x;
    getmaxyx(stdscr, y, x);
    drawborder();
    drawdatetime(dayssince(date::August/1/2019,0), "After School");
    mvprintwrap(10, 20, x-40, "Igor:\nMy name is Igor... I am delighted to make your acquaintance.\nThis place exists between dream and reality, mind and matter...\nIt is a room that only those who are bound by a \"contract\" may enter...\nIt may be that such a fate awaits you in the near future.\nNow then... Why don't you introduce yourself...?");
    refresh();
    getch();
    int offset = 0;
    for (int i = 0; i < 5; i++) {
        move(y-1, 0);
        clrtoeol();
        scrl(1);
        drawborder();
        randdatetime(dayssince(date::August/1/2019, ++offset), "After School");
        refresh();
        flushinp();
        getch();
    }
    endwin();
    return 0;
}
