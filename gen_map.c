#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NOISE 1.0 //blad stohastyczny

double point_value(int x, int y, int xp, int yp, int R, double Smax){ //wartosc punktu na gorce
	double d = sqrt((x - xp)*(x - xp)+(y - yp)*(y - yp));
	if(d > R)
		return -1000.00;
	else{
		double val = Smax * (1 - d/(double)R) - NOISE + 2*(rand() % 10)/(NOISE*10);
	}
	return val;
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
	int K = (ceil(Pole/150) > 6 ? 6 : (int)ceil(Pole/150));	// ile górek 
	int R = max(2, (int)ceil(min(W,H)/6));	// promień górki
	double Smax = 30.0 + (rand() % 7001) / 100.0 ;	// max sygnal
}
