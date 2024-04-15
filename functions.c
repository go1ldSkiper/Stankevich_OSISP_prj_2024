#include "header.h"
#include <stdio.h>


const char RESULT_FIND_NAME_FILE[] = "tempResultFind.txt";
const char HISTORY_REQUEST_NAME_FILE[] = "historyRequest.txt";
const char HELP_NAME_FILE[] = "help.txt";


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


FILE* deleteLineInFile(FILE* oldDiscript, const char* fileName, int numberLineToDelete){
    fclose(oldDiscript);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    FILE *tempFile = fopen("temp.txt", "w+");
    char buffer[1024];
    int lineNum = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (lineNum != numberLineToDelete) {
            fputs(buffer, tempFile);
        }
        lineNum++;
    }

    fclose(file);
    fclose(tempFile);

    // Удаляем исходный файл
    if (remove(fileName) != 0) {
        perror("Ошибка удаления исходного файла");
        exit(EXIT_FAILURE);
    }

    // Переименовываем временный файл в исходный
    if (rename("temp.txt", fileName) != 0) {
        perror("Ошибка переименования временного файла");
        exit(EXIT_FAILURE);
    }
    return fopen(fileName, "r+");
}

void addCommandInHistory(char* command){
    FILE *file = fopen(HISTORY_REQUEST_NAME_FILE, "r+");
    if (file == NULL) {
        // Попробуем создать новый файл для записи
        file = fopen(HISTORY_REQUEST_NAME_FILE, "w+");
    }
    FILE *tempFile = fopen("temp.txt", "w+");
    // Пишем строку для вставки в начале файла
    fprintf(tempFile, "%s\n", command);
    // Копируем содержимое исходного файла во временный файл
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        fprintf(tempFile, "%s", buffer);
    }
    fclose(file);
    fclose(tempFile);
    // Заменяем исходный файл временным файлом
    remove(HISTORY_REQUEST_NAME_FILE);
    rename("temp.txt", HISTORY_REQUEST_NAME_FILE);
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


void searchFromHistory(FILE* file, int currentLine){
    char buffer[255];
    fseek(file, 0, 0);
    for(int i = 0; i < currentLine; i++)       // Считал все до курент лайн
        fgets(buffer, 255, file);
    fgets(buffer, 255, file);   // содержит нужную команду 
    int i = 0;
    for (i = 0; buffer[i] != '\n'; i++);    // убираю \n в конце
    buffer[i] = ' ';
    FILE* resultFind = sendCommand(buffer);
    outputResultFind(resultFind);
}