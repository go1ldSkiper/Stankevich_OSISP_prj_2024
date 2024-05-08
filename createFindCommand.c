#include "header.h"
#include <stdio.h>


const char RESULT_FIND_NAME_FILE[] = "tempResultFind.txt";




void createCommand(char* command, char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer){
    memset(command, '\0', 150);
    strcpy(command, "find");
    if (pathBuffer[0] != '\0'){
        strcat(command, " ");
        strcat(command, pathBuffer);
    }
    if (nameBuffer[0] != '\0'){
        strcat(command, " ");
        strcat(command, "-name ");
        strcat(command, nameBuffer);
    }
    if (typeBuffer[0] != '\0'){
        strcat(command, " ");
        strcat(command, "-type ");
        strcat(command, typeBuffer);
    }
    if (sizeBuffer[0] != '\0'){
        strcat(command, " ");
        strcat(command, "-size ");
        strcat(command, sizeBuffer);
    }
}

FILE* sendCommand(char* command){
    strcat(command, " > ");
    strcat(command, RESULT_FIND_NAME_FILE);
    strcat(command, " 2>/dev/null");
    system(command);
    return fopen(RESULT_FIND_NAME_FILE, "r");
}







void find(char* pathBuffer, char* nameBuffer, char* typeBuffer, char* sizeBuffer){
    char command[150];
    createCommand(command, pathBuffer, nameBuffer, typeBuffer, sizeBuffer);
    addCommandInHistory(command);
    FILE* resultFind = sendCommand(command);
    outputResultFind(resultFind);
    fclose(resultFind);
    remove(RESULT_FIND_NAME_FILE);
}


