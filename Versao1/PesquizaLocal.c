#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PesquisaLocal.h"

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges, Grafo **grafo) {
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

    (*grafo)->numVertices = *numVertices;
    (*grafo)->numArestas = *numEdges;

    fclose(file);
}

void imprimirSubconjunto(int* subconjunto, int tamanho) {
    printf("Subconjunto de vertices: ");
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", subconjunto[i]);
    }
    printf("\n");
}

int calculaCustoTotal(int *solucao, Edge **edges, int numArestas) {
    int custoTotal = 0;

    for (int i = 0; i < numArestas; ++i) {
        int pos1 = (*edges)[i].u - 1, pos2 = (*edges)[i].v - 1;

        if (solucao[pos1] == 1 && solucao[pos2] == 1) {
            custoTotal += (*edges)[i].cost;
        }
    }

    return custoTotal;
}

int* geraSolucaoInicial(int *k, Edge **edges, Grafo **grafo){
    int tam = (*grafo)->numVertices;
    int *solucaoInicial = (int*)malloc(tam * sizeof(int));

    for (int i = 0; i < tam; ++i) {
        solucaoInicial[i] = 0;
    }

    srand(time(NULL));
    int custoTotal = 0;
    int numeroAleatorio = rand() % 3;

    for (int i = numeroAleatorio; i < (*grafo)->numArestas; ++i) {
        int pos1 = (*edges)[i].u - 1, pos2 = (*edges)[i].v - 1;
        solucaoInicial[pos1] = 1;
        solucaoInicial[pos2] = 1;

        custoTotal = calculaCustoTotal(solucaoInicial, edges, (*grafo)->numArestas);

        int contador = 0;
        for (int j = 0; j < tam; ++j) {
            if (solucaoInicial[j] == 1) {
                contador++;
            }
        }

        if (contador == *k) {
            printf("Custo total = %d\n", custoTotal);
            return solucaoInicial;
        }
    }

    free(solucaoInicial);
    return NULL;
}

void trepa_colinas(int *k,Edge **edges){

}