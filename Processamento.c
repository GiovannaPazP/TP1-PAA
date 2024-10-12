#include "Processamento.h"

void iniciaVertice(Vertice *v){
    v->cor = (char*)malloc(2 * sizeof(char));
    v->tam = 0;
    v->inicio .x = v->inicio.y = v->final.x = v->final.y = 0;
}

Vertice criaVertice(char *linha){
    Vertice v;
    iniciaVertice(&v);
    sscanf(linha, "%d %d %d %d %d %i %s", &v.inicio.x, &v.inicio.y, &v.final.x, &v.final.y, &v.tam, v.cor); //não sei se funciona
    return v;
}