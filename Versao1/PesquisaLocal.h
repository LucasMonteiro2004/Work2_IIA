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
    int *solucaoInicial;
    int custo_melhor_solucao;
} Resultado;

typedef struct {
    int* melhorsolucao;
    int cost;
}Penalizacao;

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges, Grafo **grafo);
void imprimirSubconjunto(int* subconjunto, int tamanho);
int* geraSolucaoInicial(int k, Edge **edges, Grafo **grafo);
Resultado* Hill_Climbing(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k);
Resultado* Hill_Climbing_2(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k);
int validateSoluction(Resultado *resultado, Grafo *grafo, Edge **edges, int *k);
int *generates_neighbor_2(int *solucaoInicial, Grafo *grafo);
int *generates_neighbor_1(int *solucaoInicial, Grafo *grafo);
int calculaCustoTotal(int *solucao, Edge **edges, int numArestas);
Penalizacao penalizacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k);
int* reparacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k);

#endif //VERSAO1_PESQUISALOCAL_H