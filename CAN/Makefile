CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = can_demo

SRC = src/can_mock.c examples/main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)