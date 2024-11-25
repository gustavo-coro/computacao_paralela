#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random edge between two nodes
void generate_edge(int *u, int *v, int nodes) {
    *u = rand() % nodes;
    *v = rand() % nodes;

    // Ensure no self-loops
    while (*u == *v) {
        *v = rand() % nodes;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <number_of_nodes> <sparse|dense> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int nodes = atoi(argv[1]);
    if (nodes <= 0) {
        fprintf(stderr, "Error: Number of nodes must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    int sparse = strcmp(argv[2], "sparse") == 0 ? 1 : 0;
    const char *output_file = argv[3];

    // Open the output file
    FILE *file = fopen(output_file, "w");
    if (!file) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Determine the number of edges
    int max_edges = nodes * (nodes - 1) / 2; // Max edges in an undirected graph
    int edges = sparse ? nodes : max_edges / 2; // Sparse: ~n edges, Dense: ~n^2/2 edges

    // Generate edges
    for (int i = 0; i < edges; ++i) {
        int u, v;
        generate_edge(&u, &v, nodes);
        fprintf(file, "%d %d\n", u, v);
    }

    fclose(file);

    printf("Generated %s graph with %d nodes and %d edges in '%s'.\n",
           sparse ? "sparse" : "dense", nodes, edges, output_file);

    return EXIT_SUCCESS;
}
