#ifndef GRAPH_H
#define GRAPH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edges {
    int origin, destiny, num_edges;
} edges;

edges* read_edges_from_file(char*);  // returns the edges from the file
int* get_adjacency_matrix_from_edges(edges*,
                                     int*);  // returns the graph as an 1D array

#endif