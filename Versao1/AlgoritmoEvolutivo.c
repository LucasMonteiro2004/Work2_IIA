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
Resultado *algoritmoMutacao_Troca(int *solucaoInicial, Grafo *grafo) {
    Resultado *res = (Resultado *)malloc(sizeof(Resultado));
    if (res == NULL) {
        // Tratamento de erro de alocação de memória para Resultado
        return NULL;
    }

    res->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    if (res->melhorSolucao == NULL) {
        // Tratamento de erro de alocação de memória para melhorSolucao
        free(res);
        return NULL;
    }

    // Copia a solução inicial para melhorSolucao
    memcpy(res->melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));

    // Realiza a mutação por troca
    int posicao1 = rand() % grafo->numVertices;
    int posicao2;
    do {
        posicao2 = rand() % grafo->numVertices;
    } while (posicao2 == posicao1);

    int temp = res->melhorSolucao[posicao1];
    res->melhorSolucao[posicao1] = res->melhorSolucao[posicao2];
    res->melhorSolucao[posicao2] = temp;

    // Inicializa os outros campos da estrutura Resultado
    res->melhorSolucao2 = NULL; // ou alocar e definir conforme necessário
    res->solucaoInicial = solucaoInicial; // mantendo a referência para a solução inicial
    // O custo da melhor solução pode ser calculado aqui ou mais tarde
    res->custo_melhor_solucao = 0; // ou calcular o custo se necessário

    return res;
}

// Mutação de Inserção
Resultado *algoritmoMutacao_Insercao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k) {
    Resultado *res = (Resultado *)malloc(sizeof(Resultado));
    if (res == NULL) {
        // Tratamento de erro de alocação de memória para Resultado
        return NULL;
    }

    res->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    if (res->melhorSolucao == NULL) {
        // Tratamento de erro de alocação de memória para melhorSolucao
        free(res);
        return NULL;
    }

    // Copia a solução original para melhorSolucao
    memcpy(res->melhorSolucao, melhorSolucao, grafo->numVertices * sizeof(int));

    // Realiza a mutação por inserção
    int posicaoRemocao = rand() % grafo->numVertices;
    int posicaoInsercao;
    do {
        posicaoInsercao = rand() % grafo->numVertices;
    } while (posicaoInsercao == posicaoRemocao);

    // Elemento a ser movido
    int elementoMovido = res->melhorSolucao[posicaoRemocao];

    // Desloca os elementos para abrir espaço para a inserção
    if (posicaoInsercao < posicaoRemocao) {
        memmove(res->melhorSolucao + posicaoInsercao + 1, res->melhorSolucao + posicaoInsercao, (posicaoRemocao - posicaoInsercao) * sizeof(int));
    } else {
        memmove(res->melhorSolucao + posicaoRemocao, res->melhorSolucao + posicaoRemocao + 1, (posicaoInsercao - posicaoRemocao) * sizeof(int));
    }

    // Insere o elemento movido na nova posição
    res->melhorSolucao[posicaoInsercao] = elementoMovido;

    // Inicializa os outros campos da estrutura Resultado
    res->melhorSolucao2 = NULL;
    res->solucaoInicial = melhorSolucao;
    res->custo_melhor_solucao = 0; // ou calcular o custo se necessário

    return res;
}
