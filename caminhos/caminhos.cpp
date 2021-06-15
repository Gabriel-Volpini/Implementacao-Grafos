#include <iostream>
#include <list>
using namespace std;


class Vertice {
	int numeroVertice;
	list<int> *adjacente;


	void imprimeTodosCaminhosFim(int, int, bool[], int[], int&);

public:
	Vertice(int V);
	void addVertice(int v, int w);
	void imprimeTodosCaminhos(int s, int d);
};

Vertice::Vertice(int V){
	this->numeroVertice  = V;
	adjacente  = new list<int>[V];
}

void Vertice::addVertice(int v, int w){
	adjacente[v].push_back(w);
}


void Vertice::imprimeTodosCaminhos(int s, int d){

	bool* visitado = new bool[numeroVertice];

	int* caminho = new int[numeroVertice];
	int index = 0;


	for (int i = 0; i < numeroVertice; i++)
		visitado[i] = false;


	imprimeTodosCaminhosFim(s, d, visitado, caminho, index);
}

void Vertice::imprimeTodosCaminhosFim(int u, int d, bool visitado[],
							int caminho[], int& index){
	visitado[u] = true;
	caminho[index] = u;
	index++;

	if (u == d) {
		for (int i = 0; i < index; i++)
			cout << caminho[i] << " ";
		cout << endl;
	}
	else{

		list<int>::iterator i;
		for (i = adjacente[u].begin(); i != adjacente[u].end(); ++i)
			if (!visitado[*i])
				imprimeTodosCaminhosFim(*i, d, visitado, caminho, index);
	}


	index--;
	visitado[u] = false;
}

int main(){

	Vertice g(10);
	g.addVertice(0, 1);
	g.addVertice(0, 2);
	g.addVertice(0, 3);
	g.addVertice(2, 0);
	g.addVertice(2, 1);
	g.addVertice(1, 3);
	g.addVertice(1, 4);
	g.addVertice(1, 5);
	g.addVertice(5, 2);
    g.addVertice(2, 0);

	int s, d;
	cout << "Digite a raiz e o final" << endl;
	cin >> s >> d;
	cout << "Todos os caminhos de " << s << " para " << d << endl;
	g.imprimeTodosCaminhos(s, d);

	return 0;
}