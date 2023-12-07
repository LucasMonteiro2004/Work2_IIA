#ifndef VERSAO1_PESQUISALOCAL_H
#define VERSAO1_PESQUISALOCAL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char car;
    int u, v, cost, haveConection;
} Edge;

typedef struct {
    int numVertices;
    int numArestas;
} Grafo;

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges, Grafo **grafo);
void imprimirSubconjunto(int* subconjunto, int tamanho);
int* geraSolucaoInicial(int *k, Edge **edges, Grafo **grafo);
int* Hill_Climbing(int *solucaoInicial, Grafo *grafo, Edge **edges);
int validateSoluction(int *melhorSolucao, Grafo *grafo, Edge **edges, int *k);
int *generates_neighbor_2(int *solucaoInicial, Grafo *grafo, Edge **edges);
int *generates_neighbor_1(int *solucaoInicial, Grafo *grafo, Edge **edges);

#endif //VERSAO1_PESQUISALOCAL_H