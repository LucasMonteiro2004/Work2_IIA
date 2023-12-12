#include "AbordagensHíbridas.h"

int* reparacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k){
    while ((validateSoluction(melhorSolucao, grafo, edges, k) != 1)){
        melhorSolucao = generates_neighbor_2(melhorSolucao, grafo, edges);
    }
    return melhorSolucao;
}