# Makefile

CC = gcc
CFLAGS = -Wall -Wextra

TARGET = a3

SRC = main.c init.c evidence.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

