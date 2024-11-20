#include "../include/graph.h"
#include "../include/solver_sequential.h"
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // get the path of the exit file
    char* file_name = argv[1];
    strtok(file_name, ".");
    strcat(file_name, ".cng");

    graph* gph = read_edges_from_file(argv[1]);

    solver(gph, file_name);

    free_graph(gph);

    return EXIT_SUCCESS;
}