#include <stdio.h>
#include "PesquisaLocal.h"

int main() {
    int k, numVertices, numEdges;
    Edge *edges;
    Grafo *grafo;

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

    int *sub = geraSolucaoInicial(&k, &edges, &grafo);
    imprimirSubconjunto(sub, grafo->numVertices);
    int *Sol = Hill_Climbing(sub, grafo, &edges);
    imprimirSubconjunto(Sol, grafo->numVertices);
    validateSoluction(Sol, grafo, &edges, &k);

    free(edges);
    free(grafo);
    free(sub);
    free(Sol);

    return 0;
}
