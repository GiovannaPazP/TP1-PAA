#ifndef PROCESSAMENTO_H
#define PROCESSAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int x;
    int y;
}Coordenada;

typedef struct{
    Coordenada inicio;
    Coordenada final;
    int tam;
    char* cor;
}Vertice;

void iniciaVertice(Vertice* v);

Vertice criaVertice(char* linha);

#endif