#include <ncurses.h>
#include <vector>
#include <string>

void mvprintascii(int y, int x, std::vector<std::string> arr) {
    for (uint i = 0; i < arr.size(); i++) {
        mvprintw(y+i, x, arr[i].c_str());
    }
    return;
}

void mvprintasciiright(int y, int x, std::vector<std::string> arr) {
    for (uint i = 0; i < arr.size(); i++) {
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

int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, true);
    int y, x;
    getmaxyx(stdscr, y, x);
    drawborder();
    mvprintwrap(10, 20, x-40, "Igor:\nMy name is Igor... I am delighted to make your acquaintance. This place exists between dream and reality, mind and matter... It is a room that only those who are bound by a \"contract\" may enter... It may be that such a fate awaits you in the near future. Now then... Why don't you introduce yourself...?");
    refresh();
    getch();
    while(1) {
        move(y-1, 0);
        clrtoeol();
        scrl(1);
        drawborder();
        refresh();
        getch();
    }
    endwin();
    return 0;
}
