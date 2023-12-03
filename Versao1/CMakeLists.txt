cmake_minimum_required(VERSION 3.26)
project(Versao1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Versao1 main.c
        PesquizaLocal.c
        PesquisaLocal.h
        "AlgoritmoEvolutivo .c"
        "AlgoritmoEvolutivo .h"
)
