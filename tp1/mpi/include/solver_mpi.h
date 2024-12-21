#ifndef SOLVER_MPI_H
#define SOLVER_MPI_H

#include <mpi.h>
#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"

typedef struct pair {
    int src, dest, count;
} pair;

int count_common_neighbors(node*, node*, bool*);
void solver_mpi(graph*, char*);

#endif