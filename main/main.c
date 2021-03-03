#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CAMINHO_ARQUIVO "data.txt"
#define TAMANHO_GRAFO 6 //"(entrada,saida)"

//padrão  (entrada,saida) 

int main(void) {
    FILE *arquivo = fopen( CAMINHO_ARQUIVO, "r" );
    if( !arquivo ) perror(CAMINHO_ARQUIVO), exit(1);

    char itemGrafo[TAMANHO_GRAFO];

    while (fgets(itemGrafo, TAMANHO_GRAFO, arquivo) != NULL){
        
        //Separando os valores de entrada e saída das outros chars do arquvo
        char entradaAtual = itemGrafo[1], saidaAtual = itemGrafo[3]; 

        printf("%c %c\n",entradaAtual,saidaAtual);

        //Implementar codigo ak gabrielly
    }

    printf("Fechando arquivo..");
    fclose(arquivo);
    return 0;
}