#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "PesquisaLocal.h"
#include "AlgoritmoEvolutivo.h"
#include "AbordagensHíbridas.h"

#define INTER 100

int main() {
    srand(time(NULL));
    int k, numVertices, numEdges, opcao = -1;
    int *sub, *melhorSub, *sub_1;
    Edge *edges;
    Grafo *grafo;
    Resultado *sol, *sol_1;
    char arquivo[20];
    int melhorCusto = INT_MAX;
    int totalCusto = 0;
    int iteracoesValidas = 0;

    while (opcao != 0) {
        printf("\nEscolha uma opcao:\n");
        printf("1. Hill Climbing gerando 1 vizinho\n");
        printf("2. Hill Climbing gerando 2 vizinhos\n");
        printf("3. Recombinacao Single Point Crossover Reparacao\n");
        printf("4. Recombinacao double Point Crossover Reparacao\n");
        printf("5. Mutacao troca\n");
        printf("6. Mutacao Insercao\n");
        printf("7. Hibrido\n");
        printf("8. Recombinacao Single Point Crossover penalisacao\n");
        printf("9. Recombinacao double Point Crossover penalisacao\n");
        printf("10. Hibrido 2\n");
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

                totalCusto = 0;
                iteracoesValidas = 0;

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = Hill_Climbing(sub, grafo, &edges, &k);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                        totalCusto += custoAtual;
                        iteracoesValidas++;

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }

                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(edges);
                free(grafo);
                free(sub);
                break;

            case 2:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                sub_1 = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub_1, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub_1, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol_1 = Hill_Climbing_2(sub_1, grafo, &edges, &k);
                    imprimirSubconjunto(sol_1->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol_1, grafo, &edges, &k) == 1){
                        int custoAtual = calculaCustoTotal(sol_1->melhorSolucao, &edges, grafo->numArestas);

                        totalCusto += custoAtual;
                        iteracoesValidas++;

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol_1->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }

                    memcpy(sub_1, sol_1->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol_1);
                }
                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));
                free(edges);
                free(grafo);
                free(sub_1);
                break;

            case 3:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int **duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_1 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_1, duasSolucoes[0], grafo->numVertices * sizeof(int));
                int melhorCusto_1 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        reparacao(solucoesCrossover[j], grafo->numVertices, k);
                        Resultado res;
                        res.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res.melhorSolucao = solucoesCrossover[j];
                        res.custo_melhor_solucao = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numVertices);
                        res.melhorSolucao2 = NULL;
                        res.solucaoInicial = duasSolucoes[0];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                            totalCusto += custoAtual;
                            iteracoesValidas++;
                            if (custoAtual < melhorCusto_1) {
                                melhorCusto_1 = custoAtual;
                                memcpy(melhorSub_1, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                            }
                        }
                    }

                    memcpy(duasSolucoes[0], solucoesCrossover[0], grafo->numVertices * sizeof(int));
                    memcpy(duasSolucoes[1], solucoesCrossover[1], grafo->numVertices * sizeof(int));

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub_1, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto_1);

                free(melhorSub_1);
                for (int i = 0; i < 2; i++) {
                    free(duasSolucoes[i]);
                }
                free(duasSolucoes);

                break;

            case 4:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int **duasSolucoes_2 = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_2 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_2, duasSolucoes_2[0], grafo->numVertices * sizeof(int));
                int melhorCusto_2 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Double_Point_Crossover(duasSolucoes_2[0], duasSolucoes_2[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        reparacao(solucoesCrossover[j], grafo->numVertices, k);
                        Resultado res_1;
                        res_1.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res_1.melhorSolucao = solucoesCrossover[j];
                        res_1.custo_melhor_solucao = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numVertices);
                        res_1.melhorSolucao2 = NULL;
                        res_1.solucaoInicial = duasSolucoes_2[0];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res_1, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                            totalCusto += custoAtual;
                            iteracoesValidas++;
                            if (custoAtual < melhorCusto_2) {
                                melhorCusto_2 = custoAtual;
                                memcpy(melhorSub_2, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                            }
                        }
                    }

                    memcpy(duasSolucoes_2[0], solucoesCrossover[0], grafo->numVertices * sizeof(int));
                    memcpy(duasSolucoes_2[1], solucoesCrossover[1], grafo->numVertices * sizeof(int));

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub_2, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto_2);

                free(melhorSub_2);
                for (int i = 0; i < 2; i++) {
                    free(duasSolucoes_2[i]);
                }
                free(duasSolucoes_2);

                break;

            case 5:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = algoritmoMutacao_Troca(sub, grafo);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);
                        totalCusto += custoAtual;
                        iteracoesValidas++;
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(edges);
                free(grafo);
                free(sub);
                break;

            case 6:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = algoritmoMutacao_Insercao(sub, grafo, &edges, &k);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);
                        totalCusto += custoAtual;
                        iteracoesValidas++;
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(edges);
                free(grafo);
                free(sub);
                break;

            case 7:
                printf("\nNome do arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int *subSolucao = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(subSolucao, grafo->numVertices);

                melhorSub = malloc(grafo->numVertices * sizeof(int));
                if (!melhorSub) {
                    printf("Erro na alocacao de memoria para melhorSub.\n");
                    free(subSolucao);
                    break;
                }

                memcpy(melhorSub, subSolucao, grafo->numVertices * sizeof(int));
                melhorCusto = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int *novaSolucao = Hibrido(k, &edges, grafo, 10, subSolucao);
                    if (!novaSolucao) {
                        printf("Erro ao obter solucao hibrida.\n");
                        break;
                    }
                    imprimirSubconjunto(novaSolucao, grafo->numVertices);

                    Resultado tempResultado;
                    tempResultado.melhorSolucao = malloc(grafo->numVertices * sizeof(int ));
                    tempResultado.solucaoInicial = subSolucao;
                    tempResultado.custo_melhor_solucao = 0;
                    tempResultado.melhorSolucao = novaSolucao;
                    if (validateSoluction(&tempResultado, grafo, &edges, &k) == 1) {
                        int custoAtual = calculaCustoTotal(novaSolucao, &edges, grafo->numArestas);
                        totalCusto += custoAtual;
                        iteracoesValidas++;
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, novaSolucao, grafo->numVertices * sizeof(int));
                        }
                    }

                    if (i < INTER - 1) {
                        free(subSolucao);
                        subSolucao = novaSolucao;
                    } else {
                        free(novaSolucao);
                    }
                }
                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(subSolucao);
                free(melhorSub);
                free(grafo);
                free(edges);
                break;

            case 8:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int **duasSolucoes_3 = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_3 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_3, duasSolucoes_3[0], grafo->numVertices * sizeof(int));
                int melhorCusto_3 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(duasSolucoes_3[0], duasSolucoes_3[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res_2;
                        res_2.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res_2.melhorSolucao = solucoesCrossover[j];
                        res_2.custo_melhor_solucao = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numVertices);
                        res_2.melhorSolucao2 = NULL;
                        res_2.solucaoInicial = duasSolucoes_3[0];
                        penalizacao(solucoesCrossover[j], grafo->numVertices, &edges, k, &res_2.custo_melhor_solucao);
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res_2, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                            totalCusto += custoAtual;
                            iteracoesValidas++;
                            if (custoAtual < melhorCusto_3) {
                                melhorCusto_3 = custoAtual;
                                memcpy(melhorSub_3, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                            }
                        }
                    }

                    memcpy(duasSolucoes_3[0], solucoesCrossover[0], grafo->numVertices * sizeof(int));
                    memcpy(duasSolucoes_3[1], solucoesCrossover[1], grafo->numVertices * sizeof(int));

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub_3, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto_3);

                free(melhorSub_3);
                for (int i = 0; i < 2; i++) {
                    free(duasSolucoes_3[i]);
                }
                free(duasSolucoes_3);

                break;

            case 9:
                printf("\nNome arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int **duasSolucoes_4 = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_4 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_4, duasSolucoes_4[0], grafo->numVertices * sizeof(int));
                int melhorCusto_4 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Double_Point_Crossover(duasSolucoes_4[0], duasSolucoes_4[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res_3;
                        res_3.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res_3.melhorSolucao = solucoesCrossover[j];
                        res_3.custo_melhor_solucao = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numVertices);
                        res_3.melhorSolucao2 = NULL;
                        res_3.solucaoInicial = duasSolucoes_4[0];
                        penalizacao(solucoesCrossover[j], grafo->numVertices, &edges, k, &res_3.custo_melhor_solucao);
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res_3, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
                            totalCusto += custoAtual;
                            iteracoesValidas++;
                            if (custoAtual < melhorCusto_4) {
                                melhorCusto_4 = custoAtual;
                                memcpy(melhorSub_4, solucoesCrossover[j], grafo->numVertices * sizeof(int));
                            }
                        }
                    }

                    memcpy(duasSolucoes_4[0], solucoesCrossover[0], grafo->numVertices * sizeof(int));
                    memcpy(duasSolucoes_4[1], solucoesCrossover[1], grafo->numVertices * sizeof(int));

                    free(solucoesCrossover[0]);
                    free(solucoesCrossover[1]);
                    free(solucoesCrossover);
                }

                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }

                imprimirSubconjunto(melhorSub_4, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", melhorCusto_4);

                free(melhorSub_4);
                for (int i = 0; i < 2; i++) {
                    free(duasSolucoes_4[i]);
                }
                free(duasSolucoes_4);

                break;

            case 10:
                printf("\nNome do arquivo?");
                scanf("%s", arquivo);
                readFile(arquivo, &k, &numVertices, &numEdges, &edges, &grafo);

                printf("k: %d\n", k);
                printf("Numero de vertices: %d\n", grafo->numVertices);
                printf("Numero de arestas: %d\n", grafo->numArestas);

                totalCusto = 0;
                iteracoesValidas = 0;

                int *subSolucao_2 = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(subSolucao_2, grafo->numVertices);

                melhorSub = malloc(grafo->numVertices * sizeof(int));
                if (!melhorSub) {
                    printf("Erro na alocacao de memoria para melhorSub.\n");
                    free(subSolucao_2);
                    break;
                }

                memcpy(melhorSub, subSolucao_2, grafo->numVertices * sizeof(int));
                melhorCusto = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int *novaSolucao = Hibrido_2(k, &edges, grafo, 10, subSolucao_2);
                    if (!novaSolucao) {
                        printf("Erro ao obter solucao hibrida.\n");
                        break;
                    }
                    imprimirSubconjunto(novaSolucao, grafo->numVertices);

                    Resultado tempResultado;
                    tempResultado.melhorSolucao = malloc(grafo->numVertices * sizeof(int ));
                    tempResultado.solucaoInicial = subSolucao_2;
                    tempResultado.custo_melhor_solucao = 0;
                    tempResultado.melhorSolucao = novaSolucao;
                    if (validateSoluction(&tempResultado, grafo, &edges, &k) == 1) {
                        int custoAtual = calculaCustoTotal(novaSolucao, &edges, grafo->numArestas);
                        totalCusto += custoAtual;
                        iteracoesValidas++;
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, novaSolucao, grafo->numVertices * sizeof(int));
                        }
                    }

                    if (i < INTER - 1) {
                        free(subSolucao);
                        subSolucao = novaSolucao;
                    } else {
                        free(novaSolucao);
                    }
                }
                if (iteracoesValidas > 0) {
                    float mbf = (float)totalCusto / iteracoesValidas;
                    printf("MBF (Media de Custo): %f\n", mbf);
                } else {
                    printf("Nenhuma iteracao valida encontrada.\n");
                }
                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solucao encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(subSolucao);
                free(melhorSub);
                free(grafo);
                free(edges);
                break;

            case 0:
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
        }

    }
    return 0;
}