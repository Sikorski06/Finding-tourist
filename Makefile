CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

APP = app
GEN = gen_map

# Domyślne wartości 
W ?= 10
H ?= 10
MAPFILE ?= mapa.txt

all: $(APP)

$(APP): main.o map.o pso.o Logger.o
	$(CC) $(CFLAGS) -o $(APP) main.o map.o pso.o Logger.o $(LDFLAGS)

main.o: main.c map.h pso.h Logger.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

pso.o: pso.c pso.h map.h
	$(CC) $(CFLAGS) -c pso.c

Logger.o: Logger.c Logger.h map.h
	$(CC) $(CFLAGS) -c Logger.c

# Generator mapy
$(GEN): gen_map.o
	$(CC) $(CFLAGS) -o $(GEN) gen_map.o $(LDFLAGS)

gen_map.o: gen_map.c
	$(CC) $(CFLAGS) -c gen_map.c

#Wygeneruj mapę

map: $(GEN)
	./$(GEN) $(W) $(H) $(MAPFILE)

# Workflow: zbuduj wszystko -> wygeneruj mapę -> uruchom app 

run: all map
	@echo "Mapa wygenerowana: $(MAPFILE)"
	@echo "Uruchamiam: ./$(APP) $(MAPFILE)"
	./$(APP) $(MAPFILE)

clean:
	rm -f *.o $(APP) $(GEN) $(MAPFILE)

#make
#make run W=7 H=7 MAPFILE=mapa.txt
