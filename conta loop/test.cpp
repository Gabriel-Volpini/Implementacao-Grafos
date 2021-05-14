
#include <stdio.h>
#include<iostream>
#include<list>

using namespace std;
 
class Vertice {
    int numeroVertice;  
    list<int> *adjacente;   
    bool calculaCiclo(int v, bool visitado[], bool *pilha);  
public:
    Vertice(int V);   
    void addVertice(int v, int w); 
    int possuiLoop();  
};
 
Vertice::Vertice(int V) {
    this->numeroVertice = V;
    adjacente = new list<int>[V];
}
 
void Vertice::addVertice(int v, int w){
    adjacente[v].push_back(w); 
}
 
bool Vertice::calculaCiclo(int v, bool visitado[], bool *pilha){

    if(visitado[v] == false){
        visitado[v] = true;
        pilha[v] = true;
 
        list<int>::iterator i;
        for(i = adjacente[v].begin(); i != adjacente[v].end(); ++i){
            if ( !visitado[*i] && calculaCiclo(*i, visitado, pilha) )
                return true;
            else if (pilha[*i])
                return true;
        }
 
    }
    pilha[v] = false;  
    return false;
}
 
int Vertice::possuiLoop(){

    bool *visitado = new bool[numeroVertice];
    bool *pilha = new bool[numeroVertice];
    for(int i = 0; i < numeroVertice; i++){
        visitado[i] = false;
        pilha[i] = false;
    }
    int count = 0;

    for(int i = 0; i < numeroVertice; i++)
        if (calculaCiclo(i, visitado, pilha))
            count++;

    return count;
}
 

int main() {
    Vertice g(4);

    //1 ciclo simples
    
    g.addVertice(1,2);
    g.addVertice(2,3);
    g.addVertice(3,1);
 
    //2 ciclos complexo
    // g.addVertice(0, 1);
    // g.addVertice(0, 2);
    // g.addVertice(1, 2);
    // g.addVertice(2, 0);
    // g.addVertice(2, 3);
    // g.addVertice(3, 3);

    cout << "O grafo contem: " << g.possuiLoop() << " ciclos!";
    return 0;
}