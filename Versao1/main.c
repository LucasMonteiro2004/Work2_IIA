#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"

#define INTER 400

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges, opcao = -1;
    int *sub, *melhorSub;
    Edge *edges;
    Grafo *grafo;
    Resultado *sol;
    int melhorCusto = INT_MAX;
    char arquivo[20];

    while (opcao != 0) {
        printf("\nEscolha uma opcao:\n");
        printf("1. Hill Climbing gerando 1 vizinho\n");
        printf("2. Hill Climbing gerando 2 vizinhos\n");
        printf("3. Single Point Crossover\n");
        printf("4. double Point Crossover\n");
        printf("5. Mutacao Troca\n");
        printf("6. Mutacao Insercao\n");
        printf("7. Hibrido\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome arquivo?");
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

                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                free(edges);
                free(grafo);
                free(sub);
                break;

            case 2:
                printf("Nome arquivo?");
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

                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                free(edges);
                free(grafo);
                free(sub);
                break;

            case 3:
                printf("Nome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);
                break;

            case 4:
                printf("Nome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);
                break;

            case 5:
                printf("Nome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);
                break;

            case 6:
                printf("Nome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);
                break;

            case 7:
                printf("Nome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}