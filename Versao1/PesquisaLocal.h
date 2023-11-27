#ifndef VERSAO1_PESQUISALOCAL_H
#define VERSAO1_PESQUISALOCAL_H

#include <stdio.h>
#include <stdlib.h>

//estrutura das arestas
typedef struct {
    char car;
    int u, v, cost;
} Edge;

typedef struct {
    int numVertices;
    int numArestas;
    Edge* arestas;
} Grafo;

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges);

#endif //VERSAO1_PESQUISALOCAL_H
