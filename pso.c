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
        roj[i].x  = (double)((rand() % ((W-1) * 100 + 1)) / 100.0);  
	roj[i].y  = (double)((rand() % ((H-1) * 100 + 1)) / 100.0);
        roj[i].vx = ((double)rand() / RAND_MAX - 0.5); 
        roj[i].vy = ((double)rand() / RAND_MAX - 0.5);
        roj[i].fit = fitness(mapa, W, H, roj[i].x, roj[i].y);
        roj[i].pbest_x = roj[i].x;
        roj[i].pbest_y = roj[i].y;
        roj[i].pbest_val = roj[i].fit;
    }

    return roj;
}


GBest *inicjalizacja_gbest(Particle *roj, int n){
    GBest *g = malloc(sizeof(GBest));
    if (!g) 
	    return NULL;    
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
	double w  = config[0];
	double c1 = config[1];
	double c2 = config[3];
	double R1 = config[2];  
	double R2 = config[4];  

	for(int i = 0; i < n; i++){
		double r1 = R1 * ((double)rand() / ((double)RAND_MAX + 1.0));
		double r2 = R2 * ((double)rand() / ((double)RAND_MAX + 1.0));
		roj[i].vx = (w*roj[i].vx) + c1 * r1 * (roj[i].pbest_x - roj[i].x) + c2 * r2 * (gbest->x - roj[i].x);
		roj[i].vy = (w*roj[i].vy) + c1 * r1 * (roj[i].pbest_y - roj[i].y) + c2 * r2 * (gbest->y - roj[i].y);
		roj[i].x += roj[i].vx;
		roj[i].y += roj[i].vy;
		
		double maxX = (double)(W - 1);
		double maxY = (double)(H - 1);
		if (roj[i].x < 0.0) {	//Odbicie od krawedzi 
    			roj[i].x  = -roj[i].x;
    			roj[i].vx = -roj[i].vx;
		} 
		else if (roj[i].x > maxX) {
    			roj[i].x  = 2.0 * maxX - roj[i].x;
    			roj[i].vx = -roj[i].vx;
		}
		if (roj[i].y < 0.0) {
    			roj[i].y  = -roj[i].y;
    			roj[i].vy = -roj[i].vy;
		} 
		else if (roj[i].y > maxY) {
    			roj[i].y  = 2.0 * maxY - roj[i].y;
    			roj[i].vy = -roj[i].vy;
		}

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

