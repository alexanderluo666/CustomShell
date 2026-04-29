CC=gcc
CFLAGS=-Wall -Wextra -O2

SRC=src/main.c
OUT=build/myshell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)