#ifndef VERSAO1_PESQUISALOCAL_H
#define VERSAO1_PESQUISALOCAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char car;
    int u, v, cost, haveConection;
} Edge;

typedef struct {
    int numVertices;
    int numArestas;
} Grafo;

typedef struct {
    int *melhorSolucao;
    int *melhorSolucao2;
} Resultado;

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges, Grafo **grafo);
void imprimirSubconjunto(int* subconjunto, int tamanho);
int* geraSolucaoInicial(int *k, Edge **edges, Grafo **grafo);
Resultado* Hill_Climbing(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k);
int validateSoluction(int *melhorSolucao, Grafo *grafo, Edge **edges, int *k);
int *generates_neighbor_2(int *solucaoInicial, Grafo *grafo, Edge **edges);
int *generates_neighbor_1(int *solucaoInicial, Grafo *grafo, Edge **edges);
int calculaCustoTotal(int *solucao, Edge **edges, int numArestas);

#endif //VERSAO1_PESQUISALOCAL_H