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

    fscanf(file, "%*s %d %*s %*s %d %d", k, numVertices, numEdges);

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

// Função para imprimir o subconjunto de vértices
void imprimirSubconjunto(int* subconjunto, int tamanho) {
    printf("Subconjunto de vertices: ");
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", subconjunto[i]);
    }
    printf("\n");
}
