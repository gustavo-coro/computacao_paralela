#include <string.h>

#include "../include/graph.h"
#include "../include/solver_mpi.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    graph* gph = read_edges_from_file(argv[1]);

    // get the path of the exit file
    char* file_name = argv[1];
    strtok(file_name, ".");
    strcat(file_name, "mpi.cng");

    MPI_Init(&argc, &argv);

    double start_time = MPI_Wtime();

    solver_mpi(gph, file_name);

    double end_time = MPI_Wtime();

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        FILE* stream = fopen(argv[2], "a+");
        if (stream == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        double execution_time = (end_time - start_time);
        printf("Execution time: %f seconds\n", execution_time);
        fprintf(stream, "%lf;", execution_time);
        fclose(stream);
    }

    MPI_Finalize();

    free_graph(gph);

    return EXIT_SUCCESS;
}