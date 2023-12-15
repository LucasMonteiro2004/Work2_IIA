#include <stdio.h>
#include "PesquisaLocal.h"

#define INTER 100

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges;
    int *sub;
    Edge *edges;
    Grafo *grafo;
    Resultado* sol[INTER];

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
        sol[i] = (Resultado*)malloc(sizeof(Resultado));
        sub = geraSolucaoInicial(&k, &edges, &grafo);
        imprimirSubconjunto(sub, grafo->numVertices);
        sol[i] = Hill_Climbing_2(sub, grafo, &edges, &k);
        imprimirSubconjunto(sol[i]->melhorSolucao, grafo->numVertices);
        validateSoluction(sol[i], grafo, &edges, &k);
        free(sol[i]);
    }

    free(edges);
    free(grafo);
    free(sub);

    return 0;
}
