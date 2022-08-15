#pragma once
#include <limits.h>
#include "Botiga.h"
#include <algorithm>
#include <vector>


struct Node
{
	bool visitat;
	Botiga* botiga;
	int distanciaMinima;
	Node(Botiga* b) :visitat(false), botiga(b), distanciaMinima(INT_MAX) {}
};

struct Aresta
{
	int inici, desti, pes;
};
class Graf
{
private:
	const int ARESTA_NULA = -1;
	
	int getPes(Node* inici, Node* desti);
	int getIndex(Node* vertex);
	Node* distanciaMinima();
	vector<Node*> dijkstra(Node* nodeInici);
	int m_numNodes;
	int m_numArestes;
	vector<Aresta> m_arestes;
	vector<Node*> m_nodes;
	vector<vector<int>> matriu_adj;

public:
	Graf() {
		m_numArestes = 0;
		m_numNodes = 0;
	}
	Graf(vector<Botiga*> llistaVertexs, vector<Aresta> llistaArestes);
	vector<Node*> getVertexs() const;
	vector<vector<int>> getArestes() const;
	vector<Botiga*> getBotiguesOrdenades(Node* nodeInici);
	Graf& operator=(Graf g);
};

