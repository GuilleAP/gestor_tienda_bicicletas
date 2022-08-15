#include "Empresa.h"

bool Empresa::realitzaComanda(Comanda& c)
{
	return false;
}

bool Empresa::afegeixSeguiment(Bicicleta* bicicleta)
{
	if (bicicleta != nullptr && bicicleta->getCodiRus() != "")
	{
		if (m_taulaSeguiment.find(bicicleta->getCodiRus()) == m_taulaSeguiment.end()) {
			DadesSeguiment dades = DadesSeguiment();
			dades.m_bicicleta = bicicleta;
			string codiRus = bicicleta->getCodiRus();
			m_taulaSeguiment.insert(pair<const string, DadesSeguiment>(codiRus, dades));
			return true;
		}
	}
	
	return false;
}

bool Empresa::actualitzaEstat(const string& codiRus, EstatBicicleta nouEstat, Entitat* novaEntitat)
{
	if (m_taulaSeguiment.find(codiRus) != m_taulaSeguiment.end() && novaEntitat != nullptr && codiRus != "") {
		m_taulaSeguiment[codiRus].m_historic.push_back({nouEstat,novaEntitat});
		return true;
	}
	return false;
}

bool Empresa::comprobaEstatCodi(string codiRus, EstatBicicleta objectiu)
{
	if (m_taulaSeguiment.count(codiRus) > 0)
	{
		bool flag = false;
		vector<pair<EstatBicicleta, Entitat*>> historial = m_taulaSeguiment[codiRus].m_historic;
		vector<pair<EstatBicicleta, Entitat*>>::iterator it = historial.begin();
		while (!flag && it != historial.end())
		{
			flag = (*it).first == objectiu;
			++it; 
		}
		return flag;
	}
	return false;

}

//Creamos las tiendas necesarias
Empresa::Empresa(string name, int numBotigues, Magatzem* magatzemPrincipal, Proveidor& p) {
	m_nom = name;
	m_nBotigues = numBotigues;
	m_magatzem = magatzemPrincipal;
	m_proveidor = p;
	for (int i = 0; i < m_nBotigues; i++) {
		string nomBotiga = "Botiga_" + to_string(i);
		Botiga* botiga = new Botiga(nomBotiga, to_string(i));
		m_botigues.push_back(botiga);
	}
}

Empresa::Empresa(string name, vector<Botiga*> botigues, vector<Aresta> conexionsBotigues, Magatzem* magatzemPrincipal, Proveidor& p)
{
    m_nom = name;
	m_botigues = botigues;
	m_conexions = conexionsBotigues;
	m_magatzem = magatzemPrincipal;
	m_proveidor = p;
    Graf graf(botigues, conexionsBotigues);
	for (int i = 0; i < botigues.size(); i++)
	{
		botigues[i]->setMatgatzem(magatzemPrincipal);
		botigues[i]->setveinesOrdenades(graf.getBotiguesOrdenades(graf.getVertexs()[i]));
	}
}

//Añadir una tienda nueva
void Empresa::afegeixBotiga(Botiga* b) {
	m_botigues.push_back(b);
	m_nBotigues++;
}

//La tienda realiza una comanda al proveidor
bool Empresa::realitzaComanda(Comanda& c, Proveidor& p) {
	return p.procesaComanda(c, *m_magatzem);
}

//Generamos un código único para cada bicicleta
string Empresa::generaCodiRus(const string& model) {
	m_codiUnic = getSeguentCodiRus();
	string cadena = to_string(m_codiUnic);
	m_codiUnic++;
	return model + cadena;
}


