#include "Graf.h"

int Graf::getPes(Node* inici, Node* desti)
{
    vector<Node*>::iterator pos1 = find(m_nodes.begin(), m_nodes.end(), inici);
    vector<Node*>::iterator pos2 = find(m_nodes.begin(), m_nodes.end(), desti);

    int pes = distance(pos1, pos2);

    return pes;
}

int Graf::getIndex(Node* vertex)
{
    int index = 0;
    for (int i = 0; i < m_nodes.size(); i++)
    {
        if (vertex->botiga->getCodi() == m_nodes[i]->botiga->getCodi())
        {
            index = i;
            break;
        }
    }
    return index;
}

Node* Graf::distanciaMinima()
{
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < m_nodes.size(); i++)
    {
        if (!m_nodes[i]->visitat && m_nodes[i]->distanciaMinima <= min)
        {
            min = m_nodes[i]->distanciaMinima;
            minIndex = i;
        }
    }
    return m_nodes[minIndex];
}

vector<Node*> Graf::dijkstra(Node* nodeInici)
{
    for (int i = 0; i < m_nodes.size(); i++) {
        m_nodes[i]->visitat = false;
    }

    int pos = getIndex(nodeInici);
    m_nodes[pos]->distanciaMinima = 0;
    for (int i = 0; i < m_numNodes - 1; i++) {
        Node* aux = distanciaMinima();
        pos = getIndex(aux);
        m_nodes[pos]->visitat = true;
        for (int j = 0; j < m_numNodes; j++) {
            if (!m_nodes[j]->visitat) {
                if (matriu_adj[pos][j] != -1) {
                    if (m_nodes[pos]->distanciaMinima + matriu_adj[pos][j] < m_nodes[j]->distanciaMinima)
                        m_nodes[j]->distanciaMinima = m_nodes[pos]->distanciaMinima + matriu_adj[pos][j];
                    else{
                        if (m_nodes[j]->distanciaMinima == INT_MAX)
                            m_nodes[j]->distanciaMinima = m_nodes[pos]->distanciaMinima + matriu_adj[pos][j];
                    }
                }
            }
        }
    }

    return m_nodes;
}


Graf::Graf(vector<Botiga*> llistaVertexs, vector<Aresta> llistaArestes)
{
    for (int j = 0; j < llistaVertexs.size(); j++) {
        Node aux = Node(llistaVertexs[j]);
        m_nodes.push_back(new Node(aux));
    }
    m_numNodes = m_nodes.size();
    m_arestes = llistaArestes;
    m_numArestes = llistaArestes.size();
    matriu_adj.resize(m_numNodes);
    for (int i = 0; i < m_numNodes; i++) {
        matriu_adj[i].resize(m_numNodes, -1);
    }
    if (m_numNodes >= m_numArestes) {
        for (int i = 0; i < m_numArestes; i++) {
            matriu_adj[i][m_arestes[i].desti] = m_arestes[i].pes;
            matriu_adj[m_arestes[i].desti][i] = m_arestes[i].pes;
        }
    }
    else {
        for (int i = 0; i < m_numArestes - (m_numArestes - m_numNodes); i++) {
            matriu_adj[i][m_arestes[i].desti] = m_arestes[i].pes;
            matriu_adj[m_arestes[i].desti][i] = m_arestes[i].pes;
        }
    }
    
}

vector<Node*> Graf::getVertexs() const
{
    return m_nodes;
}

vector<vector<int>> Graf::getArestes() const
{
    return matriu_adj;
}

vector<Botiga*> Graf::getBotiguesOrdenades(Node* nodeInici)
{
    vector<Node*> aux = dijkstra(nodeInici);
    vector<int> distancias;
    vector<Botiga*> tiendas;

    vector<Node*>::iterator it = aux.begin();
    while (it != aux.end())
    {
        distancias.push_back((*it)->distanciaMinima);
        it++;
    }
        
    sort(distancias.begin(), distancias.end());
    distancias.erase(unique(distancias.begin(), distancias.end()), distancias.end());
    distancias.erase(distancias.begin());

    vector<int>::iterator it_dist = distancias.begin();
    while (it_dist != distancias.end())
    {
        vector<Node*>::iterator i = aux.begin();
        for (i; i != aux.end(); i++) {
            if ((*it_dist) == (*i)->distanciaMinima)
                tiendas.push_back((*i)->botiga);
        }
        it_dist++;
    }
    
    vector<Node*>::iterator it_nodes = m_nodes.begin();
    while (it_nodes != m_nodes.end())
    {
        (*it_nodes)->distanciaMinima = INT_MAX;
        (*it_nodes)->visitat = false;
        it_nodes++;
    }

    return tiendas;
}

Graf& Graf::operator=(Graf g)
{
    // TODO: Insertar una instrucción "return" aquí
    return g;
}
