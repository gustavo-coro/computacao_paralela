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
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = gph->num_nodes;
    int num_pairs = (n * (n - 1)) / 2;
    int num_pairs_process = num_pairs / size;
    int extra_pairs = num_pairs % size;

    int start =
        rank * num_pairs_process + (rank < extra_pairs ? rank : extra_pairs);
    int end = start + num_pairs_process + (rank < extra_pairs ? 1 : 0);

    pair* local_results = (pair*)malloc(sizeof(pair) * (end - start));

    int local_index = 0;
    int pair_index = 0;

#pragma omp parallel num_threads(n_threads)
    {
        bool* visited = calloc(n, sizeof(bool));

#pragma omp for schedule(dynamic, 1)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (pair_index >= start && pair_index < end) {
                    int common_neighbors = count_common_neighbors(
                        gph->node_list[i], gph->node_list[j], visited);
#pragma omp critical
                    {
                        local_results[local_index].count = common_neighbors;
                        local_results[local_index].dest = j;
                        local_results[local_index].src = i;
                        local_index++;
                    }
                }
                pair_index++;
                if (pair_index >= end) {
                    break;
                }
            }
        }

        free(visited);
    }

    pair* global_results = NULL;
    if (rank == 0) {
        global_results = (pair*)malloc(num_pairs * sizeof(pair));

        int idx = 0;
        for (; idx < local_index; idx++) {
            global_results[idx] = local_results[idx];
        }
        for (int i = 1; i < size; i++) {
            MPI_Status status;
            int s = i * num_pairs_process + (i < extra_pairs ? i : extra_pairs);
            int e = s + num_pairs_process + (i < extra_pairs ? 1 : 0);
            int recv_count = e - s;
            MPI_Recv(global_results + idx, recv_count * sizeof(pair), MPI_BYTE,
                     i, 0, MPI_COMM_WORLD, &status);
            idx += recv_count;
        }
    } else {
        MPI_Send(local_results, local_index * sizeof(pair), MPI_BYTE, 0, 0,
                 MPI_COMM_WORLD);
    }

    if (rank == 0) {
        FILE* stream = fopen(file_path, "w");
        if (stream == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < num_pairs; i++) {
            if (global_results[i].count != 0) {
                fprintf(stream, "%d %d %d\n", global_results[i].src,
                        global_results[i].dest, global_results[i].count);
            }
        }
        fclose(stream);
        free(global_results);
    }

    free(local_results);
}