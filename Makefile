# Компилятор
CC=gcc
# Флаги компиляции
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
# Библиотеки
LIBS=-lncurses

# Исходные файлы
SOURCES=main.c printGUI.c createFindCommand.c workWithHistory.c
# Заголовочные файлы
HEADERS=header.h printGUI.h createFindCommand.h workWithHistory.h

# Имя исполняемого файла
EXECUTABLE=myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(LIBS) $(SOURCES) -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

