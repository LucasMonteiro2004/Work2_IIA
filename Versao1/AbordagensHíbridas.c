#include "AbordagensHíbridas.h"

int* Hibrido(int k, Edge **edges, Grafo *grafo, int interacoes, int* solucaoInicial) {
    int *melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    if (!melhorSolucao) {
        return NULL;
    }

    memcpy(melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int melhorCusto = INT_MAX;

    for (int i = 0; i < interacoes; i++) {
        Resultado *resultadoFinal = Hill_Climbing_2(melhorSolucao, grafo, edges, &k);
        if (!resultadoFinal) {
            free(melhorSolucao);
            return NULL;
        }

        if (validateSoluction(resultadoFinal, grafo, edges, &k) == 1) {
            int custoAtual = calculaCustoTotal(resultadoFinal->melhorSolucao, edges, grafo->numArestas);
            if (custoAtual < melhorCusto) {
                melhorCusto = custoAtual;
                memcpy(melhorSolucao, resultadoFinal->melhorSolucao, grafo->numVertices * sizeof(int));
            }
        }

        free(resultadoFinal->melhorSolucao);
        free(resultadoFinal);
    }

    return melhorSolucao;
}
