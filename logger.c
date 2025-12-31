#include "logger.h"
#include "pso.h"


void zapis(Particle *roj, GBest *gbest, FILE *fptr, int iter, int n_particles){
    for (int i = 0; i < n_particles; i++) {
        fprintf(fptr,"%d;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",iter,i,roj[i].x,roj[i].y,roj[i].fit,roj[i].pbest_val,gbest->x,gbest->y,gbest->val);
    }
}

