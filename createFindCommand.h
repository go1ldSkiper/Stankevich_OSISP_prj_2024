#ifndef CREATEFINDCOMMAND_H
#define CREATEFINDCOMMAND_H

#include <stdio.h>


void createCommand(char* command, char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer);
FILE* sendCommand(char* command);
void find(char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer);

#endif