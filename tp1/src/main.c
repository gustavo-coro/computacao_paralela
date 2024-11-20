#include "../include/graph.h"
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    edges* edg = read_edges_from_file(argv[1]);

    for (int i = 0; i < edg->num_edges; i++) {
        printf("%d %d\n", edg[i].origin, edg[i].destiny);
    }

    int dimension;
    int* matrix = get_adjacency_matrix_from_edges(edg, &dimension);

    printf("%d\n", matrix[0]);

    char* file_name = argv[1];
    strtok(file_name, ".");
    strcat(file_name, ".cng");

    printf("%s\n", file_name);

    free(edg);
    free(matrix);

    return EXIT_SUCCESS;
}