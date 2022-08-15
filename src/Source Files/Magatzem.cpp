#include "Magatzem.h"
#include "Empresa.h"

//Cogemos la comanda que nos pasa el proveedor y la almacenamos en Magatzem.
void Magatzem::enmagatzemarComanda(vector<Bicicleta*>& paquet, Data dataEntrada) {
	vector<Bicicleta*>::iterator it = paquet.begin();
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator aux = m_stock.begin();
	//Recorremos cada una de las bicicletas de paquet
	for (it = paquet.begin(); it != paquet.end(); it++) {
		Empresa e;
		
		(*it)->setDataEntrada(dataEntrada);
		string model = (*it)->getModel();
		string modelTipus;
		if (model == "A" || model == "B") {
			switch ((*it)->getTipus()) {
			case TipusBicicleta::CARRETERA:
				modelTipus = "CTR_" + model;
				break;
			case TipusBicicleta::INFANTIL:
				modelTipus = "INF_" + model;
				break;
			case TipusBicicleta::MTB:
				modelTipus = "MTB_" + model;
			}
		}
		else {
			modelTipus = model;
		}
		string codi = e.generaCodiRus(modelTipus);
		(*it)->setCodiRus(codi);
		e.afegeixSeguiment(*it);
		e.actualitzaEstat(codi, EstatBicicleta::EN_MAGATZEM, this);
		aux = m_stock.find(modelTipus);
		if (aux == m_stock.end()) {
			priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta> bicicletes;
			bicicletes.push((*it));
			m_stock.insert(pair<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> (modelTipus, bicicletes));
		}
		else {
			m_stock[modelTipus].push((*it));
		}
	}

}

//Comprobamos que la comando que llega de magatzem llegue en el tiempo previsto y con todas las bicicletas que se han pedido. 
//Si esto no se cumple, se le aplica una penalización.
float Magatzem::procesQA(Comanda& c, vector<Bicicleta*>& paquet, Data dataActual) {
	float cost = 0;
	float penalitzacio = 0.1;
	for (int i = 0; i < paquet.size(); i++) {
		cost = cost + paquet[i]->getPreu();
	}
	if ((dataActual <= c.getDataEntregaPrevista()) || (c.getTotalBicicletes() != paquet.size()))
		penalitzacio = 0.0;
	
	return cost + (cost * penalitzacio);
}

//Almacenamos la comanda que llega de proveedor, comprobamos que ha pasado el test de calidad y generamos una factura.
bool Magatzem::rebreComanda(Comanda& c, vector<Bicicleta*>& paquet, Data dataRecepcioPaquet) {
	bool trobat = false;
	enmagatzemarComanda(paquet, dataRecepcioPaquet);
	if (procesQA(c, paquet, dataRecepcioPaquet) == c.getCostTotal())
		trobat = true;
	generaFactura(trobat, procesQA(c, paquet, dataRecepcioPaquet), c);
	return trobat;
}

//Genera una factura de la comanda que llega del proveedor.
void Magatzem::generaFactura(bool paquetComplet, float costCorregit, Comanda& c) {
	ofstream fitxer;
	string nomFitxer = "factura.txt";
	fitxer.open(nomFitxer);
	const vector<lineaComanda> comanda = c.getLlistaComanda();
	vector<lineaComanda>::const_iterator it = comanda.begin();
	if (paquetComplet) {
		fitxer << "Resum comanda." << endl;
		fitxer << "Dades Entitat responsable:" << endl;
		fitxer << "Nom: " << m_nom << endl;
		fitxer << "Codi identificatiu: " << m_codi << endl;
		fitxer << "Articles." << endl;
		while (it != comanda.end()) {
			string model = (*it).m_model;
			string modelTipus;
			if (model == "A" || model == "B") {
				switch ((*it).tipus) {
				case TipusBicicleta::CARRETERA:
					modelTipus = "CTR_" + model;
					break;
				case TipusBicicleta::INFANTIL:
					modelTipus = "INF_" + model;
					break;
				case TipusBicicleta::MTB:
					modelTipus = "MTB_" + model;
				}
			}
			fitxer << modelTipus << " * " << (*it).m_quantitat << endl;
			fitxer << endl;
			it++;
		}
		fitxer << "Preu final: " << costCorregit;
	}
	else {
		fitxer << "Resum comanda." << endl;
		fitxer << "Dades Entitat responsable:" << endl;
		fitxer << "Nom: " << m_nom << endl;
		fitxer << "Codi identificatiu: " << m_codi << endl;
		fitxer << "Articles." << endl;
		fitxer << "El paquet no pasa els test de qualitat." << endl;
		fitxer << "Es redueix el cost del paquet en un 1.1" << endl;
		fitxer << "Preu final: " << costCorregit << endl;
	}
}

//Cogemos la bicicleta que más tiempo lleva en el magatzem.
Bicicleta* Magatzem::agafaBicicletaAntiga(const string& model) {
	Bicicleta* b = new Bicicleta();
		if (m_stock[model].size() > 0) {
			b = m_stock[model].top();
			m_stock[model].pop();
		}
		return b;
}


void Magatzem::mostraCataleg() {
    
}


