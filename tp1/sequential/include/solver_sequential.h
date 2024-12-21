#ifndef SOLVER_SEQUENTIAL_H
#define SOLVER_SEQUENTIAL_H

#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int count_common_neighbors(node*, node*, bool*);
void solver(graph*, char*);

#endif