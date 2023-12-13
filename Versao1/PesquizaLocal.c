#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

    *grafo = (Grafo *)malloc(sizeof(Grafo));  // Allocate memory for Grafo structure
    (*grafo)->numVertices = *numVertices;
    (*grafo)->numArestas = *numEdges;

    fclose(file);
}

void imprimirSubconjunto(int *subconjunto, int tamanho) {
    printf("Vertices: ");
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

int *geraSolucaoInicial(int *k, Edge **edges, Grafo **grafo) {
    int tam = (*grafo)->numVertices;
    int *solucaoInicial = (int *)malloc(tam * sizeof(int));

    for (int i = 0; i < tam; ++i) {
        solucaoInicial[i] = 0;
    }

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
            printf("Custo solucao inicial = %d\n", custoTotal);
            return solucaoInicial;
        }
    }

    free(solucaoInicial);
    return NULL;
}

int *generates_neighbor_2(int *solucaoInicial, Grafo *grafo) {
    int *neighbor2 = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(neighbor2, solucaoInicial, grafo->numVertices * sizeof(int));

    int random_neighbor1 = rand() % grafo->numVertices;
    int random_neighbor2;
    do {
        random_neighbor2 = rand() % grafo->numVertices;
    } while (random_neighbor2 == random_neighbor1);

    int temp = neighbor2[random_neighbor1];
    neighbor2[random_neighbor1] = neighbor2[random_neighbor2];
    neighbor2[random_neighbor2] = temp;

    return neighbor2;
}


int *generates_neighbor_1(int *solucaoInicial, Grafo *grafo) {
    int *neighbor1 = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(neighbor1, solucaoInicial, grafo->numVertices * sizeof(int));

    int pos1 = rand() % grafo->numVertices;
    int pos2;
    do {
        pos2 = rand() % grafo->numVertices;
    } while (pos2 == pos1); // Garantindo que pos2 seja diferente de pos1

    // Trocando os valores
    int temp = neighbor1[pos1];
    neighbor1[pos1] = neighbor1[pos2];
    neighbor1[pos2] = temp;

    return neighbor1;
}

Resultado* Hill_Climbing(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k) {
    Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
    int melhorCusto = calculaCustoTotal(solucaoInicial, edges, grafo->numArestas);
    resultado->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->melhorSolucao2 = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(resultado->melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int nextCost = 0, cosPreview = 0;

    do {
        int *solucaoFinal = generates_neighbor_1(resultado->melhorSolucao, grafo);
        nextCost = calculaCustoTotal(solucaoFinal, edges, grafo->numArestas);

        if (nextCost < melhorCusto) {
            cosPreview = melhorCusto;
            resultado->melhorSolucao2 = resultado->melhorSolucao;
            melhorCusto = nextCost;
            free(resultado->melhorSolucao);
            resultado->melhorSolucao = solucaoFinal;
        } else {
            free(solucaoFinal);
        }
    } while (melhorCusto < nextCost);

    printf("Custo solucao Final = %d\n", melhorCusto);

    return resultado;
}

Resultado* Hill_Climbing_2(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k){
    Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
    int melhorCusto = calculaCustoTotal(solucaoInicial, edges, grafo->numArestas);
    resultado->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->melhorSolucao2 = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(resultado->melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int nextCost = 0, cosPreview = 0;

    do {
        int *solucaoFinal = generates_neighbor_2(resultado->melhorSolucao, grafo);
        nextCost = calculaCustoTotal(solucaoFinal, edges, grafo->numArestas);

        if (nextCost < melhorCusto) {
            cosPreview = melhorCusto;
            resultado->melhorSolucao2 = resultado->melhorSolucao;
            melhorCusto = nextCost;
            free(resultado->melhorSolucao);
            resultado->melhorSolucao = solucaoFinal;
        } else {
            free(solucaoFinal);
        }
    } while (melhorCusto < nextCost);

    printf("Custo solucao Final = %d\n", melhorCusto);

    return resultado;
}

int validateSoluction(int *melhorSolucao, Grafo *grafo, Edge **edges, int *k) {
    int tam = grafo->numArestas, contador = 0;
    int vetor_comparacao[*k][2];

    for (int i = 0; i < tam; ++i) {
        if (melhorSolucao[i] == 1) {
            contador++;
            if (i >= grafo->numVertices) {
                printf("Solucao Invalida\n");
                return 0;
            }
        }
    }

    if (contador != *k) {
        printf("Solucao Invalida\n");
        return 0;
    }

    printf("Solucao valida\n");
    return 1;
}

int* reparacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k){
    while ((validateSoluction(melhorSolucao, grafo, edges, k) != 1)){
        melhorSolucao = generates_neighbor_2(melhorSolucao, grafo);
    }
    return melhorSolucao;
}

Penalizacao penalizacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k){
    Penalizacao *p = (Penalizacao *)malloc(sizeof(Penalizacao));
    p->melhorsolucao = melhorSolucao;
    p->cost = 10000;
    return *p;
}