#include "AbordagensHíbridas.h"

int* Hibrido(int k, Edge **edges, Grafo *grafo, int interacoes, int* solucaoInicial) {
    int *melhorSolucao = malloc(grafo->numVertices * sizeof(int));
    if (!melhorSolucao) {
        printf("Erro na alocacao de memoria para melhorSolucao.\n");
        return NULL;
    }
    memcpy(melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int melhorCusto = INT_MAX;

    for (int i = 0; i < interacoes; i++) {
        // Aplica a mutação por inserção
        Resultado *resultadoMutacao = algoritmoMutacao_Insercao(melhorSolucao, grafo, edges, &k);
        if (!resultadoMutacao) {
            printf("Erro em algoritmoMutacao_Insercao.\n");
            free(melhorSolucao);
            return NULL;
        }

        // Aplica Hill Climbing na solução mutada
        Resultado *resultadoHillClimbing = Hill_Climbing(resultadoMutacao->melhorSolucao, grafo, edges, &k);
        if (!resultadoHillClimbing) {
            printf("Erro em Hill_Climbing.\n");
            free(resultadoMutacao->melhorSolucao);
            free(resultadoMutacao);
            free(melhorSolucao);
            return NULL;
        }

        int custoAtual = calculaCustoTotal(resultadoHillClimbing->melhorSolucao, edges, grafo->numArestas);
        if (custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            memcpy(melhorSolucao, resultadoHillClimbing->melhorSolucao, grafo->numVertices * sizeof(int));
        }

        free(resultadoMutacao->melhorSolucao);
        free(resultadoMutacao);
        free(resultadoHillClimbing->melhorSolucao);
        free(resultadoHillClimbing);
    }

    return melhorSolucao;
}


int* Hibrido_2(int k, Edge **edges, Grafo *grafo, int interacoes, int* solucaoInicial) {
    int *melhorSolucao = malloc(grafo->numVertices * sizeof(int));
    if (!melhorSolucao) {
        printf("Erro na alocacao de memoria para melhorSolucao.\n");
        return NULL;
    }
    memcpy(melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int melhorCusto = INT_MAX;

    for (int i = 0; i < interacoes; i++) {
        // Aplica a mutação de troca
        Resultado *resultadoMutacao = algoritmoMutacao_Troca(melhorSolucao, grafo);
        if (!resultadoMutacao) {
            printf("Erro em algoritmoMutacao_Troca.\n");
            free(melhorSolucao);
            return NULL;
        }

        // Aplica Hill Climbing na solução mutada
        Resultado *resultadoHillClimbing = Hill_Climbing(resultadoMutacao->melhorSolucao, grafo, edges, &k);
        if (!resultadoHillClimbing) {
            printf("Erro em Hill_Climbing.\n");
            free(resultadoMutacao->melhorSolucao);
            free(resultadoMutacao);
            free(melhorSolucao);
            return NULL;
        }

        int custoAtual = calculaCustoTotal(resultadoHillClimbing->melhorSolucao, edges, grafo->numArestas);
        if (custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            memcpy(melhorSolucao, resultadoHillClimbing->melhorSolucao, grafo->numVertices * sizeof(int));
        }

        free(resultadoMutacao->melhorSolucao);
        free(resultadoMutacao);
        free(resultadoHillClimbing->melhorSolucao);
        free(resultadoHillClimbing);
    }

    return melhorSolucao;
}
