#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 6

/*DEF - ESTRUTURA MATRIZ*/
typedef struct{
    int **dados;
    int lin, col;
}Matriz;

void zeraMatriz(Matriz *m){
    if(m == NULL)
        return;
    for(int i=0; i<m->lin; i++)
        for(int j=0; j<m->col; j++)
            m->dados[i][j] = 0;
}

Matriz *criaMatriz(){
    Matriz *m = (Matriz*)malloc(sizeof(Matriz));
    if(m != NULL){
        m->lin = MAX;
        m->col = MAX;
        m->dados = (int**)malloc(MAX*sizeof(int*));
        for(int i=0; i<MAX; i++)
            m->dados[i] = (int*)malloc(MAX*sizeof(int));
        zeraMatriz(m);
        printf("Matriz criada com sucesso.\n");
    }
    return m;
}

void destroiMatriz(Matriz *m){
    if(m != NULL){
        printf("Destruindo matriz...\n");
        for(int i=0; i<m->lin; i++){
            printf("Liberando linha %d\n", i);
            free(m->dados[i]);
        }
        free(m->dados);
        free(m);
    }
    printf("Matriz destruida com sucesso.\n");
}

int insereElem(Matriz *m, int l, int c, int elem){
    if(m == NULL)
        return 0;
    if(l < 0 || c < 0 || l > m->lin || c > m->col){
        printf("Valores invalidos, elemento nao inserido.\n");
        return 0;
    }
    m->dados[l][c] = elem;
    printf("Elemento inserido com sucesso.\n");
    return 1;
}

void exprode(){
    printf("Kit Invalido - KABOOM!!\n");
}

int verificaPosicao(Matriz *m, int l, int c){
    if(m == NULL) return 0;
    if(l < 0 || c < 0 || l > m->lin || c > m->col){
        printf("Valores invalidos, para verificacao de conflito.\n");
        return 0;
    }
    printf("Verificando colisao na posicao [%d][%d], elem = %d\n", l, c, m->dados[l][c]);
    if(m->dados[l][c] == 0) return 0;
    return 1;
}

int verificaElemento(Matriz *m, int l, int c, int cor){
    if(m == NULL) return 0;
    printf("ver elemento, l=%d e c=%d\n", l, c);
    if(l < 0 || c < 0 || l > m->lin || c > m->col){
        printf("Valores invalidos, para verificacao de conflito em ver elem.\n");
        return 0;
    }
    int elem = m->dados[l][c];
    if(elem == cor){
        return 1;
    }
    return 0;
}

int caso2(Matriz *m, int inicio, int final, int sentido, int cor){
    int check = 0;
    for(int i=inicio; i<=final; i++){
        check = verificaElemento(m, i, sentido, cor);
        if(check) return 1;
    }
    return 0;
}

int caso3(Matriz *m, int inicio, int final, int sentido, int cor){
    int check = 0;
    for(int i=inicio; i<=final; i++){
        check = verificaElemento(m, sentido, i, cor);
        if(check) return 1;
    }
    return 0;
}

//retorna 1 se houve explosao
int verificaExplosao(Matriz *m, int x1, int y1, int x2, int y2, int cor){
    if(m == NULL) return 0;
    int X = x2-x1;
    int Y = y2-y1;
    int proxX1=0, proxY1=0, proxX2=0, proxY2=0;
    proxX1 = x1-1;
    proxY1 = y1-1;
    proxX2 = x2+1;
    proxY2 = y2+1;
    //tamanho unico - caso 1
    printf("\tVerificando as Explosoes X=%d e Y=%d.\n", X, Y);
    if(X == Y){
        if(proxX2 < MAX)
            if(verificaElemento(m, proxX2, y1, cor)) return 1;
        if(proxX1 >= 0)
            if(verificaElemento(m, proxX1, y1, cor)) return 1;
        if(proxY2 < MAX)
            if(verificaElemento(m, x1, proxY2, cor)) return 1;
        if(proxY1 >= 0)
            if(verificaElemento(m, x1, proxY1, cor)) return 1;
        printf("Caso 1\n");
    }
    //tamanho 2 ou 3 - caso 2, horizontal
    else if(X > Y){
        printf("\tX>Y, Proxx2 = %d\n", proxX2);
        if(proxX2 < MAX){
            printf("VAlor do return do caso 2 da segunda linha da conf %d\n", verificaElemento(m, proxX2, y1, cor));
            if(verificaElemento(m, proxX2, y1, cor)) return 1;
        }if(proxX1 >= 0)
            if(verificaElemento(m, proxX1, y1, cor)) return 1;
        if(proxY2 < MAX)
            if(caso2(m, x1, x2, proxY2, cor)) return 1;
        if(proxY1 >= 0)
            if(caso2(m, x1, x2, proxY1, cor)) return 1;
        printf("Caso 2\n");
    }
    //tamanho 2 ou 3 - caso 3, vertical
    else{
        if(proxY1 >= 0)
            if(verificaElemento(m, x1, proxY1, cor)) return 1;
        if(proxY2 < MAX)
            if(verificaElemento(m, x1, proxY2, cor)) return 1;
        if(proxX1 >= 0)
            if(caso3(m, y1, y2, proxX1, cor)) return 1;
        if(proxX2 < MAX)
            if(caso3(m, y1, y2, proxX2, cor)) return 1;
        printf("Caso 3\n");
    }
    return 0;
}

void imprime(Matriz *m){
    if(m == NULL)
        return;
    for(int i=0; i<m->lin; i++){
        for(int j=0; j<m->col; j++){
            printf("[%d] ", m->dados[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Matriz imprimida com sucesso.\n");
}

/*LISTA DE COMPOSIÇÃO - CONTÉM A COMPOSIÇÃO DO KIT*/
//OBS: talvez uma lista encadeada seja melhor

typedef struct{
    char **lista;
    int tam;
    int capacidade;
}ListaComposicao;

ListaComposicao *criaListaComposicao(){
    ListaComposicao *v = (ListaComposicao*) malloc (sizeof(ListaComposicao));
    if(v != NULL){
        v->lista = (char**)malloc(10*sizeof(char*));
        v->tam = 0;
        v->capacidade = 10;
        printf("Lista de composicao criada com sucesso.\n");
    }
    return v;
}

void destroiListaComposicao(ListaComposicao *v){
    if(v!=NULL){
        for(int i=0; i<v->tam;i++){
            free(v->lista[i]);
        }
    }
    free(v->lista);
    free(v);
    printf("Lista de composicao destruida com sucesso.\n");
}

void insereListaComposicao(ListaComposicao *v, char *tamcor){
    if(v == NULL)
        return;
    if(v->tam == v->capacidade){
        v->capacidade += 10;
        v->lista = (char**)realloc(v->lista, v->capacidade*sizeof(char*));
    }
    v->lista[v->tam] = (char*)malloc(strlen(tamcor)*sizeof(char));
    strcpy(v->lista[v->tam], tamcor);
    v->tam++;
}

int procuraListaComposicao(ListaComposicao *l, char *elemento){
    if(l == NULL) return 0;
    for(int i=0; i<l->tam; i++){
        if(l->lista[i] == NULL) continue;
        if(strcmp(l->lista[i], elemento) == 0){
            l->lista[i] = NULL;
            printf("Elemento achado e excluido com sucesso - LC.\n");
            return 1;
        }
    }
    printf("Elemento nao encontrado.\n");
    return 0;
}

void imprimeListaComposicao(ListaComposicao *lista){
    if(lista != NULL){
        for(int i=0; i<lista->tam; i++){
            printf(" [%s] |", lista->lista[i]);
        }
        printf("\n");
    }
}

ListaComposicao *copiaListaComposicao(ListaComposicao *l){
    if(l == NULL) return NULL;
    ListaComposicao *copia = criaListaComposicao();
    for(int i=0; i<l->tam; i++)
        insereListaComposicao(copia, l->lista[i]);
    return copia;
}

int listaComposicaoVazia(ListaComposicao *l){
    if(l == NULL) return 0;
    for(int i=0; i<l->tam; i++)
        if(l->lista[i] != NULL) return 0;
}

/*CONSTRUÇÃO DO CÓDIGO*/

void reinicia(ListaComposicao *lista, ListaComposicao *listaCopia, Matriz *m){
    if(lista == NULL|| listaCopia == NULL || m == NULL) return;
    destroiListaComposicao(listaCopia);             //pq esse trecho funciona? Ao destruir, a referencia também não deveria ser 
    listaCopia = copiaListaComposicao(lista);       //destruida? Eh o fato de q uma nova lista é criada quando se faz a copia e a sorte
    zeraMatriz(m);                                  //de ter listaCopia declarada como uma var de listaComposicao?
}

int codificaCor(char *tag, int *cor){
    if(tag == NULL) return 0;
    char aux[3] = {0};
    int lixo = 0;
    sscanf(tag, "%d %s", &lixo, &aux);
    if (strcmp(aux, "Az") == 0) {
        *cor = 1;
    } else if (strcmp(aux, "Vm") == 0) {
        *cor = 2;
    } else if (strcmp(aux, "Am") == 0) {
        *cor = 3;
    } else if (strcmp(aux, "Vd") == 0) {
        *cor = 4;
    }
    printf("Codificacao da Cor: %d\n", *cor);
    return 0;
}

void verificaValidadeComposicao(int qtd, char *tamcor, int *area){
    if(tamcor == NULL) return;
    char tam[2] = {0};
    printf("Aqui, %.1s * %d\n", tamcor, qtd);
    sscanf(tamcor, "%1s", tam);
    *area += (qtd*atoi(tam));
    printf("Area: %d\n", *area);
}

//se explode ou tem algum problema com a conf, retorna 1
int leLinhaConfiguracao(char *linha, char *token, ListaComposicao *lista, Matriz *matriz){
    if(lista == NULL || matriz == NULL){
        printf("Falha ao configurar\n");
        return 0;
    }
    int aux = 0;
    int x1=0, x2=0, y1=0, y2=0;
    char tamcor[5] = {0};               //5 pelo espaço e o terminador nulo.
    token = strtok(linha, " "); 
    do{
        printf("Token: %s\n", token);
        //-1 para ajustar a matriz, x e y estão trocados para manter a matriz certa
        if (aux == 0) y1 = atoi(token)-1;
        else if (aux == 1) x1 = atoi(token)-1;
        else if (aux == 2) y2 = atoi(token)-1;
        else if (aux == 3) x2 = atoi(token)-1;
        else if (aux == 4){
            sscanf(token, "%3s", tamcor);
        }
        aux++;
    }while(token = strtok(NULL, " "));
    printf("Print %d %d %d %d  |  \n[%s]\tLista: ", x1, y1, x2, y2, tamcor);
    imprimeListaComposicao(lista);
    if(!procuraListaComposicao(lista, tamcor)){
        printf("A bomba nao pertence a composicao.\n");
        return  1;
    }
    imprimeListaComposicao(lista);
    for(int i=x1; i<=x2; i++){
        for(int j=y1; j<=y2; j++){
            printf("\tentrou no for q verifica se bateu a pos.\n");
            //troquei x com y pela matriz
            if(verificaPosicao(matriz, i, j)){
                printf("Conflito nas posicoes das bombas\n");
                exprode();
                return 1;
            }
        }
    }
    int cor = 0;
    codificaCor(tamcor, &cor);
    if(cor){
        printf("\tConseguiu codificar a cor\n");
        //tambem troque x por y e vice versa pela matriz
        if(!verificaExplosao(matriz, x1, y1, x2, y2, cor)){
            for(int i=x1; i<=x2; i++){
                for(int j=y1; j<=y2; j++){
                    insereElem(matriz, i, j, cor);
                }
            }
            return 0;
        }
    }
    exprode();
    return 1;
}

void leLinhaComposicao(char *linha, char *token, ListaComposicao *lista, int *area){
    if(lista == NULL){
        printf("Lista de composição não existe\n");
        return;
    }
    int aux = 0;
    int quantidade=0;
    char tamcor[5] = {0};       //tamanho e cor da bomba
    token = strtok(linha, " ");
    do{
        if(aux == 0) quantidade = atoi(token);
        else if(aux == 1){
            sscanf(token, "%3s", tamcor);
            printf("\n\t\t\t\t\t\tTamcor: [%s]\n", tamcor);
        }
        aux++;
    }while(token = strtok(NULL, " "));
    for(int i=0; i<quantidade; i++)
        insereListaComposicao(lista, tamcor);
    verificaValidadeComposicao(quantidade, tamcor, area);
}

void processaComposicao(char *nomeArquivo, ListaComposicao *lista){
    FILE *arq;
    printf("Abrindo arquivo %s\n", nomeArquivo);
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo\n");
        fclose(arq);
        free(arq);
        return;
    }

    int area = 0;
    char *token;
    char *linha = (char*)malloc(10*sizeof(char));
    while(!feof(arq)){
        fgets(linha, 10, arq);
        leLinhaComposicao(linha, token, lista, &area);
    }
    fclose(arq);
    free(arq);
    free(linha);
    free(token);
    if(area != 36){
        printf("Composicao do Kit Invalida.\n");
        destroiListaComposicao(lista);
        exit(1);
    }
}

void processaConfiguracao(char *nomeArquivo, ListaComposicao *lista, Matriz *matriz){
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo\n");
        fclose(arq);
        free(arq);
        return;
    }
    ListaComposicao *listaCopia = copiaListaComposicao(lista);
    char *token;
    char *linha = (char*)malloc(15*sizeof(char));
    int itera = 0;
    bool valido = true;
    while(!feof(arq)){
        printf("\t\t----------ITERACAO %d----------\n", itera);
        fgets(linha, 15, arq);

        if(strcmp(linha, "\n") == 0 || feof(arq)){  //tem q pegar um álem do eof, senão exclui a última bomba, arrumar
            if(valido){
                printf("\n\t\t\t\tPROCESSANDO CONFIGURACAO DO KIT\n\n");
                if(!listaComposicaoVazia(listaCopia))
                    printf("A configuracao eh valida porem nao atende a composicao especificada"
                    " pois nem todos os elementos da composicao foram utilizados.\n");
                else
                    printf("A configuracao do Kit eh valida!\n");
                imprime(matriz);
            }
            reinicia(lista, listaCopia, matriz);
            //imprimeListaComposicao(listaCopia);
            //imprime(matriz);
            valido = true;
            itera = 0;
            continue;
        }

        if(!valido) continue;

        //se exprode 
        if(leLinhaConfiguracao(linha, token, listaCopia, matriz)){
            valido = false;
        }

        itera++;
    }
    fclose(arq);
    free(arq);
    free(linha);
    free(token);
    destroiListaComposicao(listaCopia);
    free(listaCopia);
}

int main(int argc, char *argv[]){

    Matriz *teste = criaMatriz();

    printf("\tTestes lista\n");
    ListaComposicao *lista = criaListaComposicao();
    printf("\tInserindo elementos\n");
    processaComposicao(argv[1], lista);
    printf("\tImprimindo elementos\n");
    imprimeListaComposicao(lista);

    printf("\tTestes configuracao\n");
    processaConfiguracao(argv[2], lista, teste);
    
    printf("\tImprimindo matriz.\n");
    imprime(teste);
    imprimeListaComposicao(lista);
    printf("\tDestruindo elementos\n");
    destroiListaComposicao(lista);
    destroiMatriz(teste);
    free(teste);
    free(lista);

    return 0;
}
