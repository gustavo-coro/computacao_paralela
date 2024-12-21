#include "../include/solver.h"

int count_common_neighbors(node* first_list, node* second_list, bool* visited) {
    int count = 0;

    for (node* temp = first_list; temp != NULL; temp = temp->next_vertex) {
        visited[temp->vertex] = true;
    }

    for (node* temp = second_list; temp != NULL; temp = temp->next_vertex) {
        if (visited[temp->vertex]) {
            count++;
        }
    }

    for (node* temp = first_list; temp != NULL; temp = temp->next_vertex) {
        visited[temp->vertex] = false;
    }

    return count;
}

void solver(graph* gph, char* file_path, int n_threads) {
    FILE* stream;
    stream = fopen(file_path, "w");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int n = gph->num_nodes;
    int** result = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        result[i] = calloc(n, sizeof(int));
    }

#pragma omp parallel num_threads(n_threads)
    {
        bool* visited = calloc(n, sizeof(bool));

#pragma omp for schedule(dynamic, 1)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int common_neighbors = count_common_neighbors(
                    gph->node_list[i], gph->node_list[j], visited);
                result[i][j] = common_neighbors;
            }
        }

        free(visited);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (result[i][j] != 0)
                fprintf(stream, "%d %d %d\n", i, j, result[i][j]);
        }
        free(result[i]);
    }
    free(result);

    fclose(stream);
}