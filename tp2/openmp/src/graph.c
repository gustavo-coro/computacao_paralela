#include "../include/graph.h"

node* create_new_node(int vertex) {
    node* v = (node*)malloc(sizeof(node));
    v->vertex = vertex;
    v->next_vertex = NULL;
    return v;
}

graph* create_graph(int number_of_nodes) {
    graph* g = (graph*)malloc(sizeof(graph));
    g->num_nodes = number_of_nodes;
    g->node_list = (node**)malloc(sizeof(node*) * number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++) {
        g->node_list[i] = NULL;
    }
    return g;
}

void add_edge(graph* gph, int src, int dest) {
    node* new_node = create_new_node(dest);
    new_node->next_vertex = gph->node_list[src];
    gph->node_list[src] = new_node;

    new_node = create_new_node(src);
    new_node->next_vertex = gph->node_list[dest];
    gph->node_list[dest] = new_node;
}

graph* read_edges_from_file(char* file_path) {
    FILE* stream;
    char* line = NULL;
    size_t len = 0;

    stream = fopen(file_path, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // count the number of edges in the file
    int lines = 0;

    while ((getline(&line, &len, stream)) != -1) {
        lines++;
    }

    rewind(stream);

    edges* edg = (edges*)malloc(sizeof(edges) * lines);

    // read the edges in the file
    int cont = 0;
    while ((getline(&line, &len, stream)) != -1) {
        int n;

        errno = 0;
        n = sscanf(line, "%d %d", &edg[cont].src, &edg[cont].dest);
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

    // find the number of nodes in the graph
    int max_node = 0;

    for (int i = 0; i < lines; i++) {
        if (edg[i].src >= edg[i].dest) {
            if (edg[i].src >= max_node) {
                max_node = edg[i].src;
                continue;
            }
        }
        if (edg[i].dest >= max_node) {
            max_node = edg[i].dest;
        }
    }

    max_node++;

    // create the graph with adjacency list
    graph* g = create_graph(max_node);

    for (int i = 0; i < lines; i++) {
        add_edge(g, edg[i].src, edg[i].dest);
    }

    free(edg);

    return g;
}

void free_node_list(node* head) {
    node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next_vertex;
        free(temp);
    }
}

void free_graph(graph* gph) {
    if (gph == NULL) return;

    for (int i = 0; i < gph->num_nodes; i++) {
        free_node_list(gph->node_list[i]);
    }
    free(gph->node_list);
    free(gph);
}