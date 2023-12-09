#include "AlgoritmoEvolutivo.h"

int* algoritmoRecombinacao_Single_Point_Crossover(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo, Edge** edges, int* k) {
    int* novaSolucao = (int*)malloc(grafo->numVertices * sizeof(int));
    int pontoCorte = rand() % grafo->numVertices;

    // Copia a primeira parte da solução do melhorSolucao1
    memcpy(novaSolucao, melhorSolucao1, pontoCorte * sizeof(int));

    // Copia a segunda parte da solução do melhorSolucao2
    memcpy(novaSolucao + pontoCorte, melhorSolucao2 + pontoCorte, (grafo->numVertices - pontoCorte) * sizeof(int));

    return novaSolucao;
}

int* algoritmoMutacao_Troca(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k) {
    int* solucaoMutada = (int*)malloc(grafo->numVertices * sizeof(int));
    memcpy(solucaoMutada, melhorSolucao, grafo->numVertices * sizeof(int));

    int posicaoMutacao = rand() % grafo->numVertices;

    // Inverte o valor na posição de mutação
    solucaoMutada[posicaoMutacao] = (solucaoMutada[posicaoMutacao] == 0) ? 1 : 0;

    return solucaoMutada;
}