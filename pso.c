#include "pso.h"


double fitness(double **mapa, int W, int H, double x, double y){
    int ix = (int)round(x);
    int iy = (int)round(y);

    if(ix < 0 || ix > W-1 || iy < 0 || iy > H-1)
        return -6767.67;   // kara poza mapą    
    return mapa[iy][ix]; 
}


Particle *inicjalizacja_roju(double **mapa, int W, int H, int n) {
    Particle *roj = malloc(n * sizeof(Particle));
    
    if (!roj)
        return NULL;

    for(int i = 0; i < n; i++){
        roj[i].x  = (rand() % ((W-1) * 100 + 1)) / 100.0;  
	roj[i].y  = (rand() % ((H-1) * 100 + 1)) / 100.0;
        roj[i].vx = 0.0;
        roj[i].vy = 0.0;
        roj[i].fit = fitness(mapa, W, H, roj[i].x, roj[i].y);
        roj[i].pbest_x = roj[i].x;
        roj[i].pbest_y = roj[i].y;
        roj[i].pbest_val = roj[i].fit;
    }

    return roj;
}


GBest *inicjalizacja_gbest(Particle *roj, int n){
    GBest *g = malloc(sizeof(GBest));
    g->x = roj[0].pbest_x;
    g->y = roj[0].pbest_y;
    g->val = roj[0].pbest_val;

    for(int i = 1; i < n; i++){
        if(roj[i].pbest_val > g->val){
            g->val = roj[i].pbest_val;
            g->x = roj[i].pbest_x;
            g->y = roj[i].pbest_y;
        }
    }
    return g;
}


void PSO(double** mapa, int W, int H, Particle* roj, int n, GBest *gbest,double* config){
	double r1,r2;
	double w = config[0];
	double c1 = config[1];
	double c2 = config[3];
	for(int i = 0; i < n; i++){
		r1 = (double)rand() / (double)RAND_MAX;
		r2 = (double)rand() / (double)RAND_MAX;
		roj[i].vx = (w*roj[i].vx) + c1 * r1 * (roj[i].pbest_x - roj[i].x) + c2 * r2 * (gbest->x - roj[i].x);
		roj[i].vy = (w*roj[i].vy) + c1 * r1 * (roj[i].pbest_y - roj[i].y) + c2 * r2 * (gbest->y - roj[i].y);
		roj[i].x += roj[i].vx;
		roj[i].y += roj[i].vy;
		if (roj[i].x < 0.0) 
			roj[i].x = 0.0;
		if (roj[i].x > (double)(W - 1)) 
			roj[i].x = (double)(W - 1);
		if (roj[i].y < 0.0) 
			roj[i].y = 0.0;
		if (roj[i].y > (double)(H - 1)) 
			roj[i].y = (double)(H - 1);

		roj[i].fit = fitness(mapa, W, H, roj[i].x, roj[i].y);
		if(roj[i].fit > roj[i].pbest_val){
			roj[i].pbest_x = roj[i].x;
			roj[i].pbest_y = roj[i].y;
			roj[i].pbest_val = roj[i].fit;
			if(roj[i].pbest_val > gbest->val){
				gbest->val = roj[i].pbest_val;
				gbest->x = roj[i].x;
				gbest->y = roj[i].y;
			}
		}
	}
}



void free_roj(Particle *roj, GBest *gbest){
    free(roj);
    free(gbest);
}

