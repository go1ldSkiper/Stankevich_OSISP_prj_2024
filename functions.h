#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>


void createCommand(char* command, char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer);
FILE* sendCommand(char* command);

FILE* deleteLineInFile(FILE* oldDiscript, const char* fileName, int numberLineToDelete);

void addCommandInHistory(char* command);
void find(char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer);
void searchFromHistory(FILE* file, int currentLine);

#endif