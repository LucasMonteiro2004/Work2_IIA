#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"

#define INTER 300

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges, opcao = -1;
    int *sub, *melhorSub;
    Edge *edges;
    Grafo *grafo;
    Resultado *sol;
    char arquivo[20];
    int melhorCusto = INT_MAX;

    while (opcao != 0) {
        printf("\nEscolha uma opcao:\n");
        printf("1. Hill Climbing gerando 1 vizinho\n");
        printf("2. Hill Climbing gerando 2 vizinhos\n");
        printf("3. Recombinacao Single Point Crossover\n");
        printf("4. Recombinacao double Point Crossover\n");
        printf("5. Mutacao troca\n");
        printf("6. Mutacao Insercao\n");
        printf("7. Hibrido\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = Hill_Climbing(sub, grafo, &edges, &k);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    validateSoluction(sol, grafo, &edges, &k);
                    int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                    if (custoAtual < melhorCusto) {
                        melhorCusto = custoAtual;
                        memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    }

                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
                }
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                break;

            case 2:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = Hill_Climbing_2(sub, grafo, &edges, &k);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    validateSoluction(sol, grafo, &edges, &k);
                    int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                    if (custoAtual < melhorCusto) {
                        melhorCusto = custoAtual;
                        memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    }

                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
                }
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));
                break;

            case 3:
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }

    free(edges);
    free(grafo);
    free(sub);
    return 0;
}
