#ifndef SOLVER_H
#define SOLVER_H

#include <mpi.h>
#include <omp.h>
#include <stdbool.h>

#include "graph.h"

typedef struct pair {
    int src, dest, count;
} pair;

int count_common_neighbors(node*, node*, bool*);
void solver(graph*, char*, int);

#endif