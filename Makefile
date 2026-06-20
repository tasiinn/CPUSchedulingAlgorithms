CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
SRC     = src/scheduling_algorithms.c
BIN     = scheduler

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
