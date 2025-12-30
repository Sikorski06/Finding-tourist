#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NOISE 1.0 //blad stohastyczny

double point_value(int x, int y, int xp, int yp, int R, double Smax){ //wartosc punktu na gorce
	double d = sqrt((x - xp)*(x - xp)+(y - yp)*(y - yp));
	if(d > R)
		return -1000.00;
	else{
		double u = (double)rand() / ((double)RAND_MAX + 1.0); // [0,1)
		double noise = (2.0 * u - 1.0) * NOISE;
		double val = Smax * (1.0 - d / (double)R) + noise;
		// nie robimy ujemnych gorek (tlo i tak jest -1000)
		if (val < 0.0) 
			val = 0.0;
		return val;
	}
}

int min(int a, int b){
	return a <= b ? a : b;
}

int max(int a, int b){
	return a>=b ? a:b;
}


int main(int argc, char** argv){
	if(argc < 3){
		fprintf(stderr,"Błąd: Podano zbyt małą ilość argumentów\n");
		fprintf(stderr, "Uzycie: %s W H\n", argv[0]);
		return 1;}

	if(argc > 3){
		fprintf(stderr,"Błąd: Podano zbyt dużą ilość argumentów\n");
		fprintf(stderr, "Uzycie: %s W H\n", argv[0]);
		return 1;}
	int W;
	if(atof(argv[1]) == atoi(argv[1])){
		W = atoi(argv[1]);}
	else{
		fprintf(stderr,"Błąd: Nie podano liczby całkowitej\n");
		return 1;}
	int H;
	if(atof(argv[2]) == atoi(argv[2])){
		H = atoi(argv[2]);}
	else{
		fprintf(stderr,"Błąd: Nie podano liczby całkowitej\n");
		return 1;
	}
	int Pole = W * H; // pole mapy
	int K = (ceil(Pole/150.0) > 6 ? 6 : (int)ceil(Pole/150.0));	// ile górek 
	int R = max(2, (int)ceil(min(W,H)/6.0));	// promień górki
	double mapa[H][W];
	for(int x =0; x < H; x++){
		for(int y = 0; y < W; y++){
			mapa[x][y] = -1000.00;
		}
	}
	int sx[K], sy[K];
	int min_dist = max(2, (int)ceil(min(W, H) / 6.0));
	int liczba_prob = 0;
	
	for(int i = 0; i<K; i++){
		int err =0;
		liczba_prob +=1;
		sx[i] = rand() % W;
		sy[i] = rand() % H;
		for(int j = i-1; j >= 0; j--){
			if(sqrt((sx[i] - sx[j])*(sx[i] - sx[j])+(sy[i] - sy[j])*(sy[i] - sy[j])) < min_dist){
				i--;
				err = 1;
				liczba_prob++;
				break;}
		}
		if (err) {
			if (liczba_prob > 15) {
				K = i + 1; // tyle udalo sie sensownie wylosowac
				break;
			}
			continue;
		}
		liczba_prob = 0;
	}

	double s_val[K];
	for(int i =0;i<K;i++){
		s_val[i] =  30.0 + (rand() % 7001) / 100.0 ;
	}

	for(int x =0; x < H; x++){
		for(int y = 0; y < W; y++){
			double best = -1000.00;
			for(int k = 0; k< K; k++){
				double v = point_value(x, y, sx[k], sy[k], R, s_val[k]);
				if (v > best) 
					best = v;
			}
			mapa[y][x] = best;
		}
	}


	return 0;
}
