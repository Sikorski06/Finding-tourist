#include "logger.h"
#include "pso.h"


void zapis(Particle* roj,GBest *gbest, FILE* fptr, int n, int roj_n){
	fprintf(fptr,"%d\n", n);
	for(int i = 0; i < roj_n; i++){
		fprintf(fptr,"Dron nr.%d x= %.2lf  y= %.2lf\n",i,roj[i].x, roj[i].y);
	}
	fprintf(fptr,"Najlepsza dotychczas znana pozycja roju: x= %.2lf  y= %.2lf\n\n",gbest->x, gbest->y);
}
