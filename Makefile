CC = gcc
CFLAGS = -Wall -g

app: main.o map.o pso.o logger.o
	$(CC) $(CFLAGS) -o app main.o map.o pso.o logger.o

main.o: main.c map.o pso.o logger.o
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

pso.o: pso.c pso.h map.h
	$(CC) $(CFLAGS) -c pso.c

logger.o: logger.c logger.h map.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f *.o app
