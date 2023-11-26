#include <stdio.h>
#include "PesquisaLocal.h"

int main() {
    int k, numVertices, numEdges;
    Edge *edges;
    char arquivo[20];

    printf("Nome arquivo?");
    scanf("%s", arquivo);
    readFile(arquivo, &k, &numVertices, &numEdges, &edges);

    printf("k: %d\n", k);
    printf("Numero de vertices: %d\n", numVertices);
    printf("Numero de arestas: %d\n", numEdges);


    for (int i = 0; i < numEdges; i++) {
        printf("Aresta %d: %c %d %d %d\n", i+1 ,edges[i].car, edges[i].u, edges[i].v, edges[i].cost);
    }

    free(edges);
    return 0;
}
