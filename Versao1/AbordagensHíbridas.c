#include "AbordagensHíbridas.h"

Resultado * Hibrido(int k, Edge **edges, Grafo *grafo, int interacoes, int* solucaoInicial) {
    Resultado *resultadoMutacao = algoritmoMutacao_Troca(solucaoInicial, grafo);
    Resultado *resultadoFinal;
    int melhorCusto;
    int * melhorSub = malloc(grafo->numVertices * sizeof(int));

    for(int i = 0; i < interacoes; i++){
        resultadoFinal = Hill_Climbing_2(resultadoMutacao->melhorSolucao, grafo, edges, &k);
        if(validateSoluction(resultadoFinal, grafo, edges, &k) == 1){
            int custoAtual = calculaCustoTotal(resultadoFinal->melhorSolucao, edges, grafo->numArestas);

            if (custoAtual < melhorCusto) {
                melhorCusto = custoAtual;
                memcpy(melhorSub, resultadoFinal->melhorSolucao, grafo->numVertices * sizeof(int));
            }
        }
        memcpy(resultadoMutacao->melhorSolucao, resultadoFinal->melhorSolucao, grafo->numVertices * sizeof(int));
        free(resultadoFinal);
    }

    memcpy(resultadoMutacao->melhorSolucao, melhorSub, grafo->numVertices * sizeof(int));
    free(melhorSub);
    return resultadoMutacao;
}
