#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PesquisaLocal.h"

void readFile(char *fileName, int *k, int *numVertices, int *numEdges, Edge **edges, Grafo **grafo) {
    FILE *file = fopen(fileName, "rt");

    char type;
    int u, v, cost;

    if (file == NULL) {
        printf("[Erro] de abertura de ficheiro");
        exit(1);
    }

    fscanf(file, "%*s %d %*s %*s %d %d", k, numVertices, numEdges);

    *edges = (Edge *)malloc(sizeof(Edge) * (*numEdges));
    for (int i = 0; i < *numEdges; i++) {
        fscanf(file, " %c %d %d %d", &type, &u, &v, &cost);

        (*edges)[i].car = type;
        (*edges)[i].u = u;
        (*edges)[i].v = v;
        (*edges)[i].cost = cost;
    }

    *grafo = (Grafo *)malloc(sizeof(Grafo));
    (*grafo)->numVertices = *numVertices;
    (*grafo)->numArestas = *numEdges;

    fclose(file);
}

void imprimirSubconjunto(int *subconjunto, int tamanho) {
    printf("Vertices: ");
    for (int i = 0; i < tamanho; ++i) {
        printf("%d ", subconjunto[i]);
    }
    printf("\n");
}

int calculaCustoTotal(int *solucao, Edge **edges, int numArestas) {
    int custoTotal = 0;

    for (int i = 0; i < numArestas; ++i) {
        int pos1 = (*edges)[i].u - 1, pos2 = (*edges)[i].v - 1;

        if (solucao[pos1] == 1 && solucao[pos2] == 1) {
            custoTotal += (*edges)[i].cost;
        }
    }

    return custoTotal;
}

int *geraSolucaoInicial(int *k, Edge **edges, Grafo **grafo) {
    int tam = (*grafo)->numVertices;
    int *solucaoInicial = (int *)malloc(tam * sizeof(int));

    for (int i = 0; i < tam; ++i) {
        solucaoInicial[i] = 0;
    }

    int custoTotal = 0;
    int numeroAleatorio = rand() % 3;

    for (int i = 0; i < (*grafo)->numArestas; ++i) {
        int pos1 = (*edges)[i].u - 1, pos2 = (*edges)[i].v - 1;
        solucaoInicial[pos1] = 1;
        solucaoInicial[pos2] = 1;

        custoTotal = calculaCustoTotal(solucaoInicial, edges, (*grafo)->numArestas);

        int contador = 0;
        for (int j = 0; j < tam; ++j) {
            if (solucaoInicial[j] == 1) {
                contador++;
            }
        }

        if (contador == *k) {
            printf("Custo solucao inicial = %d\n", custoTotal);
            return solucaoInicial;
        }else if(contador > *k){
            for (int j = 0; j < tam; ++j) {
                if(solucaoInicial[j] == 1){
                    solucaoInicial[j] = 0;
                    break;
                }
            }
            return solucaoInicial;
        }
    }

    free(solucaoInicial);
    return NULL;
}

int** geraDuasSolucoesIniciais(int *k, Edge **edges, Grafo *grafo) {
    int tam = grafo->numVertices;

    // Alocar memória para o array de soluções
    int **duasSolucoes = (int**)malloc(2 * sizeof(int*));

    // Alocar memória para cada solução individual
    duasSolucoes[0] = (int *)malloc(tam * sizeof(int));
    duasSolucoes[1] = (int *)malloc(tam * sizeof(int));

    // Inicializar a primeira solução
    for (int i = 0; i < tam; ++i) {
        duasSolucoes[0][i] = rand() % 2; // Gera 0 ou 1 aleatoriamente
    }

    // Inicializar a segunda solução garantindo que seja diferente da primeira
    for (int i = 0; i < tam; ++i) {
        if (duasSolucoes[0][i] == 0) {
            duasSolucoes[1][i] = rand() % 2; // Também pode ser 0 ou 1
        } else {
            duasSolucoes[1][i] = 0; // Garantir que seja diferente da primeira solução
        }
    }

    return duasSolucoes;
}

int *generates_neighbor_2(int *solucaoInicial, Grafo *grafo) {
    int *neighbor = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(neighbor, solucaoInicial, grafo->numVertices * sizeof(int));

    // Primeira troca
    int random_neighbor1 = rand() % grafo->numVertices;
    int random_neighbor2;
    do {
        random_neighbor2 = rand() % grafo->numVertices;
    } while (random_neighbor2 == random_neighbor1);

    int temp = neighbor[random_neighbor1];
    neighbor[random_neighbor1] = neighbor[random_neighbor2];
    neighbor[random_neighbor2] = temp;

    // Segunda troca
    int random_neighbor3;
    int random_neighbor4;
    do {
        random_neighbor3 = rand() % grafo->numVertices;
        random_neighbor4 = rand() % grafo->numVertices;
    } while (random_neighbor3 == random_neighbor4 || random_neighbor3 == random_neighbor1 || random_neighbor4 == random_neighbor1 || random_neighbor4 == random_neighbor2);

    temp = neighbor[random_neighbor3];
    neighbor[random_neighbor3] = neighbor[random_neighbor4];
    neighbor[random_neighbor4] = temp;

    return neighbor;
}

int *generates_neighbor_1(int *solucaoInicial, Grafo *grafo) {
    int *neighbor1 = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(neighbor1, solucaoInicial, grafo->numVertices * sizeof(int));

    int random_neighbor1 = rand() % grafo->numVertices;
    int random_neighbor2;
    do {
        random_neighbor2 = rand() % grafo->numVertices;
    } while (random_neighbor2 == random_neighbor1);

    int temp = neighbor1[random_neighbor1];
    neighbor1[random_neighbor1] = neighbor1[random_neighbor2];
    neighbor1[random_neighbor2] = temp;

    return neighbor1;
}

Resultado* Hill_Climbing(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k) {
    Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
    int melhorCusto = calculaCustoTotal(solucaoInicial, edges, grafo->numArestas);
    resultado->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->melhorSolucao2 = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->solucaoInicial = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(resultado->melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int nextCost = 0, cosPreview = 0;

    do {
        int *solucaoFinal = generates_neighbor_1(resultado->melhorSolucao, grafo);
        nextCost = calculaCustoTotal(solucaoFinal, edges, grafo->numArestas);

        if (nextCost < melhorCusto) {
            cosPreview = melhorCusto;
            resultado->melhorSolucao2 = resultado->melhorSolucao;
            melhorCusto = nextCost;
            free(resultado->melhorSolucao);
            resultado->melhorSolucao = solucaoFinal;
        } else {
            free(solucaoFinal);
        }
    } while (melhorCusto <= nextCost && resultado->melhorSolucao == solucaoInicial);

    printf("Custo solucao Final = %d\n", melhorCusto);
    resultado->custo_melhor_solucao = calculaCustoTotal(resultado->melhorSolucao, edges, grafo->numArestas);
    resultado->solucaoInicial = solucaoInicial;
    return resultado;
}

Resultado* Hill_Climbing_2(int *solucaoInicial, Grafo *grafo, Edge **edges, int *k){
    Resultado* resultado = (Resultado*)malloc(sizeof(Resultado));
    int melhorCusto = calculaCustoTotal(solucaoInicial, edges, grafo->numArestas);
    resultado->melhorSolucao = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->melhorSolucao2 = (int *)malloc(grafo->numVertices * sizeof(int));
    resultado->solucaoInicial = (int *)malloc(grafo->numVertices * sizeof(int));
    memcpy(resultado->melhorSolucao, solucaoInicial, grafo->numVertices * sizeof(int));
    int nextCost = 0, cosPreview = 0;

    do {
        int *solucaoFinal = generates_neighbor_2(resultado->melhorSolucao, grafo);
        nextCost = calculaCustoTotal(solucaoFinal, edges, grafo->numArestas);

        if (nextCost < melhorCusto) {
            cosPreview = melhorCusto;
            resultado->melhorSolucao2 = resultado->melhorSolucao;
            melhorCusto = nextCost;
            free(resultado->melhorSolucao);
            resultado->melhorSolucao = solucaoFinal;
        } else {
            free(solucaoFinal);
        }
    } while (melhorCusto <= nextCost && resultado->melhorSolucao == solucaoInicial);

    printf("Custo solucao Final = %d\n", melhorCusto);
    resultado->custo_melhor_solucao = calculaCustoTotal(resultado->melhorSolucao, edges, grafo->numArestas);
    resultado->solucaoInicial = solucaoInicial;
    return resultado;
}

int validateSoluction(Resultado * resultado, Grafo *grafo, Edge **edges, int *k) {
    int tam = grafo->numVertices, contador = 0;
    int *melhorSolucao = resultado->melhorSolucao;

    // não aceita soluções de custo igual
    if(resultado->melhorSolucao == resultado->solucaoInicial ||
    resultado->custo_melhor_solucao == calculaCustoTotal(resultado->solucaoInicial, edges, grafo->numArestas)){
        printf("Solucao Invalida por custo ou solucao incial = solucao final\n");
        return 0;
    }

    // Verifica os vértices selecionados na melhorSolucao
    for (int i = 0; i < tam; ++i) {
        if (melhorSolucao[i] == 1) {
            contador++;
            if (i >= grafo->numVertices) {
                printf("Solucao Invalida\n");
                return 0;
            }
        }
    }

    // Se o número de vértices selecionados é diferente de k, a solução é inválida
    if (contador != *k) {
        printf("Solucao Invalida\n");
        return 0;
    }

    // Verifica se cada vértice selecionado está conectado a pelo menos um outro
    for (int i = 0; i < tam; ++i) {
        if (melhorSolucao[i] == 1) {
            int isConnected = 0;
            // Verifica todas as arestas para encontrar uma conexão
            for (int j = 0; j < grafo->numArestas; ++j) {
                int pos1 = (*edges)[j].u - 1;
                int pos2 = (*edges)[j].v - 1;
                if ((i == pos1 || i == pos2) && melhorSolucao[pos1] == 1 && melhorSolucao[pos2] == 1) {
                    isConnected = 1;
                    break; // Uma conexão encontrada é suficiente
                }
            }
            // Se não encontrou nenhuma conexão, a solução é inválida
            if (!isConnected) {
                printf("Solucao Invalida - Vertice %d nao esta conectado a outro vertice selecionado\n", i + 1);
                return 0;
            }
        }
    }

    printf("Solucao valida\n");
    return 1;
}

void reparacao(int* solucao, int numVertices, int k) {
    int numAtivos = 0;

    // Contar o número de vértices ativos na solução
    for (int i = 0; i < numVertices; i++) {
        if (solucao[i] == 1) {
            numAtivos++;
        }
    }

    // Se houver mais vértices ativos do que k, desative alguns aleatoriamente
    while (numAtivos > k) {
        int pos = rand() % numVertices;
        if (solucao[pos] == 1) {
            solucao[pos] = 0;
            numAtivos--;
        }
    }

    // Se houver menos vértices ativos do que k, ative alguns aleatoriamente
    while (numAtivos < k) {
        int pos = rand() % numVertices;
        if (solucao[pos] == 0) {
            solucao[pos] = 1;
            numAtivos++;
        }
    }
}

void penalizacao(int* solucao, int numVertices, Edge **edges,int k, int *custo) {
    int numAtivos = 0;
    int precisaPenalizar = 0;

    for (int i = 0; i < numVertices; i++) {
        if (solucao[i] == 1) {
            numAtivos++;
        }
    }

    if (numAtivos != k) {
        precisaPenalizar = 1;
    }

    while (numAtivos != k) {
        int pos = rand() % numVertices;
        if (numAtivos > k && solucao[pos] == 1) {
            solucao[pos] = 0;
            numAtivos--;
        } else if (numAtivos < k && solucao[pos] == 0) {
            solucao[pos] = 1;
            numAtivos++;
        }
    }

    *custo = calculaCustoTotal(solucao, edges, numVertices);

    if (precisaPenalizar) {
        *custo += 1000;
    }
}
