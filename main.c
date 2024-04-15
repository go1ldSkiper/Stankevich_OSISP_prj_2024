// #include "header.h"
#include "header.h"
#include <ncurses.h>

int main() {
    initscr();  // Инициализация библиотеки ncurses
    if (!has_colors()) {
        printw("Colors are not supported!");
        endwin();    // Завершение работы с ncurses
        return 0;
    }
    keypad(stdscr, TRUE); // Включить использование функциональных клавиш
    cbreak(); // Включить режим CBREAK
    // scrollok(stdscr, true);
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    start_color();
    init_color(COLOR_YELLOW, 1000, 1000, 0); // Создает насыщенный желтый цвет
    noecho();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    bkgdset(COLOR_PAIR(1));  
    clear(); 
    printWelcomeWin();
    printAppBarWin();
    mainInputBlock();
    echo();
    endwin();    // Завершение работы с ncurses
    return 0;
}