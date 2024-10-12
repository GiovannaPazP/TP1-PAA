#include "EeSDados.h"
#include "Processamento.h"

void abreArquivo(char **argv){
    FILE *arq;
    arq = fopen(argv[1], "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
}
char* leArquivo(FILE *arq){
    char *linha = (char*)malloc(15 * sizeof(char));
    fgets(linha, 15, arq);
    if(feof(arq)){
        free(linha);
        fechaArquivo(arq);
        return NULL;
    }
    return linha;
}

void fechaArquivo(FILE *arq){
    fclose(arq);
    free(arq);
}

void saida(int exprode){
    if(exprode == 1)
        printf("Kaboom!\n");
    else
        printf("Kit Valido!\n");
}