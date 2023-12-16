#include "AlgoritmoEvolutivo.h"
#include "PesquisaLocal.h"

int** algoritmoRecombinacao_Single_Point_Crossover(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo) {
    int** solucoes = (int**)malloc(2 * sizeof(int*));
    int pontoCorte = rand() % grafo->numVertices;

    // Primeira solução
    solucoes[0] = (int*)malloc(grafo->numVertices * sizeof(int));
    memcpy(solucoes[0], melhorSolucao1, pontoCorte * sizeof(int));
    memcpy(solucoes[0] + pontoCorte, melhorSolucao2 + pontoCorte, (grafo->numVertices - pontoCorte) * sizeof(int));

    // Segunda solução (inversa)
    solucoes[1] = (int*)malloc(grafo->numVertices * sizeof(int));
    memcpy(solucoes[1], melhorSolucao2, pontoCorte * sizeof(int));
    memcpy(solucoes[1] + pontoCorte, melhorSolucao1 + pontoCorte, (grafo->numVertices - pontoCorte) * sizeof(int));

    return solucoes;
}

int** algoritmoRecombinacao_Double_Point_Crossover(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo) {
    int** solucoes = (int**)malloc(2 * sizeof(int*));
    int pontoCorte1 = rand() % grafo->numVertices;
    int pontoCorte2;

    do {
        pontoCorte2 = rand() % grafo->numVertices;
    } while (pontoCorte2 == pontoCorte1);

    int pontoInicio = pontoCorte1 < pontoCorte2 ? pontoCorte1 : pontoCorte2;
    int pontoFim = pontoCorte1 > pontoCorte2 ? pontoCorte1 : pontoCorte2;

    // Primeira solução
    solucoes[0] = (int*)malloc(grafo->numVertices * sizeof(int));
    memcpy(solucoes[0], melhorSolucao1, pontoInicio * sizeof(int));
    memcpy(solucoes[0] + pontoInicio, melhorSolucao2 + pontoInicio, (pontoFim - pontoInicio) * sizeof(int));
    memcpy(solucoes[0] + pontoFim, melhorSolucao1 + pontoFim, (grafo->numVertices - pontoFim) * sizeof(int));

    // Segunda solução (inversa)
    solucoes[1] = (int*)malloc(grafo->numVertices * sizeof(int));
    memcpy(solucoes[1], melhorSolucao2, pontoInicio * sizeof(int));
    memcpy(solucoes[1] + pontoInicio, melhorSolucao1 + pontoInicio, (pontoFim - pontoInicio) * sizeof(int));
    memcpy(solucoes[1] + pontoFim, melhorSolucao2 + pontoFim, (grafo->numVertices - pontoFim) * sizeof(int));

    return solucoes;
}


// Função auxiliar para trocar dois elementos em um array
void trocaElementos(int* solucao, int posicao1, int posicao2) {
    int temp = solucao[posicao1];
    solucao[posicao1] = solucao[posicao2];
    solucao[posicao2] = temp;
}

// Mutação de Troca
int* algoritmoMutacao_Troca(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k) {
    int* novaSolucao = (int*)malloc(grafo->numVertices * sizeof(int));

    // Copia a solução original para a nova solução
    memcpy(novaSolucao, melhorSolucao, grafo->numVertices * sizeof(int));

    // Escolhe duas posições aleatórias diferentes na solução
    int posicao1 = rand() % grafo->numVertices;
    int posicao2;

    do {
        posicao2 = rand() % grafo->numVertices;
    } while (posicao2 == posicao1);

    // Troca os elementos nas posições escolhidas
    trocaElementos(novaSolucao, posicao1, posicao2);

    return novaSolucao;
}

// Mutação de Inserção
int* algoritmoMutacao_Insercao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k) {
    int* novaSolucao = (int*)malloc(grafo->numVertices * sizeof(int));

    // Copia a solução original para a nova solução
    memcpy(novaSolucao, melhorSolucao, grafo->numVertices * sizeof(int));

    // Escolhe uma posição aleatória para remover um elemento
    int posicaoRemocao = rand() % grafo->numVertices;

    // Remove o elemento da posição escolhida
    int elementoRemovido = novaSolucao[posicaoRemocao];

    // Escolhe uma posição aleatória diferente para inserir o elemento removido
    int posicaoInsercao;

    do {
        posicaoInsercao = rand() % grafo->numVertices;
    } while (posicaoInsercao == posicaoRemocao);

    // Desloca os elementos para abrir espaço para a inserção
    memmove(novaSolucao + posicaoInsercao + 1, novaSolucao + posicaoInsercao, (grafo->numVertices - posicaoInsercao - 1) * sizeof(int));

    // Insere o elemento removido na nova posição
    novaSolucao[posicaoInsercao] = elementoRemovido;

    return novaSolucao;
}