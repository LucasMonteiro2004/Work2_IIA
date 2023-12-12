#include <stdio.h>
#include "PesquisaLocal.h"
#include "AlgoritmoEvolutivo.h"
#include "AbordagensHíbridas.h"

#define INTER 10

int main() {
    int k, numVertices, numEdges;
    int *sub;
    Edge *edges;
    Grafo *grafo;
    Resultado* sol = (Resultado*)malloc(sizeof(Resultado));

    printf("Nome arquivo?");
    char arquivo[20];
    scanf("%s", arquivo);
    readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

    printf("k: %d\n", k);
    printf("Numero de vertices: %d\n", grafo->numVertices);
    printf("Numero de arestas: %d\n", grafo->numArestas);

    for (int i = 0; i < grafo->numArestas; i++) {
        printf("Aresta %d: %c %d %d %d\n", i + 1, edges[i].car, edges[i].u, edges[i].v, edges[i].cost);
    }

    for(int i = 0; i < INTER; i++){
        sub = geraSolucaoInicial(&k, &edges, &grafo);
        imprimirSubconjunto(sub, grafo->numVertices);
        sol = Hill_Climbing_2(sub, grafo, &edges, &k);
        imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
        validateSoluction(sol->melhorSolucao, grafo, &edges, &k);
    }

    free(edges);
    free(grafo);
    free(sub);

    return 0;
}
