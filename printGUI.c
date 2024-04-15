#include "header.h"
#include <ncurses.h>
#include <stdio.h>

WINDOW* welcomeWin = NULL;
WINDOW* appBarWin = NULL;
// WINDOW* helpWinBox = NULL;
// WINDOW* helpWin = NULL;
WINDOW* mainInputBlockWin = NULL;
WINDOW* pathWin = NULL;
WINDOW* nameWin = NULL;
WINDOW* typeWin = NULL;
WINDOW* sizeWin = NULL;



int WIN_SIZE_X,WIN_SIZE_Y;
static const int sizePathBuffer = 120, sizeNameBuffer = 120, sizeTypeBuffer = 10, sizeSizeBuffer = 10;


void printWelcomeWin(){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (NULL != welcomeWin){
        delwin(welcomeWin);
    }
    welcomeWin = newwin(3, WIN_SIZE_X, 0, 0);
    wbkgd(welcomeWin, COLOR_PAIR(1));
    wattron(welcomeWin, COLOR_PAIR(1) | A_BOLD);
    char* welcomeStr = "WELCOM TO SEARCH PROGRAMM!";
    mvwprintw(welcomeWin, 0, WIN_SIZE_X/2 - strlen(welcomeStr) / 2, "%s", welcomeStr);
    refresh();
    wrefresh(welcomeWin);
}

void printAppBarWin(){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (NULL != appBarWin){
        delwin(appBarWin);
    }
    appBarWin = newwin(3, WIN_SIZE_X, 1, 0);

    wbkgd(appBarWin, COLOR_PAIR(1));
    wattron(appBarWin, COLOR_PAIR(1) | A_BOLD);
    wborder(appBarWin, 0, 0, 0, 0, 0, 0, 0, 0);

    mvwprintw(appBarWin, 1, 1, "  open history(F1)  |");
    wprintw(appBarWin, "  help(F2)  |");
    wprintw(appBarWin, "  exit(F3)  |");
    refresh();
    wrefresh(appBarWin);
}

void wprintBox(WINDOW* win, int startY, int startX, int sizeY, int sizeX){
    // Нарисовать верхнюю горизонтальную линию рамки
    for (int x = startX; x < startX + sizeX; x++) {
        mvwaddch(win, startY, x, ACS_HLINE);
    }

    // Нарисовать нижнюю горизонтальную линию рамки
    for (int x = startX; x < startX + sizeX; x++) {
        mvwaddch(win, startY + sizeY, x, ACS_HLINE);
    }

    // Нарисовать левую вертикальную линию рамки
    for (int y = startY; y < startY + sizeY; y++) {
        mvwaddch(win, y, startX, ACS_VLINE);
    }

    // Нарисовать правую вертикальную линию рамки
    for (int y = startY; y < startY + sizeY; y++) {
        mvwaddch(win, y, startX + sizeX, ACS_VLINE);
    }
    mvwaddch(win, startY, startX, ACS_ULCORNER); // верхний левый угол
    mvwaddch(win, startY, startX + sizeX, ACS_URCORNER); // верхний правый угол
    mvwaddch(win, startY + sizeY, startX, ACS_LLCORNER); // нижний левый угол
    mvwaddch(win, startY + sizeY, startX + sizeX, ACS_LRCORNER); // нижний правый угол
}

void outputFileLine(WINDOW* resultWin, FILE* file, int currentLine, bool highlightCurrentLine){
    curs_set(0);
    werase(resultWin);
    fseek(file, 0, 0);
    char buffer[255];
    for(int i = 0; i < currentLine; i++)       // Считал все до курент лайн
        fgets(buffer, 255, file);
    if (highlightCurrentLine)
        wattron(resultWin,COLOR_PAIR(2));
    else wattron(resultWin,COLOR_PAIR(1));
    for(int i = 0; i < getmaxy(resultWin) && fgets(buffer, 255, file) != NULL; i++){
        mvwprintw(resultWin, i, 0, "%s", buffer);
        if (i == 0 && highlightCurrentLine)                 // убрать подсветку строки
            wattron(resultWin,COLOR_PAIR(1));
        if (strlen(buffer) / (getmaxx(resultWin) + 2) > 0){    // \n И + 1 чтобы было конкретно больше
            i += strlen(buffer) / (getmaxx(resultWin) + 2);
        }
    }
    wrefresh(resultWin);
}

void drawHelp(WINDOW** helpWinBox, WINDOW** helpWin, FILE* helpFile, int currentLine){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (NULL != *helpWinBox)
        delwin(*helpWinBox);
    *helpWinBox = newwin(WIN_SIZE_Y - 4, WIN_SIZE_X, 4, 0);
    wbkgd(*helpWinBox, COLOR_PAIR(1));
    keypad(*helpWinBox, true);
    if (NULL != *helpWin)
        delwin(*helpWin);
    *helpWin = subwin(*helpWinBox, WIN_SIZE_Y - 6, WIN_SIZE_X - 2, 5, 1);
    wattron(*helpWinBox, COLOR_PAIR(1) | A_BOLD);
    box(*helpWinBox, 0, 0);
    mvwprintw(*helpWinBox, 0, 0, "Help");
    outputFileLine(*helpWin, helpFile, currentLine, false);
    wrefresh(*helpWinBox);
    wrefresh(*helpWin);
}

void outputHelp(){
    int currentLine = 0;
    char buffer[255];
    WINDOW* helpWinBox = NULL;
    WINDOW* helpWin = NULL;
    int numberOfLine;
    FILE *helpFile = fopen(HELP_NAME_FILE, "r+");
    if (helpFile == NULL) {
        return;
    }
    for(numberOfLine = 0; fgets(buffer, 255, helpFile); ++numberOfLine);
    int keyPad;
    drawHelp(&helpWinBox, &helpWin, helpFile, currentLine);
    while(( keyPad = getch() )){
        switch (keyPad) {
            case KEY_UP:
                if (currentLine != 0)
                    --currentLine;
                break;
            case KEY_DOWN:
                if (currentLine < numberOfLine - 1)
                    ++currentLine;
                break;
            case KEY_F(1):
            case KEY_F(2):
                break;
            case KEY_F(3):
                delwin(helpWin);
                delwin(helpWinBox);
                curs_set(1);
                return;
            case KEY_RESIZE:
                printWelcomeWin();
                printAppBarWin();
                drawHelp(&helpWinBox, &helpWin, helpFile, currentLine);
                break;
            default: break;
        }
    outputFileLine(helpWin, helpFile, currentLine, false);
    }
}



void drawResultFind(WINDOW** resultWinBox, WINDOW** resultWin, FILE* resultFind, int currentLine){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (NULL != *resultWinBox)
        delwin(*resultWinBox);
    *resultWinBox = newwin(WIN_SIZE_Y - 4, WIN_SIZE_X, 4, 0);
    wbkgd(*resultWinBox, COLOR_PAIR(1));
    keypad(*resultWinBox, true);
    if (NULL != *resultWin)
        delwin(*resultWin);
    *resultWin = subwin(*resultWinBox, WIN_SIZE_Y - 6, WIN_SIZE_X - 2, 5, 1);
    wattron(*resultWinBox, COLOR_PAIR(1) | A_BOLD);
    box(*resultWinBox, 0, 0);
    mvwprintw(*resultWinBox, 0, 0, "Result");
    outputFileLine(*resultWin, resultFind, currentLine, true);
    // refresh();
    wrefresh(*resultWinBox);
    wrefresh(*resultWin);
}

void outputResultFind(FILE* resultFind){
    int currentLine = 0;
    char buffer[255];
    WINDOW* resultWinBox = NULL;
    WINDOW* resultWin = NULL;
    int numberOfLine;
    for(numberOfLine = 0; fgets(buffer, 255, resultFind); ++numberOfLine);
    int keyPad;
    drawResultFind(&resultWinBox, &resultWin, resultFind, currentLine);
    while(( keyPad = getch() )){
        switch (keyPad) {
            case KEY_UP:
                if (currentLine != 0)
                    --currentLine;
                break;
            case KEY_DOWN:
                if (currentLine < numberOfLine - 1)
                    ++currentLine;
                break;
            case KEY_F(1):
                outputHistoryRequest();
                delwin(resultWin);
                delwin(resultWinBox);
                curs_set(1);
                return;
            case KEY_F(2):
                outputHelp();
                drawResultFind(&resultWinBox, &resultWin, resultFind, currentLine);
                break;
            case KEY_F(3):
                delwin(resultWin);
                delwin(resultWinBox);
                curs_set(1);
                return;
            case KEY_RESIZE:
                printWelcomeWin();
                printAppBarWin();
                drawResultFind(&resultWinBox, &resultWin, resultFind, currentLine);
            default: break;
        }
    outputFileLine(resultWin, resultFind, currentLine, true);
    }
}


void drawHistoryRequest(WINDOW** historyWinBox, WINDOW** historyWin, FILE* historyFile,int currentLine){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (NULL != *historyWinBox)
        delwin(*historyWinBox);
    *historyWinBox = newwin(WIN_SIZE_Y - 4, WIN_SIZE_X, 4, 0);
    wbkgd(*historyWinBox, COLOR_PAIR(1));
    keypad(*historyWinBox, true);
    if (NULL != *historyWin)
        delwin(*historyWin);
    *historyWin = subwin(*historyWinBox, WIN_SIZE_Y - 6, WIN_SIZE_X - 2, 5, 1);
    wattron(*historyWinBox, COLOR_PAIR(1) | A_BOLD);
    box(*historyWinBox, 0, 0);
    mvwprintw(*historyWinBox, 0, 0, "Request history");
    outputFileLine(*historyWin, historyFile, currentLine, true);
    refresh();
    wrefresh(*historyWinBox);
    wrefresh(*historyWin);
}

void outputHistoryRequest(){
    int currentLine = 0;
    char buffer[255];
    WINDOW* historyWinBox = NULL;
    WINDOW* historyWin = NULL;
    FILE *historyFile = fopen(HISTORY_REQUEST_NAME_FILE, "r+");
    if (historyFile == NULL) {
        historyFile = fopen(HISTORY_REQUEST_NAME_FILE, "w+");
    }
    int numberOfLine;
    for(numberOfLine = 0; fgets(buffer, 255, historyFile) != NULL; ++numberOfLine);
    int keyPad;
    drawHistoryRequest(&historyWinBox, &historyWin, historyFile, currentLine);
    while(( keyPad = getch() )){
        switch (keyPad) {
            case KEY_UP:
                if (currentLine != 0)
                    --currentLine;
                break;
            case KEY_DOWN:
                if (currentLine < numberOfLine - 1)
                    ++currentLine;
                break;
            case KEY_DC:
                historyFile = deleteLineInFile(historyFile,HISTORY_REQUEST_NAME_FILE, currentLine);
                --numberOfLine;
                break;
            case ENTER_KEY:
                searchFromHistory(historyFile, currentLine);
                delwin(historyWin);
                delwin(historyWinBox);
                return;
            case KEY_F(2):
                outputHelp();
                printWelcomeWin();
                printAppBarWin();
                drawHistoryRequest(&historyWinBox, &historyWin, historyFile, currentLine);
                break;
            case KEY_F(3):
                delwin(historyWin);
                delwin(historyWinBox);
                curs_set(1);
                return;
            case KEY_RESIZE:
                printWelcomeWin();
                printAppBarWin();
                drawHistoryRequest(&historyWinBox, &historyWin, historyFile, currentLine);
                break;
            default: break;
        }
    outputFileLine(historyWin, historyFile, currentLine, true);
    }
}


int inputLine(WINDOW* win, char* buffer,int sizeBuffer,int* length){
    short int inputSymbols;
    keypad(win, TRUE);
    werase(win);
    mvwprintw(win, 0, 1, "%s", buffer);
    wrefresh(win);
    while((inputSymbols = getch())){
        switch (inputSymbols) {
            case KEY_UP:
            case KEY_DOWN:
            case ENTER_KEY:
            case KEY_F(1):
            case KEY_F(2):
            case KEY_F(3):
            case KEY_RESIZE:
                return inputSymbols;
            case KEY_LEFT:
            case KEY_RIGHT:
                break;
            case KEY_BACKSPACE:
                if ((*length) != 0)
                    buffer[--(*length)] = '\0';
                break;
            default:
                if ((*length) < sizeBuffer - 1)
                    buffer[(*length)++] = inputSymbols;
                break;
        }
        werase(win);
        mvwprintw(win, 0, 1, "%s", buffer);
        wrefresh(win);
    }
    return ENTER_KEY;
}

void drawInputLine(char* pathBuffer,char* nameBuffer,char* typeBuffer,char* sizeBuffer){
    mvwprintw(pathWin, 0, 1, "%s", pathBuffer);
    wrefresh(pathWin);
    mvwprintw(nameWin, 0, 1, "%s", nameBuffer);
    wrefresh(nameWin);
    mvwprintw(typeWin, 0, 1, "%s", typeBuffer);
    wrefresh(typeWin);
    mvwprintw(sizeWin, 0, 1, "%s", sizeBuffer);
    wrefresh(sizeWin);
}

void drawMainInputBlock(char* pathBuffer,char* nameBuffer,char* typeBuffer, char* sizeBuffer){
    getmaxyx(stdscr, WIN_SIZE_Y, WIN_SIZE_X);
    if (mainInputBlockWin != NULL)
        delwin(mainInputBlockWin);
    mainInputBlockWin = newwin(WIN_SIZE_Y - 4, WIN_SIZE_X, 4, 0);
    wbkgd(mainInputBlockWin, COLOR_PAIR(1));
    keypad(mainInputBlockWin, TRUE);
    if (pathWin != NULL)
        delwin(pathWin);
    pathWin = subwin(mainInputBlockWin, 1, WIN_SIZE_X - 7 -3, 6, 8);
    scrollok(pathWin, true);
    if (nameWin != NULL)
        delwin(nameWin);
    nameWin = subwin(mainInputBlockWin, 1, WIN_SIZE_X - 7 -3, 9, 8);
    scrollok(nameWin, true);
    if (typeWin != NULL)
        delwin(typeWin);
    typeWin = subwin(mainInputBlockWin, 1, sizeTypeBuffer, 11, 7);
    if (sizeWin != NULL)
        delwin(sizeWin);
    sizeWin = subwin(mainInputBlockWin, 1, sizeSizeBuffer, 12, 7);

    wattron(mainInputBlockWin,COLOR_PAIR(1) | A_BOLD);
    box(mainInputBlockWin,0,0);
    mvwprintw(mainInputBlockWin, 0, 0, "Input command block");
    mvwprintw(mainInputBlockWin, 2, 1, "Path: ");
    mvwprintw(mainInputBlockWin, 5, 1, "Name: ");
    mvwprintw(mainInputBlockWin, 7, 1, "Type: ");
    mvwprintw(mainInputBlockWin, 8, 1, "Size: ");
    wprintBox(mainInputBlockWin, 1, 7, 2, WIN_SIZE_X - 7 - 2);  // draw box for inputPath
    wprintBox(mainInputBlockWin, 4, 7, 2, WIN_SIZE_X - 7 - 2);  // draw box for inputName

    drawInputLine(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);    
    refresh();
    wrefresh(mainInputBlockWin);
}


void mainInputBlock(){
    char pathBuffer[sizePathBuffer], nameBuffer[sizeNameBuffer], typeBuffer[sizeTypeBuffer], sizeBuffer[sizeSizeBuffer];
    memset(pathBuffer, '\0', sizePathBuffer);
    memset(nameBuffer, '\0', sizeNameBuffer);
    memset(sizeBuffer, '\0', sizeSizeBuffer); 
    memset(typeBuffer, '\0', sizeTypeBuffer);
    ///////////////////////
    const int numberOfLines = 4;
    int lineNumberAndXCoordinate[numberOfLines];
    for(int i = 0; i< numberOfLines; i++)
        lineNumberAndXCoordinate[i] = 0;
    int pressedKey, currentLine = 0;
    drawMainInputBlock(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
    while(1){
        switch (currentLine) {
            case 0: pressedKey = inputLine(pathWin, pathBuffer, sizePathBuffer, (lineNumberAndXCoordinate + currentLine));
                break;
            case 1: pressedKey = inputLine(nameWin, nameBuffer, sizeNameBuffer, (lineNumberAndXCoordinate + currentLine));
                break;
            case 2: pressedKey = inputLine(typeWin, typeBuffer, sizeTypeBuffer, (lineNumberAndXCoordinate + currentLine));;
                break;
            case 3: pressedKey = inputLine(sizeWin, sizeBuffer, sizeSizeBuffer, (lineNumberAndXCoordinate + currentLine));
                break;
        }
        switch (pressedKey) {
            case KEY_UP: 
                if (currentLine != 0) --currentLine;
                break;
            case KEY_DOWN:
                if (currentLine != numberOfLines - 1) ++currentLine;
                break;
            case ENTER_KEY:
                find(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
                drawMainInputBlock(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
                break;
            case KEY_F(1):
                outputHistoryRequest();
                drawMainInputBlock(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
                break;
            case KEY_F(2):
                outputHelp();
                drawMainInputBlock(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
                break;
            case KEY_F(3):
                return;
            case KEY_RESIZE:
                printWelcomeWin();
                printAppBarWin();
                drawMainInputBlock(pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
                break;
            default: 
                break;
        }
    }   
}