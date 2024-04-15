// // #include <ncurses.h>

// // int main() {
// //     initscr(); // Инициализация экрана ncurses
// //     cbreak(); // Включить режим CBREAK (без ожидания новой строки для ввода)
// //     noecho(); // Не отображать вводимые символы
// //     keypad(stdscr, TRUE); // Включить поддержку функциональных клавиш

// //     // Создать окно с поддержкой прокрутки
// //     WINDOW *scrollwin = newwin(10, 30, 5, 5);
// //     scrollok(scrollwin, TRUE); // Разрешить прокрутку в окне
// //     refresh();
// //     // Добавить большой объем информации
// //     for (int i = 0; i < 7; ++i) {
// //         wprintw(scrollwin, "Line %d\n", i);
// //     }
// //     wrefresh(scrollwin);
// //     getch();

// //     for (int i = 7; i < 15; ++i) {
// //         wprintw(scrollwin, "Line %d\n", i);
// //     }
// //     // Обновить окно для отображения изменений
// //     // Прокрутить текст вверх на 10 строк
// //     wrefresh(scrollwin);
// //     getch();
// //     int ch;
// //     while ((ch = wgetch(scrollwin))){
// //         switch (ch) {
// //             case KEY_UP:
// //                 wscrl(scrollwin, +5);
// //                 wrefresh(scrollwin);
// //                 break;
// //             case KEY_DOWN:
// //                 wscrl(scrollwin, -5);
// //                 wrefresh(scrollwin);
// //                 break;
// //         }
// //     }

// //     // Обновить окно после прокрутки
// //     wrefresh(scrollwin);

// //     // Добавить возможность закрытия программы
// //     printw("Press any key to exit...");
// //     refresh();
// //     getch();

// //     // Освободить память и завершить работу с ncurses
// //     delwin(scrollwin);
// //     endwin();
// //     return 0;
// // }
// #include <ncurses.h>
// #include <stdio.h>
// #include <string.h>
// #include <panel.h>

// int main() {

//     // printf("%d", strlen("/home/bobr/.mozilla/firefox/d9s3aqgz.default-release/storage/default/moz-extension+++d5387527-d46c-45b2-bcc2-b7bccb4179d7^userContextId=4294967295/idb/3647222921wleabcEoxlt-eengsairo.sqlite-wal"));
//     getch();
//     initscr(); // Инициализация экрана ncurses
//     cbreak(); 
//     noecho();
//     keypad(stdscr, TRUE);


// // Создание первого окна
//     WINDOW *win1 = newwin(10, 20, 5, 5);
//     box(win1, 0, 0);
//     mvwprintw(win1, 1, 1, "Window 1");
//     mvwprintw(win1, 2, 1, "Window 1");
//     mvwprintw(win1, 3, 1, "Window 1");
//     mvwprintw(win1, 4, 1, "Window 1");
//     wrefresh(win1);

//     // Ожидание нажатия клавиши
//     wgetch(win1);

//     // Создание второго окна поверх первого
//     WINDOW *win2 = newwin(5, 10, 7, 7);
//     box(win2, 0, 0);
//     mvwprintw(win2, 1, 1, "Window 2");
//     wrefresh(win2);

//     // Преобразование окон в панели
//     PANEL *panel1 = new_panel(win1);
//     PANEL *panel2 = new_panel(win2);

//     // Ожидание нажатия клавиши
//     wgetch(win2);

//     // Скрытие и удаление второй панели
//     hide_panel(panel2);
//     // del_panel(panel2);
//     // delwin(win2);

//     // Обновление экрана
//     update_panels();
//     doupdate();

//     // Ожидание нажатия клавиши
//     wgetch(win1);

//     // Освобождение памяти и завершение работы с ncurses
//     endwin();
//     return 0;
// }
#include <ncurses.h>

int main() {
    initscr(); // Инициализация экрана ncurses
    cbreak(); // Включить режим CBREAK (без ожидания новой строки для ввода)
    noecho(); // Не отображать вводимые символы
    keypad(stdscr, TRUE); // Включить поддержку функциональных клавиш

    // Вывод текста до изменения размера окна
    printw("Resize the window to see the effect.\n");
    refresh();

    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            // Обработка других клавиш
        }

        // Проверка изменения размера окна
        if (ch == KEY_RESIZE) {
            // Очистить экран и вывести сообщение о изменении размера окна
            clear();
            printw("Window size has been changed!\n");
            refresh();

            // Обновить экран
            refresh();
        }
    }

    // Завершение работы с ncurses
    endwin();

    return 0;
}
