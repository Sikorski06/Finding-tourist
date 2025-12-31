#ifndef PSO_H
#define PSO_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Particle{
    double x;
    double y;
    double vx;
    double vy;

    double pbest_x;
    double pbest_y;
    double pbest_val;

    double fit;
} Particle;


typedef struct GBest{
    double x;
    double y;
    double val;
} GBest;



double fitness(double **mapa, int W, int H, double x, double y);


Particle *inicjalizacja_roju(double **mapa, int W, int H, int n);


GBest *inicjalizacja_gbest(Particle *roj, int n);


void PSO(double** mapa, int W, int H, Particle* roj, int n, GBest *gbest,double* config);


void free_roj(Particle *roj, GBest *gbest);

#endif
