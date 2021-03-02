#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROTEADOR 255


int main()
{
    int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112},
            vB[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112},
            vA[] = {1, 1, 1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
    int *Vert, vertCont = 0;
    for(int i=0;i<26;i++){
        if(vA[i]!=vA[i+1]){
            vertCont++;
        }
    }
    vertCont++;
    Vert=malloc(vertCont*sizeof(int));
    vertCont=0;
    for(int i = 0; i < 26; i++){
        if(vA[i] != vA[i + 1]){
            Vert[vertCont++] = i;
        }
    }
    Vert[vertCont] = 27;
    printf("%d\n", Vert[vertCont]);
    for(int i = 0; i <=vertCont; i++){
        printf("vertCont:%d\tVert:%d\n", vertCont, Vert[i]);
    }

    return 0;
}
