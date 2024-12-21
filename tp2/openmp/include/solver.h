#ifndef SOLVER_H
#define SOLVER_H

#include <omp.h>
#include <stdbool.h>

#include "graph.h"

int count_common_neighbors(node*, node*, bool*);
void solver(graph*, char*, int);

#endif