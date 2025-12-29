#include "map.h"
#include "gen_map.h"
#include "pso.h"
#include "Logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
            fclose(fcfg);
            k++;

        } else {
            fprintf(stderr, "Blad: nieznany argument: %s\n", argv[k]);
            fprintf(stderr, "Uzycie: %s <plik_mapy> [-p N] [-i N] [-n N] [-c plik]\n", argv[0]);
            return 1;
        }
    }

    printf("mapa=%s p=%d i=%d n=%d cfg=%s\n",argv[1], p, iters, n, cfg ? cfg : "(brak)"); // podglad

    return 0;
}

