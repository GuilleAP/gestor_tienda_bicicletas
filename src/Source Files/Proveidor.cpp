#include "Proveidor.h"
#include "utils.h"
#include "BicicletaInfantil.h"


//Generamos una fecha aleatoria
Data Proveidor::generaDataEnviament(Data dataprevista, int diesmaxim) {
	int dies = rand() % ((diesmaxim + 1) - (-diesmaxim));
	return dataprevista + dies;
}

bool Proveidor::procesaComanda(Comanda c, Magatzem& m)
{
	vector<lineaComanda> comandaBicicletes = c.getLlistaComanda();
	vector<Bicicleta*> bici;
	vector<lineaComanda>::iterator it = comandaBicicletes.begin();
	int i = 0;
	for (it; it != comandaBicicletes.end(); it++) {
		int quantitat = (*it).m_quantitat;
		for (int j = 0; j < quantitat; j++) {
			Bicicleta* bicicleta = new Bicicleta();
			switch ((*it).tipus) {
			case TipusBicicleta::MTB: {
				BicicletaMTB* biciMTB = new BicicletaMTB((*it).m_model, "MTB", 2020, randomTalla(), randomQuadre(), randomRoda(), randomFre(), (*it).tipus, randomCategoria(), randomModalitat(), randomBool());
				bici.push_back(biciMTB);
				break;
			}
			case TipusBicicleta::INFANTIL: {
				BicicletaInfantil* biciInfantil = new BicicletaInfantil((*it).m_model, "MTB", 2020, randomTalla(), randomQuadre(), randomRoda(), randomFre(), (*it).tipus, randomBool());
				bici.push_back(biciInfantil);
				break;
			}
			case TipusBicicleta::CARRETERA: {
				BicicletaCarretera* biciCarretera = new BicicletaCarretera((*it).m_model, "MTB", 2020, randomTalla(), randomQuadre(), randomRoda(), randomFre(), (*it).tipus, randomModalitatC(), randomBool());
				bici.push_back(biciCarretera);
				break;
			}
			}
		}
		i++;
	}

	return m.rebreComanda(c, bici, generaDataEnviament(c.getDataEntregaPrevista(), 10));
}

