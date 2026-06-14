CC=gcc
CFLAGS=$(shell pkg-config --cflags raylib)
LDFLAGS=$(shell pkg-config --libs raylib)

all:
	$(CC) main.c -o spiel $(CFLAGS) $(LDFLAGS) -lm

run: all
	./spiel
	rm spiel