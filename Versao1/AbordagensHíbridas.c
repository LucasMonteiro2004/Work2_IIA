#include "AbordagensHíbridas.h"

int* Hibrido(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo, Edge** edges, int* k, int interacoes){
    int *melhorSub;
    Resultado *sol;
    int melhorCusto = INT_MAX;
    melhorSub = malloc(grafo->numVertices * sizeof(int));

    // Obter duas soluções iniciais do crossover
    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(melhorSolucao1, melhorSolucao2, grafo);

    for (int s = 0; s < 2; s++) {
        int *solucaoAtual = solucoesCrossover[s];
        for (int i = 0; i < interacoes; i++) {
            sol = Hill_Climbing_2(solucaoAtual, grafo, edges, k);
            imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
            validateSoluction(sol, grafo, edges, k);
            int custoAtual = calculaCustoTotal(sol->melhorSolucao, edges, grafo->numArestas);

            if (custoAtual < melhorCusto) {
                melhorCusto = custoAtual;
                memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
            }

            memcpy(solucaoAtual, sol->melhorSolucao, grafo->numVertices * sizeof(int));
            free(sol);
        }
    }

    for (int i = 0; i < 2; i++) {
        free(solucoesCrossover[i]);
    }
    free(solucoesCrossover);

    return melhorSub;
}
