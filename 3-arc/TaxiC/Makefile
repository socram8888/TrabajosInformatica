
CC=gcc
CFLAGS=-std=c99 -Wall $(COPT)

all: server client

clean:
	$(RM) server server.exe
	$(RM) client client.exe
	$(RM) *.o

server: server.o connection.o packet.o select.o
	$(CC) $(CFLAGS) -pthread server.o connection.o packet.o select.o -o server

client: client.o connection.o packet.o select.o
	$(CC) $(CFLAGS) -pthread client.o connection.o packet.o select.o -o client

server.o: server.c packet.h connection.h
	$(CC) $(CFLAGS) -c server.c

client.o: client.c packet.h connection.h
	$(CC) $(CFLAGS) -c client.c

connection.o: packet.h connection.h connection.c select.h
	$(CC) $(CFLAGS) -c connection.c

packet.o: packet.h packet.c
	$(CC) $(CFLAGS) -c packet.c

select.o: select.h select.c
	$(CC) $(CFLAGS) -c select.c
