#ifndef VERSAO1_ALGORITMOEVOLUTIVO_H
#define VERSAO1_ALGORITMOEVOLUTIVO_H

#include "PesquisaLocal.h"

int *algoritmoRecombinacao(int *melhorSolucoa, Grafo *grafo, Edge **edges, int *k);
int *algorimoMutacao(int *melhorSolucoa, Grafo *grafo, Edge **edges, int *k);

#endif //VERSAO1_ALGORITMOEVOLUTIVO_H
