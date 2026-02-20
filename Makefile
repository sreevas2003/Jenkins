CC=gcc
CFLAGS=-I./src

all: app

app:
	$(CC) src/main.c src/add.c -o app $(CFLAGS)

clean:
	rm -f app
