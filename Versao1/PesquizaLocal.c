#include <stdio.h>
#include <stdlib.h>
#include "PesquisaLocal.h"

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges) {
    FILE *file = fopen(fileName, "rt");

    char type;
    int u, v, cost;

    if (file == NULL) {
        printf("[Erro] de abertura de ficheiro");
        exit(1);
    }

    fseek(file, sizeof(char), SEEK_SET);
    fscanf(file, "%d", k);

    fseek(file, sizeof(header), SEEK_SET);
    fscanf(file, "%d %d", numVertices, numEdges);

    *edges = (Edge *)malloc(sizeof(Edge) * (*numEdges));

    for (int i = 0; i < *numEdges; i++) {
        fscanf(file, " %c %d %d %d", &type, &u, &v, &cost);

        (*edges)[i].car = type;
        (*edges)[i].u = u;
        (*edges)[i].v = v;
        (*edges)[i].cost = cost;
    }
    fclose(file);
}