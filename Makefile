CC = gcc
CFLAGS = -Wall -g

app: main.o map.o pso.o Logger.o
	$(CC) $(CFLAGS) -o app main.o map.o pso.o Logger.o

main.o: main.c map.o pso.o Logger.o
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

pso.o: pso.c pso.h map.h
	$(CC) $(CFLAGS) -c pso.c

Logger.o: Logger.c Logger.h map.h
	$(CC) $(CFLAGS) -c Logger.c

clean:
	rm -f *.o app
