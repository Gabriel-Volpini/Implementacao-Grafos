#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CAMINHO_ARQUIVO "data.txt"
#define TAMANHO_GRAFO 7 //"(entrada,saida)"

//padrão  (entrada,saida)

typedef struct grafo {
    int vert;
    int prio;
    struct grafo *prox,*sucessor;
} grafo;

void organiza(int entradaAtual, int saidaAtual, grafo *vert){
    while(vert -> vert != entradaAtual){
        if(vert -> prox != NULL)
            vert = vert -> prox;
        else{
            vert -> prox = malloc(sizeof(grafo));
            vert -> prox -> vert = entradaAtual;
            vert -> prox -> prox = NULL;
            vert -> prox -> sucessor = NULL;
        }
    }
    while(vert -> sucessor != NULL)
        vert = vert -> sucessor;
    vert -> sucessor = malloc(sizeof(grafo));
    vert -> sucessor -> vert = saidaAtual;
    vert -> sucessor -> prox = NULL;
    vert -> sucessor -> sucessor = NULL;
}

void imprime(grafo *vert){
    grafo *suc;
    vert = vert->prox;
    while(vert != NULL){
        printf("\nvertice:%d\n",vert->vert);
        suc = vert->sucessor;
        while(suc != NULL){
            printf("sucessor:%d\t",suc->vert);
            suc = suc->sucessor;
        }
        vert = vert->prox;
    }
}

int main(void) {
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "r" );
    if( !arquivo ) perror(CAMINHO_ARQUIVO), exit(1);

    char itemGrafo[TAMANHO_GRAFO];
    int entrada = 0, saida = 0;

    grafo *vert;
    vert = malloc(sizeof(grafo));
    vert -> vert = ' ';
    vert -> prox = NULL;
    vert -> sucessor = NULL;
    vert -> prio = 0;

    while (!feof (arquivo)){
        fscanf(arquivo, "(%d,%d),", &entrada, &saida);
        organiza(entrada, saida, vert);
    }
    imprime(vert);
    
    fclose(arquivo);
    printf("\nFechando arquivo..");
    return 0;
}
