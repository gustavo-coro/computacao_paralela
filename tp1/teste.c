#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct graph
{
    int o, d;
};


int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int lines = 0;

    while ((nread = getline(&line, &len, stream)) != -1) {
        lines++;
    }

    printf("Lines = %d\n", lines);

    rewind(stream);

    struct graph *g = (struct graph*) malloc(sizeof(struct graph) * lines);

    int cont = 0;

    while ((nread = getline(&line, &len, stream)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);

        int n;

        errno = 0;
        n = sscanf(line, "%d %d", &g[cont].o, &g[cont].d);
        cont++;
        if (errno != 0) {
            perror("sscanf");
        } else {
            fprintf(stderr, "No matching characters\n");
        }
    }

    printf("Grafo = \n");
    for (int i = 0; i < lines; i++) {
        printf("v: %d %d\n", g[i].o, g[i].d);
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}