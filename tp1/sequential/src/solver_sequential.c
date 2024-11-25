#include "../include/solver_sequential.h"

int count_common_neighbors(node* first_list, node* second_list,
                           int numVertices) {
    bool* visited = calloc(numVertices, sizeof(bool));
    int count = 0;

    for (node* temp = first_list; temp != NULL; temp = temp->next_vertex) {
        visited[temp->vertex] = true;
    }

    for (node* temp = second_list; temp != NULL; temp = temp->next_vertex) {
        if (visited[temp->vertex]) {
            count++;
        }
    }

    free(visited);

    return count;
}

void solver(graph* gph, char* file_path) {
    FILE* stream;
    stream = fopen(file_path, "w");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < gph->num_nodes; i++) {
        for (int j = i + 1; j < gph->num_nodes; j++) {
            int common_neighbors = count_common_neighbors(
                gph->node_list[i], gph->node_list[j], gph->num_nodes);
            if (common_neighbors != 0) {
                fprintf(stream, "%d %d %d\n", i, j, common_neighbors);
            }
        }
    }

    fclose(stream);
}