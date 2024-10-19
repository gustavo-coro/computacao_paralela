#include "../include/graph.h"

int* read_graph_from_file(char* file_path) {
    FILE* input_file = fopen(file_path, "r");

    int* graph;

    

    fclose(input_file);

    return graph;
}