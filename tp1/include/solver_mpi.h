#ifndef SOLVER_SEQUENTIAL_H
#define SOLVER_SEQUENTIAL_H

#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#include "graph.h"

int count_common_neighbors(node*, node*, int);
void solver(graph*, char*);

#endif