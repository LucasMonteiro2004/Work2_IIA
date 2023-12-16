#include "AbordagensHíbridas.h"

int* Hibrido(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo, Edge** edges, int* k, int interacoes){
    int *melhorSub;
    Resultado *sol;
    int melhorCusto = INT_MAX;
    melhorSub = malloc(grafo->numVertices * sizeof(int));
    int *solucaoTrepaColinas = algoritmoRecombinacao_Single_Point_Crossover(melhorSolucao1, melhorSolucao2, grafo, edges, k);
    memcpy(melhorSub, solucaoTrepaColinas, grafo->numVertices * sizeof(int));

    for(int i = 0; i < interacoes; i++){
        sol = Hill_Climbing_2(solucaoTrepaColinas, grafo, edges, k);
        imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
        validateSoluction(sol, grafo, edges, k);
        int custoAtual = calculaCustoTotal(sol->melhorSolucao, edges, grafo->numArestas);

        if (custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
        }

        memcpy(solucaoTrepaColinas, sol->melhorSolucao, grafo->numVertices * sizeof(int));
        free(sol);
    }
    free(solucaoTrepaColinas);
    return (melhorSub);
}