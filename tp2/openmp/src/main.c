#include <string.h>

#include "../include/graph.h"
#include "../include/solver.h"
#include "../include/time_management.h"

int main(int argc, char **argv) {
    if (argc != 4) {
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
    strcat(file_name, "parallel.cng");


    struct timeval time_start, time_end, time_diff;
    double execution_time;

    gettimeofday(&time_start, NULL);

    solver(gph, file_name, atoi(argv[3]));

    gettimeofday(&time_end, NULL);

    timeval_subtract(&time_diff, &time_end, &time_start);
    execution_time = joinTimes(time_diff.tv_sec, time_diff.tv_usec);

    printf("Execution time: %f seconds\n", execution_time / 1000000);

    fprintf(stream, "%lf;", execution_time / 1000000);
    fclose(stream);

    free_graph(gph);

    return EXIT_SUCCESS;
}