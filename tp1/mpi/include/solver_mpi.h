#ifndef SOLVER_MPI_H
#define SOLVER_MPI_H

#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

#include "graph.h"

typedef struct pair {
    int src, dest, count;
} pair;


int count_common_neighbors_mpi(node*, node*, int);
void solver_mpi(graph*, char*);

#endif