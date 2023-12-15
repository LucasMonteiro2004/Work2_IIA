#include <stdio.h>
#include "PesquisaLocal.h"

#define INTER 300

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges;
    int *sub;
    Edge *edges;
    Grafo *grafo;
    Resultado* sol;

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

    sub = geraSolucaoInicial(&k, &edges, &grafo);
    imprimirSubconjunto(sub, grafo->numVertices);

    for(int i = 0; i < INTER; i++){
        sol = Hill_Climbing_2(sub, grafo, &edges, &k);
        imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
        validateSoluction(sol, grafo, &edges, &k);

        memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));

        free(sol);
    }

    free(edges);
    free(grafo);
    free(sub);

    return 0;
}
