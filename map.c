#include "map.h"	


double **get_map(const char *file, int *W_out, int *H_out) {
	FILE *fptr = fopen(file, "r");
	if (!fptr) {
   		perror("fopen");
    		return NULL;
	}
	int W, H;

    	if (fscanf(fptr, "%d %d", &W, &H) != 2 || W <= 0 || H <= 0) {
        	fprintf(stderr, "Blad: niepoprawny naglowek mapy\n");
        	fclose(fptr);
        	return NULL;
    	}

    	double **mapa = malloc(H * sizeof(double *));
    	double *data  = malloc(W * H * sizeof(double));

    	if (!mapa || !data) {
		fprintf(stderr,"Błąd przy użyciu funkcji malloc");
        	free(mapa);
        	free(data);
        	fclose(fptr);
        	return NULL;
    	}

      	for (int y = 0; y < H; y++) {
        	mapa[y] = data + y * W;
    	}

    	for (int y = 0; y < H; y++) { // wczytanie danych
        	for (int x = 0; x < W; x++) {
            		if (fscanf(fptr, "%lf", &mapa[y][x]) != 1) {
                		fprintf(stderr, "Blad: za malo danych w pliku mapy\n");
                		fclose(fptr);
                		free(data);
                		free(mapa);
                		return NULL;
            		}
        	}
    	}

    	fclose(fptr);
	*W_out = W;
    	*H_out = H;
    	return mapa;
}

void free_map(double **mapa) {
    if (!mapa) 
	    return;
    free(mapa[0]);
    free(mapa);
}	
