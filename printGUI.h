#ifndef PRINTGUI_H
#define PRINTGUI_H

#include <ncurses.h>



void printWelcomeWin();
void printAppBarWin();

void outputResultFind(FILE* resultFind);
void drawResultFind(WINDOW** resultWinBox, WINDOW** resultWin, FILE* resultFind, int currentLine);

void outputHistoryRequest();
void drawHistoryRequest(WINDOW** historyWinBox, WINDOW** historyWin, FILE* historyFile,int currentLine);

void wprintBox(WINDOW* win, int startY, int startX, int sizeY, int sizeX);

void outputHelp();
void drawHelp(WINDOW** helpWinBox, WINDOW** helpWin, FILE* helpFile, int currentLine);

void drawMainInputBlock(char* pathBuffer,char* nameBuffer,char* typeBuffer, char* sizeBuffer);
void mainInputBlock();

void outputFileLine(WINDOW* resultWin, FILE* file, int currentLine, bool highlightCurrentLine);

int inputLine(WINDOW* win, char* buffer,int sizeBuffer,int* length);
void drawInputLine(char* pathBuffer,char* nameBuffer,char* typeBuffer,char* sizeBuffer);


#endif
