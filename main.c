#include "map.h"
#include "pso.h"
#include "Logger.h"
#include <string.h>
#include <time.h>


int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Blad: brak pliku mapy.\n");
        fprintf(stderr, "Uzycie: %s <plik_mapy> [-p N] [-i N] [-n N] [-c plik]\n", argv[0]);
        return 1;
    }

    FILE *fmap = fopen(argv[1], "r");
    if (!fmap) { // sprawdzenie czy plik mapy da sie otworzyc
        fprintf(stderr, "Blad: nie moge otworzyc pliku mapy: %s\n", argv[1]);
        return 1;
    }
    fclose(fmap);

    // Domyslne wartosci
    int p = 30;      // liczba czastek
    int iters = 100; // liczba iteracji
    int n = 0;       // co ile zapis (0 = nie zapisuj)
    const char *cfg = NULL;
    double parametry[5] = {0.5, 1, 0, 1, 0};
    srand((unsigned)time(NULL));


    // sprawdzenie flag jak są to musi byc wartosc
    for (int k = 2; k < argc; k++) {
        if (strcmp(argv[k], "-p") == 0) {
            if (k + 1 >= argc) {
                fprintf(stderr, "Blad: brakuje wartosci po -p\n");
                return 1;
            }

            char *end = NULL; // na czym strtol konczy czytac jak na koncu(\0) to jest git
            long v = strtol(argv[k + 1], &end, 10); // wartosc p musi byc liczba calk > 0
            if (end == argv[k + 1] || *end != '\0' || v <= 0) {
                fprintf(stderr, "Blad: -p wymaga liczby calkowitej > 0\n");
                return 1;
            }
            p = (int)v;
            k++;

        } else if (strcmp(argv[k], "-i") == 0) {
            if (k + 1 >= argc) {
                fprintf(stderr, "Blad: brakuje wartosci po -i\n");
                return 1;
            }

            char *end = NULL;
            long v = strtol(argv[k + 1], &end, 10);
            if (end == argv[k + 1] || *end != '\0' || v < 0) {
                fprintf(stderr, "Blad: -i wymaga liczby calkowitej >= 0\n");
                return 1;
            }
            iters = (int)v;
            k++;

        } else if (strcmp(argv[k], "-n") == 0) {
            if (k + 1 >= argc) {
                fprintf(stderr, "Blad: brakuje wartosci po -n\n");
                return 1;
            }

            char *end = NULL;
            long v = strtol(argv[k + 1], &end, 10);
            if (end == argv[k + 1] || *end != '\0' || v < 0) {
                fprintf(stderr, "Blad: -n wymaga liczby calkowitej >= 0\n");
                return 1;
            }
            n = (int)v;
            k++;

        } else if (strcmp(argv[k], "-c") == 0) {
            if (k + 1 >= argc) {
                fprintf(stderr, "Blad: brakuje sciezki po -c\n");
                return 1;
            }

            cfg = argv[k + 1];
            FILE *fcfg = fopen(cfg, "r");
            if (!fcfg) {
                fprintf(stderr, "Blad: nie moge otworzyc pliku konfiguracyjnego: %s\n", cfg);
                return 1;
            }
	    for(int h = 0; h<5; i++){
		fscanf(fcfg,"%lf",&parametry[h]);
	    }
	    srand((parametry[4]*1e6)^(parametry[2]*1e6)); // XOR z parametrów r1 r2 i stworzenie z tego seeda losowan inaczej nie widze sensu podania tych parametrów w pliku config
            fclose(fcfg);
            k++;

        } else {
            fprintf(stderr, "Blad: nieznany argument: %s\n", argv[k]);
            fprintf(stderr, "Uzycie: %s <plik_mapy> [-p N] [-i N] [-n N] [-c plik]\n", argv[0]);
            return 1;
        }
    }

    	printf("mapa=%s p=%d i=%d n=%d cfg=%s\n",argv[1], p, iters, n, cfg ? cfg : "(brak)"); // podglad
	int W,H;
	double** mapa = get_map(argv[1], &W, &H);
	Particle* roj = inicjalizacja_roju(mapa, W, H, p);
	GBest *gbest = inicjalizacja_gbest(roj, p);
	FILE *fsave = fopen("Zapis_iteracji.csv","w");
	for(int i = 1; i< iters+1; i++){
		PSO(mapa, W, H, roj, p, gbest, parametry);	
		if(i % n == 0 && n != 0){
			zapis(roj,gbest, fsave, n, p);
		}
	}
	fclose(fsave);
	free_roj(roj,gbest);
	free_map(mapa);
    	return 0;
}

