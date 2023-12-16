#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"
#include "AlgoritmoEvolutivo.h"
#include "AbordagensHíbridas.h"

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
    int **duasSolucoes;

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

                duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
                melhorSub = NULL;

                for(int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado resTemp;
                        resTemp.melhorSolucao = solucoesCrossover[j];
                        resTemp.melhorSolucao2 = NULL;
                        resTemp.solucaoInicial = NULL;
                        resTemp.custo_melhor_solucao = 0;
                        if (!validateSoluction(&resTemp, grafo, &edges, &k)) {
                            solucoesCrossover[j] = reparacao(solucoesCrossover[j], grafo, &edges, &k);
                        }

                        int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            if (melhorSub) {
                                free(melhorSub);
                            }
                            melhorSub = (int *)malloc(grafo->numVertices * sizeof(int));
                            memcpy(melhorSub, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                        }
                    }

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (melhorSub) {
                    printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                    imprimirSubconjunto(melhorSub, grafo->numVertices);
                    free(melhorSub);
                }

                free(duasSolucoes[0]);
                free(duasSolucoes[1]);
                free(duasSolucoes);
                break;

            case 4:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
                int *melhorSolucao = NULL;

                for(int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Double_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado resTemp;
                        resTemp.melhorSolucao = solucoesCrossover[j];
                        resTemp.melhorSolucao2 = NULL;
                        resTemp.solucaoInicial = NULL;
                        resTemp.custo_melhor_solucao = 0;
                        if (!validateSoluction(&resTemp, grafo, &edges, &k)) {
                            solucoesCrossover[j] = reparacao(solucoesCrossover[j], grafo, &edges, &k);
                        }

                        int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            if (melhorSolucao) {
                                free(melhorSolucao);
                            }
                            melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
                            memcpy(melhorSolucao, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                        }
                    }

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (melhorSolucao) {
                    printf("Melhor solução encontrada com custo: %d\n", melhorCusto);
                    imprimirSubconjunto(melhorSolucao, grafo->numVertices);
                    free(melhorSolucao);
                }

                free(duasSolucoes[0]);
                free(duasSolucoes[1]);
                free(duasSolucoes);
                break;


            case 5:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                melhorSolucao = NULL;

                for(int i = 0; i < INTER; i++) {
                    int *solucaoMutacao = algoritmoMutacao_Troca(sub, grafo, &edges, &k);
                    Resultado resTemp;
                    resTemp.melhorSolucao = solucaoMutacao;
                    resTemp.melhorSolucao2 = NULL;
                    resTemp.solucaoInicial = NULL;
                    resTemp.custo_melhor_solucao = 0;

                    if (!validateSoluction(&resTemp, grafo, &edges, &k)) {
                        solucaoMutacao = reparacao(solucaoMutacao, grafo, &edges, &k);
                    }

                    int custoAtual = calculaCustoTotal(solucaoMutacao, &edges, grafo->numArestas);
                    if (custoAtual < melhorCusto) {
                        melhorCusto = custoAtual;
                        if (melhorSolucao) {
                            free(melhorSolucao);
                        }
                        melhorSolucao = solucaoMutacao;
                    } else {
                        free(solucaoMutacao);
                    }
                }

                if (melhorSolucao) {
                    printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                    imprimirSubconjunto(melhorSolucao, grafo->numVertices);
                    free(melhorSolucao);
                }

                free(sub);
                break;

            case 6:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                melhorSolucao = NULL;

                for(int i = 0; i < INTER; i++) {
                    int *solucaoMutacao = algoritmoMutacao_Insercao(sub, grafo, &edges, &k);
                    Resultado resTemp;
                    resTemp.melhorSolucao = solucaoMutacao;
                    resTemp.melhorSolucao2 = NULL;
                    resTemp.solucaoInicial = NULL;
                    resTemp.custo_melhor_solucao = 0;

                    if (!validateSoluction(&resTemp, grafo, &edges, &k)) {
                        solucaoMutacao = reparacao(solucaoMutacao, grafo, &edges, &k);
                    }

                    int custoAtual = calculaCustoTotal(solucaoMutacao, &edges, grafo->numArestas);
                    if (custoAtual < melhorCusto) {
                        melhorCusto = custoAtual;
                        if (melhorSolucao) {
                            free(melhorSolucao);
                        }
                        melhorSolucao = solucaoMutacao;
                    } else {
                        free(solucaoMutacao);
                    }
                }

                if (melhorSolucao) {
                    printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                    imprimirSubconjunto(melhorSolucao, grafo->numVertices);
                    free(melhorSolucao);
                }

                free(sub);
                break;

            case 7:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, &grafo);
                melhorSolucao = NULL;

                for(int i = 0; i < INTER; i++) {
                    int *solucaoHibrida = Hibrido(duasSolucoes[0], duasSolucoes[1], grafo, &edges, &k, 1);
                    Resultado resTemp;
                    resTemp.melhorSolucao = solucaoHibrida;
                    resTemp.melhorSolucao2 = NULL;
                    resTemp.solucaoInicial = NULL;
                    resTemp.custo_melhor_solucao = 0;

                    if (!validateSoluction(&resTemp, grafo, &edges, &k)) {
                        solucaoHibrida = reparacao(solucaoHibrida, grafo, &edges, &k);
                    }

                    int custoAtual = calculaCustoTotal(solucaoHibrida, &edges, grafo->numArestas);
                    if (custoAtual < melhorCusto) {
                        melhorCusto = custoAtual;
                        if (melhorSolucao) {
                            free(melhorSolucao);
                        }
                        melhorSolucao = solucaoHibrida;
                    } else {
                        free(solucaoHibrida);
                    }
                }

                if (melhorSolucao) {
                    printf("Melhor solucao encontrada com custo: %d\n", melhorCusto);
                    imprimirSubconjunto(melhorSolucao, grafo->numVertices);
                    free(melhorSolucao);
                }

                free(duasSolucoes[0]);
                free(duasSolucoes[1]);
                free(duasSolucoes);
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
