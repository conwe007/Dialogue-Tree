CC = gcc
CFLAGS = -Iinclude -Wall
LIBS = -lm

SRC = ./source/main.c ./source/dtree.c ./source/dgraph.c ./source/dnode.c ./source/dedge.c ./source/animate.c

TEST = ./test/test.c ./source/dtree.c ./source/dgraph.c ./source/dnode.c ./source/dedge.c

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o main

test: $(TEST)
	$(CC) $(TEST) $(CFLAGS) $(LIBS) -o main_test

.PHONY: clean

clean:
	rm main
	rm main_test