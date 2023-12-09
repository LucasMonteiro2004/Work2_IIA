#ifndef VERSAO1_ALGORITMOEVOLUTIVO_H
#define VERSAO1_ALGORITMOEVOLUTIVO_H

#include "PesquisaLocal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* algoritmoRecombinacao(int* melhorSolucao1, int* melhorSolucao2, Grafo* grafo, Edge** edges, int* k);
int* algoritmoMutacao(int* melhorSolucao, Grafo* grafo, Edge** edges, int* k);

#endif //VERSAO1_ALGORITMOEVOLUTIVO_H
