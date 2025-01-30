CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: server client

server: server.c eshop.h
	$(CC) $(CFLAGS) server.c -o server

client: client.c eshop.h
	$(CC) $(CFLAGS) client.c -o client

clean:
	rm -f server client
