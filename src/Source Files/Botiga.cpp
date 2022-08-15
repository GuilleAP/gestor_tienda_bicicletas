#include "Botiga.h"
#include "Empresa.h"
//La botiga sol·licita una comanda al magatzem.
bool Botiga::solicitaComanda(const Comanda& c, Magatzem& m) {
	vector<lineaComanda> comanda = c.getLlistaComanda();
	vector<lineaComanda>::const_iterator it = comanda.begin();
	bool noEsta = true;
	//Recorremos todas la comanda
	while(it != comanda.end()) {
		priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta> bicicletes;
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
		else {
			modelTipus = model;
		}
		int q = (*it).m_quantitat;
		//Cogemos cada una de las bicicletas de la comanda y las ponemos en el stock de la tienda.
		for (int i = 0; i < q; i++) {
			Bicicleta* b = new Bicicleta();
			b = m.agafaBicicletaAntiga(modelTipus);
			if (b->getModel() == "") {
				noEsta = false;
			}
			else {
				bicicletes.push(b);
				Empresa::actualitzaEstat(b->getCodiRus(), EstatBicicleta::EN_BOTIGA, this);
				map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator aux = m_stockBotiga.begin();
				aux = m_stockBotiga.find(modelTipus);
				if (aux == m_stockBotiga.end()) {
					m_stockBotiga.insert(pair<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> (modelTipus, bicicletes));
				}
				else {
					m_stockBotiga[modelTipus].push(b);
				}
			}
		}
		it++;
	}
	return noEsta;
}

bool Botiga::solicitaComanda(Comanda& c)
{
	
	vector<lineaComanda> comanda = c.getLlistaComanda();
	vector<lineaComanda>::const_iterator it = comanda.begin();
	bool noEsta = true;
	if (this->getMagatzem() != nullptr)
	{
		//Recorremos todas la comanda
		while (it != comanda.end()) {
			priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta> bicicletes;
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
			else {
				modelTipus = model;
			}
			int q = (*it).m_quantitat;
			//Cogemos cada una de las bicicletas de la comanda y las ponemos en el stock de la tienda.
			for (int i = 0; i < q; i++) {

				Bicicleta* b = new Bicicleta();
				Magatzem* m = this->magatzem;
				b = m->agafaBicicletaAntiga(modelTipus);
				if (b->getModel() == "") {
					noEsta = false;
				}
				else {
					bicicletes.push(b);
					Empresa::actualitzaEstat(b->getCodiRus(), EstatBicicleta::EN_BOTIGA, this);
					map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator aux = m_stockBotiga.begin();
					aux = m_stockBotiga.find(modelTipus);
					if (aux == m_stockBotiga.end()) {
						m_stockBotiga.insert(pair<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>(modelTipus, bicicletes));
					}
					else {
						m_stockBotiga[modelTipus].push(b);
					}
				}
			}
			it++;
		}
		
	}
	else
		noEsta = false;
	
	return noEsta;
}

//Función que muestra el catálogo de bicicletas.
void Botiga::mostraCataleg() {
	std::map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator it = m_stockBotiga.begin();
	cout << "Botiga: " << m_nom << "   Codi: " << m_codi << endl;
	cout << "_____________________________________________" << endl;

	while (it != m_stockBotiga.end())
	{
		cout << (*it).first << endl;
		it++;
	}

	cout << endl << endl;
}

//Calculamos el stock de la tienda.
int Botiga::calculaStockTotal() {
	int stock = 0;
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator it = m_stockBotiga.begin();
	for(it; it != m_stockBotiga.end(); it++)
		stock = stock + (*it).second.size();
	return stock;
}

vector<Botiga*> Botiga::getBotiguesProperes()
{
	return vector<Botiga*>();
}

Magatzem* Botiga::getMagatzem()
{
	return magatzem;
}

void Botiga::setMatgatzem(Magatzem* m)
{
    magatzem = m;
}

void Botiga::setveinesOrdenades(vector<Botiga*> veines)
{
}

bool Botiga::solicitaBicicletaAMagatzem(const string& model, Bicicleta*& bicicleta)
{
	map< string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> stock = magatzem->getStock();
	std::map< string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator itm = stock.find(model);

	if (itm == stock.end() || (*itm).second.size() == 0)
		return false;
	else {
		bicicleta = (*itm).second.top();
		(*itm).second.pop();
		return true;
	}
}

bool Botiga::procesa_venda(const string& model, Bicicleta*& bicicleta)
{
	if (!comprobaBicicletaEnStock(model, bicicleta)) 
	    if (!ComprobaStockEnVeines(model, bicicleta))
            if (!solicitaBicicletaAMagatzem(model, bicicleta)) 
                return false;
    return true;
}

bool Botiga::comprobaBicicletaEnStock(const string& model, Bicicleta*& bicicleta)
{
	if (magatzem->getStock()[model].size() != 0 && !magatzem->getStock().empty()) {
		bicicleta = magatzem->getStock()[model].top();
		magatzem->getStock()[model].pop();
		return true;
	}
	return false;
}

bool Botiga::ComprobaStockEnVeines(const string& model, Bicicleta*& bicicleta)
{
	return false;
}
