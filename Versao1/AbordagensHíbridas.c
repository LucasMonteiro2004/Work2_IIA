#include "AbordagensHíbridas.h"

int* Hibrido(int k, Edge **edges, Grafo *grafo, int interacoes, int* solucaoInicial) {
    int *melhorSolucao = malloc(grafo->numVertices * sizeof(int));
    if (!melhorSolucao) {
        printf("Erro na alocação de memória para melhorSolucao.\n");
        return NULL;
    }

    memcpy(melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int melhorCusto = INT_MAX;

    for (int i = 0; i < interacoes; i++) {
        Resultado *resultadoFinal = Hill_Climbing_2(melhorSolucao, grafo, edges, &k);
        if (!resultadoFinal) {
            printf("Erro em Hill_Climbing_2.\n");
            free(melhorSolucao);
            return NULL;
        }

        if (validateSoluction(resultadoFinal, grafo, edges, &k)) {
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
