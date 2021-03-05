#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define CAMINHO_ARQUIVO "data.txt"
//padrão  (entrada,saida) ou (entrada,saida,peso)

typedef struct grafo {
    int vert;
    int peso;
    struct grafo *proximo, *sucessor;
} grafo;

void organiza(int entradaAtual, int saidaAtual, int peso, grafo *vert){
    while(vert -> vert != entradaAtual){
        if(vert -> proximo != NULL)
            vert = vert -> proximo;
        else{
            vert -> proximo = malloc(sizeof(grafo));
            vert -> proximo -> vert = entradaAtual;
            vert -> proximo -> proximo = NULL;
            vert -> proximo -> sucessor = NULL;
            vert -> proximo -> peso = peso;
        }
    }
    while(vert -> sucessor != NULL)
        vert = vert -> sucessor;
    vert -> sucessor = malloc(sizeof(grafo));
    vert -> sucessor -> vert = saidaAtual;
    vert -> sucessor -> proximo = NULL;
    vert -> sucessor -> sucessor = NULL;
    vert -> sucessor -> peso = peso;

}

void imprime(grafo *vert){
    grafo *suc;
    vert = vert -> proximo;
    int flag = 0;
    if(vert -> peso != 0)
        flag = 1;
    while(vert != NULL){
        printf("\nvertice:%d\n",vert -> vert);
        if(flag == 1)
            printf("peso:%d\n",vert -> peso);
        suc = vert -> sucessor;
        while(suc != NULL){
            printf("\tsucessor:%d",suc -> vert);
            if(flag == 1)
                printf("peso:%d",suc -> peso);

            suc = suc->sucessor;
        }
        vert = vert -> proximo;
    }
}

bool menuGetPeso () {
    int resposta;
    printf("O arquivo de texto possui peso?\n1- Sim\n2- Nao\n");
    scanf("%d", &resposta);

    if(resposta == 1) return true;
    else if(resposta == 2) return false;
    else {
        printf("Valor invalido, tente novamente\n\n");
        return menuGetPeso();
    }
}

void liberaMemoria (grafo *vert) {
    grafo *guardado, *prox, *suc;

    suc = vert -> proximo -> sucessor;
    prox = vert -> proximo;

    while(prox -> proximo != NULL){

        while(suc -> sucessor != NULL){
            guardado = suc;
            suc = suc -> sucessor;
            free(guardado);
        }
        guardado = prox;
        prox = prox -> proximo;
        suc = prox -> sucessor;
        free(guardado);
    }

    return;
}

int main(void) {
    FILE *arquivo = fopen(CAMINHO_ARQUIVO, "r" );
    if( !arquivo ) perror(CAMINHO_ARQUIVO), exit(1);

    int entrada = 0, saida = 0, peso = 0;
    bool ehDirecional;

    grafo *vert;
    vert = malloc(sizeof(grafo));
    vert -> vert = ' ';
    vert -> proximo = NULL;
    vert -> sucessor = NULL;
    vert -> peso = 0;

    char initialChar;
    fscanf(arquivo, " %c", &initialChar);
    rewind(arquivo); //resetando cursor dentro do arquivo

    if(initialChar == '{') ehDirecional = true;
    else ehDirecional = false;

    bool possuiPeso = menuGetPeso();

    if(possuiPeso){
        while (!feof (arquivo)){
            if(ehDirecional == false)
                fscanf(arquivo, "(%d,%d,%d),", &entrada, &saida, &peso);
            else
                fscanf(arquivo, "{%d,%d,%d},", &entrada, &saida, &peso);
            organiza(entrada, saida, peso, vert);
            if(ehDirecional == false)
                organiza(saida, entrada, peso, vert);
        }
    } else {
        while (!feof (arquivo)){
            if(ehDirecional == false)
                fscanf(arquivo, "(%d,%d),", &entrada, &saida, &peso);
            else
                fscanf(arquivo, "{%d,%d},", &entrada, &saida, &peso);
            organiza(entrada, saida, peso, vert);
            if(ehDirecional == false)
                organiza(saida, entrada, peso, vert);
        }
    }

    imprime(vert);

    liberaMemoria(vert);
    fclose(arquivo);
    printf("\nFechando arquivo..");
    return 0;
}
