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
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
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

                sub_1 = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub_1, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub_1, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol_1 = Hill_Climbing_2(sub_1, grafo, &edges, &k);
                    imprimirSubconjunto(sol_1->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol_1, grafo, &edges, &k) == 1){
                        int custoAtual = calculaCustoTotal(sol_1->melhorSolucao, &edges, grafo->numArestas);

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol_1->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub_1, sol_1->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol_1);
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

                int **duasSolucoes = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_1 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_1, duasSolucoes[0], grafo->numVertices * sizeof(int));
                int melhorCusto_1 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Single_Point_Crossover(duasSolucoes[0], duasSolucoes[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res;
                        res.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res.melhorSolucao = solucoesCrossover[j];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
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

                int **duasSolucoes_2 = geraDuasSolucoesIniciais(&k, &edges, grafo);
                int *melhorSub_2 = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub_2, duasSolucoes_2[0], grafo->numVertices * sizeof(int));
                int melhorCusto_2 = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int **solucoesCrossover = algoritmoRecombinacao_Double_Point_Crossover(duasSolucoes_2[0], duasSolucoes_2[1], grafo);

                    for (int j = 0; j < 2; j++) {
                        Resultado res_1;
                        res_1.melhorSolucao = malloc(grafo->numVertices * sizeof(int));
                        res_1.melhorSolucao = solucoesCrossover[j];
                        imprimirSubconjunto(solucoesCrossover[j], grafo->numVertices);
                        if (validateSoluction(&res_1, grafo, &edges, &k) == 1) {
                            int custoAtual = calculaCustoTotal(solucoesCrossover[j], &edges, grafo->numArestas);
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

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = algoritmoMutacao_Troca(sub, grafo);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
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

                sub = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(sub, grafo->numVertices);
                melhorSub = malloc(grafo->numVertices * sizeof(int));
                memcpy(melhorSub, sub, grafo->numVertices * sizeof(int));

                for(int i = 0; i < INTER; i++){
                    sol = algoritmoMutacao_Insercao(sub, grafo, &edges, &k);
                    imprimirSubconjunto(sol->melhorSolucao, grafo->numVertices);
                    if(validateSoluction(sol, grafo, &edges, &k)){
                        int custoAtual = calculaCustoTotal(sol->melhorSolucao, &edges, grafo->numArestas);

                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                        }
                    }
                    memcpy(sub, sol->melhorSolucao, grafo->numVertices * sizeof(int));
                    free(sol);
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

                int *subSolucao = geraSolucaoInicial(&k, &edges, &grafo);
                imprimirSubconjunto(subSolucao, grafo->numVertices);

                melhorSub = malloc(grafo->numVertices * sizeof(int));
                if (!melhorSub) {
                    printf("Erro na alocacao de memoria para melhorSub.\n");
                    free(subSolucao);
                    // Considerar a liberação de outras memórias alocadas, se necessário
                    break;
                }

                memcpy(melhorSub, subSolucao, grafo->numVertices * sizeof(int));
                melhorCusto = INT_MAX;

                for (int i = 0; i < INTER; i++) {
                    int *novaSolucao = Hibrido(k, &edges, grafo, 10, subSolucao);
                    if (!novaSolucao) {
                        printf("Erro ao obter solução híbrida.\n");
                        continue;
                    }

                    imprimirSubconjunto(novaSolucao, grafo->numVertices);

                    Resultado tempResultado;
                    tempResultado.melhorSolucao = novaSolucao;
                    if (validateSoluction(&tempResultado, grafo, &edges, &k)) {
                        int custoAtual = calculaCustoTotal(novaSolucao, &edges, grafo->numArestas);
                        if (custoAtual < melhorCusto) {
                            melhorCusto = custoAtual;
                            memcpy(melhorSub, novaSolucao, grafo->numVertices * sizeof(int));
                        }
                    }

                    free(subSolucao); // Libera a antiga solução inicial
                    subSolucao = novaSolucao; // Atualiza a solução inicial com a nova solução
                }

                imprimirSubconjunto(melhorSub, grafo->numVertices);
                printf("Melhor solução encontrada com custo: %d\n", calculaCustoTotal(melhorSub, &edges, grafo->numArestas));

                free(subSolucao);
                free(melhorSub);
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