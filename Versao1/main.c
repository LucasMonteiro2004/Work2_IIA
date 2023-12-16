#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"
#include "AlgoritmoEvolutivo.h"
#include "AbordagensHíbridas.h"

#define INTER 250

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges, opcao = -1;
    int *sub;
    Edge *edges;
    Grafo *grafo;
    Resultado *sol;
    char arquivo[20];
    int **duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
    int *melhorSub = malloc(grafo->numVertices * sizeof(int));
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
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                melhorCusto = INT_MAX;

                for(int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res;
                        res.melhorSolucao = solucoesCrossover[j];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);

                        int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                        }
                    }

                    // Atualiza as soluções iniciais para a próxima iteração
                    free(duasSolucoes[0]);
                    free(duasSolucoes[1]);
                    duasSolucoes[0] = solucoesCrossover[0];
                    duasSolucoes[1] = solucoesCrossover[1];
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);

                free(melhorSub);
                free(duasSolucoes[0]);
                free(duasSolucoes[1]);
                free(duasSolucoes);

                break;

            case 4:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                melhorCusto = INT_MAX;

                for(int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Double_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res;
                        res.melhorSolucao = solucoesCrossover[j];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);

                        int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                        }
                    }

                    // Atualiza as soluções iniciais para a próxima iteração
                    free(duasSolucoes[0]);
                    free(duasSolucoes[1]);
                    duasSolucoes[0] = solucoesCrossover[0];
                    duasSolucoes[1] = solucoesCrossover[1];
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);

                free(melhorSub);
                free(duasSolucoes[0]);
                free(duasSolucoes[1]);
                free(duasSolucoes);

                break;

            case 5:

                break;

            case 6:

                break;

            case 7:

                break;

            case 0:
                printf("Saindo...\n");
                return 0;
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