CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm
APP = pso
GEN = gen_map

# Domyślne wartości
W ?= 20
H ?= 20
MAPFILE = mapa.txt

.PHONY: all map clean #dzieki temu zawsze sa interpretowane jako komendy a nie pliki

all: map $(APP)
	@echo "Uruchom: ./$(APP) $(MAPFILE) -p 20 ..."

$(APP): main.o map.o pso.o logger.o
	$(CC) $(CFLAGS) -o $(APP) main.o map.o pso.o logger.o $(LDFLAGS)

main.o: main.c map.h pso.h logger.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

pso.o: pso.c pso.h
	$(CC) $(CFLAGS) -c pso.c

logger.o: logger.c logger.h pso.h
	$(CC) $(CFLAGS) -c logger.c

$(GEN): gen_map.o
	$(CC) $(CFLAGS) -o $(GEN) gen_map.o $(LDFLAGS)

gen_map.o: gen_map.c
	$(CC) $(CFLAGS) -c gen_map.c

#generowanie mapy
map: $(GEN)
	./$(GEN) $(W) $(H)
	@echo "Stworzono mape: $(MAPFILE) (W=$(W), H=$(H))"

clean:
	rm -f *.o $(APP) $(GEN) 
