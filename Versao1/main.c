#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"

#define INTER 7

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges;
    int *sub, *melhorSub;
    Edge *edges;
    Grafo *grafo;
    Resultado *sol;
    int melhorCusto = INT_MAX;

    printf("Nome arquivo?");
    char arquivo[20];
    scanf("%s", arquivo);
    readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

    printf("k: %d\n", k);
    printf("Numero de vertices: %d\n", grafo->numVertices);
    printf("Numero de arestas: %d\n", grafo->numArestas);

    sub = geraSolucaoInicial(&k, &edges, &grafo);
    imprimirSubconjunto(sub, grafo->numVertices);
    melhorSub = malloc(grafo->numVertices * sizeof(int));
    memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

    for(int i = 0; i < INTER; i++){
        sol = Hill_Climbing_2(sub, grafo, &edges, &k);
        imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
        validateSoluction(sol, grafo, &edges, &k);
        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

        if (custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
        }

        memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
        free(sol);
    }

    printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
    imprimirSubconjunto(melhorSub, grafo->numVertices);

    free(edges);
    free(grafo);
    free(sub);
    return 0;
}