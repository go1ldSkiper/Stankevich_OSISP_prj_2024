#ifndef WORKWITHHISTORY_H
#define WORKWITHHISTORY_H

#include <stdio.h>


FILE* deleteLineInFile(FILE* oldDiscript, const char* fileName, int numberLineToDelete);

void addCommandInHistory(char* command);

void searchFromHistory(FILE* file, int currentLine);

#endif