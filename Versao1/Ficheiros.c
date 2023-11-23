#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Ficheiros.h"

ficheiro file;

void le_ficheiro(char arquivo[15]){
    FILE *file = fopen(arquivo, "rt");
    if(file == NULL){
        printf("[ERRO] Abrir ficheiro");
    }

    while (file != NULL){

    }
}