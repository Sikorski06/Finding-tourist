#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include <stdio.h>


double **get_map(const char *file, int *W_out, int *H_out);


void free_map(double **mapa);

#endif
