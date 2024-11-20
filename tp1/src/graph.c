#include "../include/graph.h"

edges* read_edges_from_file(char* file_path) {
    FILE* stream;
    char* line = NULL;
    size_t len = 0;

    stream = fopen(file_path, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int lines = 0;

    while ((getline(&line, &len, stream)) != -1) {
        lines++;
    }

    rewind(stream);

    edges* edg = (edges*)malloc(sizeof(edges) * lines);
    edg->num_edges = lines;

    int cont = 0;

    while ((getline(&line, &len, stream)) != -1) {
        int n;

        errno = 0;
        n = sscanf(line, "%d %d", &edg[cont].origin, &edg[cont].destiny);
        cont++;
        if (n != 2) {
            if (errno != 0) {
                perror("sscanf");
                exit(EXIT_FAILURE);
            } else {
                fprintf(stderr, "Error!\nNo matching characters\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(stream);
    free(line);

    return edg;
}

int* get_adjacency_matrix_from_edges(edges* edg, int* dimension) {
    int max_node = 0;

    for (int i = 0; i < edg->num_edges; i++) {
        if (edg[i].origin >= edg[i].destiny) {
            if (edg[i].origin >= max_node) {
                max_node = edg[i].origin;
                continue;
            }
        }
        if (edg[i].destiny >= max_node) {
            max_node = edg[i].destiny;
        }
    }

    max_node++;

    int* matrix = (int*)malloc(sizeof(int) * (max_node * max_node));

    for (int i = 0; i < (max_node * max_node); i++) {
        matrix[i] = 0;
    }

    for (int i = 0; i < edg->num_edges; i++) {
        int idx = edg[i].origin + edg[i].destiny * max_node;
        matrix[idx] = 1;
        idx = edg[i].destiny + edg[i].origin * max_node;
        matrix[idx] = 1;
    }

    *dimension = max_node;

    return matrix;
}