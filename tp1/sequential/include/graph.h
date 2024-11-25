#ifndef GRAPH_H
#define GRAPH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edges {
    int src, dest;
} edges;

typedef struct node {
    int vertex;
    struct node* next_vertex;
} node;

typedef struct  graph {
    int num_nodes;
    node** node_list;
} graph;


node* create_new_node(int); // returns a new node
graph* create_graph(int); // returns a new graph
void add_edge(graph*, int, int); // add a new edge to the graph
graph* read_edges_from_file(char*);  // returns the graph from the file
void free_node_list(node*); // free allocated momory from node list
void free_graph(graph*); // free allocated memory from graph

#endif