#include <string.h>
#include <time.h>

#include "../include/graph.h"
#include "../include/solver_sequential.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* stream = fopen(argv[2], "a+");
    
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    graph *gph = read_edges_from_file(argv[1]);

    // get the path of the exit file
    char *file_name = argv[1];
    strtok(file_name, ".");
    strcat(file_name, "sequential.cng");

    clock_t start_time = clock();

    solver(gph, file_name);

    clock_t end_time = clock();

    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Execution time: %f seconds\n", execution_time);

    fprintf(stream, "%lf;", execution_time);
    fclose(stream);

    free_graph(gph);

    return EXIT_SUCCESS;
}