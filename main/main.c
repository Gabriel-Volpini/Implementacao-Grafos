#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CAMINHO_ARQUIVO "data.txt"
#define TAMANHO_GRAFO 7 //"(entrada,saida)"

//padrão  (entrada,saida)

typedef struct grafo{
    char vert;
    int prio;
    struct grafo *prox,*sucessor;
} grafo;

void organiza(char entradaAtual,char saidaAtual,grafo *vert){
    while(vert->vert != entradaAtual){
        if(vert->prox != NULL)
            vert = vert->prox;
        else{
            vert->prox = malloc(sizeof(grafo));
            vert->prox->vert = entradaAtual;
            vert->prox->prox = NULL;
            vert->prox->sucessor = NULL;
        }
    }
    while(vert->sucessor != NULL)
        vert = vert->sucessor;
    vert->sucessor = malloc(sizeof(grafo));
    vert->sucessor->vert = saidaAtual;
    vert->sucessor->prox = NULL;
    vert->sucessor->sucessor = NULL;
}

void imprime(grafo *vert){
    grafo *suc;
    vert = vert->prox;
    while(vert != NULL){
        printf("\nvertice:%c\n",vert->vert);
        suc = vert->sucessor;
        while(suc != NULL){
            printf("sucessor:%c\t",suc->vert);
            suc = suc->sucessor;
        }
        vert = vert->prox;
    }
}

int main(void) {
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "r" );
    if( !arquivo ) perror(CAMINHO_ARQUIVO), exit(1);

    char itemGrafo[TAMANHO_GRAFO];
    char entradaAtual,saidaAtual;
    grafo *vert;
    vert = malloc(sizeof(grafo));
    vert->vert = ' ';
    vert->prox = NULL;
    vert->sucessor = NULL;
    vert->prio = 0;

    while (fgets(itemGrafo, TAMANHO_GRAFO, arquivo) != NULL){

        //Separando os valores de entrada e saída das outros chars do arquvo
        entradaAtual = itemGrafo[1], saidaAtual = itemGrafo[3];

        printf("%c %c\n",entradaAtual,saidaAtual);

        organiza(entradaAtual,saidaAtual, vert);
    }
    imprime(vert);
    printf("Fechando arquivo..");
    fclose(arquivo);
    return 0;
}
