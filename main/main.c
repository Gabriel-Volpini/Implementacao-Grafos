#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define DIRECIONADO "direcionado.txt"
#define NAO_DIRECIONADO "naoDirecionado.txt"
#define PONDERADO_DIRECIONADO "ponderadoDirecionado.txt"
#define PONDERADO_NAO_DIRECIONADO "ponderadoNaoDirecionado.txt"

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
            if(peso)
                vert -> proximo -> peso = peso;
        }
    }
    while(vert -> sucessor != NULL)
        vert = vert -> sucessor;
    vert -> sucessor = malloc(sizeof(grafo));
    vert -> sucessor -> vert = saidaAtual;
    vert -> sucessor -> proximo = NULL;
    vert -> sucessor -> sucessor = NULL;
    if(peso)
        vert -> sucessor -> peso = peso;

}

void imprime(grafo *vert, bool possuiPeso){
    grafo *suc;
    vert = vert -> proximo;

    while(vert != NULL){
        printf("Vertice: %d",vert -> vert);
        
        if(possuiPeso)
            printf("\tPeso:%d",vert -> peso);

        suc = vert -> sucessor;

        while(suc != NULL){
            printf("\nSucessor:%d",suc -> vert);

            if(possuiPeso)
                printf("\tPeso:%d",suc -> peso);

            suc = suc->sucessor;
        }
        printf("\n\n");
        vert = vert -> proximo;
    }
}

void caminha(grafo *vert){
    grafo *caminho;
    caminho = malloc(sizeof(grafo));
    caminho -> vert = ' ';
    caminho -> proximo = NULL;
    caminho -> sucessor = NULL;
    caminho -> peso = 0;

    vert = vert -> proximo;

    grafo *proxCaminho;
    grafo *suc;
    while(vert != NULL){
      suc = vert -> sucessor;
      proxCaminho = suc;

        while(suc != NULL){
            if(suc -> peso < proxCaminho -> peso && suc -> vert == proxCaminho -> vert){
                proxCaminho = suc;
            }
            suc = suc->sucessor;
        }
      organiza(vert->vert,proxCaminho->vert,proxCaminho->peso,caminho);
      vert = vert -> proximo;
    }

    imprime(caminho, true);
    liberaMemoria(caminho);
}

void menuGetFile (bool *possuiPeso, bool *ehDirecional, char *caminhoArquivo) {
    int resposta;
    printf("Escolha o modelo de entrada:\n1 - Direcionado\n2 - Nao direcionado\n3 - Ponderado direcionado\n4 - Ponderado nao direcionado\n");
    scanf("%d", &resposta);

    switch (resposta)
    {
    case 1:
        *possuiPeso = false;
        *ehDirecional = true;
        strcpy(caminhoArquivo, DIRECIONADO);
        break;
    case 2:
        *possuiPeso = false;
        *ehDirecional = false;
        strcpy(caminhoArquivo, NAO_DIRECIONADO);
        break;
    case 3:
        *possuiPeso = true;
        *ehDirecional = true;
        strcpy(caminhoArquivo, PONDERADO_DIRECIONADO);
        break;
    case 4:
        *possuiPeso = true;
        *ehDirecional = false;
        strcpy(caminhoArquivo, PONDERADO_NAO_DIRECIONADO);
        break;
    default:
        printf("Valor invalido, tente novamente\n\n");
        menuGetFile(possuiPeso, ehDirecional, caminhoArquivo);
    }
     
    return;
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
    bool possuiPeso = false;
    char caminhoArquivo[30] = "";
    bool ehDirecional;

    menuGetFile(&possuiPeso, &ehDirecional, caminhoArquivo);

    FILE *arquivo = fopen(caminhoArquivo, "r" );
    if( !arquivo ) perror(caminhoArquivo), exit(1);

    int entrada = 0, saida = 0, peso = 0;

    grafo *vert;
    vert = malloc(sizeof(grafo));
    vert -> vert = ' ';
    vert -> proximo = NULL;
    vert -> sucessor = NULL;
    vert -> peso = 0;

    int chegouNoFimDoArquivo = 0;

    if(possuiPeso){
        while (1){ 
            if(ehDirecional == true)
                chegouNoFimDoArquivo = fscanf(arquivo, "(%d,%d,%d),", &entrada, &saida, &peso);
            else
                chegouNoFimDoArquivo = fscanf(arquivo, "{%d,%d,%d},", &entrada, &saida, &peso);
            
            if(chegouNoFimDoArquivo == EOF) break;

            organiza(entrada, saida, peso, vert);

            if(ehDirecional == false)
                organiza(saida, entrada, peso, vert);
        }
    } else {
        while (1){
            if(ehDirecional == true)
                chegouNoFimDoArquivo = fscanf(arquivo, "(%d,%d),", &entrada, &saida, &peso);
            else
               chegouNoFimDoArquivo = fscanf(arquivo, "{%d,%d},", &entrada, &saida, &peso);
            
            if(chegouNoFimDoArquivo == EOF) break;

            organiza(entrada, saida, peso, vert);

            if(ehDirecional == false)
                organiza(saida, entrada, peso, vert);
        }
    }

    imprime(vert, possuiPeso);

    liberaMemoria(vert);
    fclose(arquivo);
    printf("\nFechando arquivo..");
    return 0;
}
