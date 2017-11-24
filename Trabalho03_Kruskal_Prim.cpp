#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
#include <fstream>
#include <string>
#include <list>
#include <stack>

using namespace std;

class Aresta
{
	int v1, v2, peso;

public:

	Aresta(int v1, int v2, int peso);
	int getV1();
	int getV2();
	int obterPeso();
	// sobrecarga "<"
	bool operator < (const Aresta& aresta2) const;

};


Aresta::Aresta(int v1, int v2, int peso)
{
	this->v1 = v1;
	this->v2 = v2;
	this->peso = peso;
}

int Aresta::getV1()
{
	return v1;
}

int Aresta::getV2()
{
	return v2;
}

int Aresta::obterPeso()
{
	return peso;
}

bool Aresta::operator < (const Aresta& aresta2) const
{
	return (peso < aresta2.peso);
}

//aqui classe grafo usado para o algoritmo kruskal
class Grafo
{
	int V; // número de vértices
	vector<Aresta> arestas; // vetor_verticesor de arestas

public:

	Grafo(int V);
	void adicionarAresta(int v1, int v2, int peso);
	//busca o subconjunto de um elemento "i"
	int buscar(int subset[], int i);
	// une dois subconjuntos em um único subconjunto
	void unir(int subset[], int v1, int v2);
	/// função que roda o algoritmo de Kruskal
	void kruskal();
	/// função que roda o algoritmo de Prim
	void prim();
};

Grafo::Grafo(int V)
{
	this->V = V;
}

void Grafo::adicionarAresta(int v1, int v2, int peso)
{
	Aresta aresta(v1, v2, peso);
	arestas.push_back(aresta);
}

int Grafo::buscar(int subset[], int i)
{
	if(subset[i] == -1)
		return i;
	return buscar(subset, subset[i]);
}

void Grafo::unir(int subset[], int v1, int v2)
{
	int v1_set = buscar(subset, v1);
	int v2_set = buscar(subset, v2);
	subset[v1_set] = v2_set;
}

void Grafo::kruskal()
{
	cout << "Kruskal: " << endl;
	vector<Aresta> arvore;
	int size_arestas = arestas.size();

	// ordena as arestas pelo menor peso
	sort(arestas.begin(), arestas.end());

	// aloca memória para criar "V" subconjuntos
	int * subset = new int[V];

	// inicializa todos os subconjuntos como conjuntos de um único elemento
	memset(subset, -1, sizeof(int) * V);

	for(int i = 0; i < size_arestas; i++)
	{
		int v1 = buscar(subset, arestas[i].getV1());
		int v2 = buscar(subset, arestas[i].getV2());

		if(v1 != v2)
		{
			// se forem diferentes é porque NÃO forma ciclo, insere no vetor_verticesor
			arvore.push_back(arestas[i]);
			unir(subset, v1, v2); // faz a união
		}
	}

	int size_arvore = arvore.size();

	int valor = 0;
	// mostra as arestas selecionadas com seus respectivos pesos
	for(int i = 0; i < size_arvore; i++)
	{
		char v1 = 'A' + arvore[i].getV1();
		char v2 = 'A' + arvore[i].getV2();
		cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
		valor += arvore[i].obterPeso();
	}

	cout << "Custo: " << valor << endl;
}

void Grafo::prim()
	{
		cout << "Prim: " << endl;
		bool vertice;
		int n;
		stack <int> pilha_valores;
		string STRING, str = "", str2 = "";
		ifstream infile;
		infile.open("ExemploGrafo.txt");

		while(!infile.eof())
		{
			if (vertice == false)
			{
				infile >> str;
				n = atoi(str.c_str());

				vertice = true;
			}
			else
			{
				infile >> str;
				pilha_valores.push(atoi(str.c_str()));
			}
		}

		int mArestas[n][n];

		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = n - 1; j >= 0; j--)
			{
				mArestas[i][j] = pilha_valores.top();
				pilha_valores.pop();
			}
		}

		int vetor_vertices[n];

		for(int i = 0; i < n; i++)
		{
			vetor_vertices[i] = -1; //inicializaçao do vetor_verticesor de vertices
		}
		
		vetor_vertices[0] = 0; //inicializaçao do primeiro vertice
		bool flag1 = true;
		int valor = 0;

		while(flag1)
		{
			int menor = 9999999;
			int aux1, aux2;
			bool flag2 = true;
			bool flag3 = false;
			for(int i = 0; i < n; i++)
			{
				if(vetor_vertices[i] >= 0) //verifica se o vertice "i" ja esta no vetor_vertice
				{
					for(int j = 0; j < n; j++)
					{
						for(int k = 0; k < n; k++)//verifica se o vertice "j" ja esta no vetor_vertice
						{
							if(vetor_vertices[k] == j)
							{
								flag2 = false;
								break;
							}
						}
						if(flag2)
						{
							if((mArestas[vetor_vertices[i]][j] < menor) && (mArestas[vetor_vertices[i]][j] >= 0)) //busca o menor caminho saindo dos vertices do vetor_verticesor
							{
								menor = mArestas[vetor_vertices[i]][j];
								aux1 =  vetor_vertices[i];
								aux2 = j;
								flag3 = true;
							}
						}
						flag2 = true;
					}
				}

			}
			if(flag3)
			{
				valor += menor; //incrementa o valor total
			}
			int cont = 0;
			for(int i = 0; i < n; i++)
			{

				if(vetor_vertices[i] == -1)
				{
					char v1 = 'A' + aux1;
					char v2 = 'A' + aux2;
					cout << "(" << v1 << ", " << v2 << ") = " << menor << endl;
					vetor_vertices[i] = aux2;//adiciona o vertice n vetor_vertice
					break;
				}
				else
				{
					cont++;
				}
				if(cont == n) //verifica se o vetor_vertice esta cheio
				{
					flag1 = false;
					cout << "Custo: " << valor << endl;
				}
			}
		}
	}

int main(int argc, char *argv[])
{
	int numero_vertices;
	bool vertice;
	stack <int> pilha_valores;
	string STRING, str = "", str2 = "";
	ifstream infile;
	infile.open("ExemploGrafo.txt");

	while(!infile.eof())
	{
		if (vertice == false)
		{
			infile >> str;
			numero_vertices = atoi(str.c_str());

			vertice = true;
		}
		else
		{
			infile >> str;
			pilha_valores.push(atoi(str.c_str()));
		}
	}

	int matriz[numero_vertices][numero_vertices];
	Grafo g(numero_vertices);

	for (int i = numero_vertices - 1; i >= 0; i--)
	{
		for (int j = numero_vertices - 1; j >= 0; j--)
		{
			matriz[i][j] = pilha_valores.top();
			pilha_valores.pop();
		}
	}


	for (int i = 0; i < numero_vertices; i++)
	{
		for (int j = 0; j < numero_vertices; j++)
		{
			if (matriz[i][j] != -1)
			{
				g.adicionarAresta(i, j, matriz[i][j]);
			}
		}
	}

	g.kruskal(); // roda o algoritmo de Kruskal
	cout << endl;
	g.prim(); // roda o algoritmo de Prim

	infile.close();
	return 0;
}
