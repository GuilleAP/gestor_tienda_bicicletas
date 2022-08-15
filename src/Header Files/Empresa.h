#pragma once
#include <string>
#include <vector>
#include "Botiga.h"
#include "Magatzem.h"
#include "Comanda.h"
#include "Proveidor.h"
#include "Graf.h"

/**
 *
* La clase empresa aglutina la inforamcion para gestionar la comunicacion del almacen con el proveedor, asi como las tiendas.
* La empresa se define por un conjunto de tiendas, un almacen y un proveedor.
* La empresa realizar� pedidos al provedor y recibira una notificacion indicando si el pedido ha llegado correctamente a almacen.
* 
**/
enum class EstatBicicleta {
	EN_MAGATZEM,
	EN_BOTIGA,
	VENUDA,
	RETORNADA
};

struct DadesSeguiment {
	Bicicleta* m_bicicleta;
	vector<pair<EstatBicicleta, Entitat*>> m_historic;
	DadesSeguiment() {
		m_bicicleta = nullptr;
		m_historic = vector<pair<EstatBicicleta, Entitat*>>();
	}
};

static int m_codiUnic = 0;
static map<string, DadesSeguiment> m_taulaSeguiment;

class Empresa
{
public:
	Empresa() { m_magatzem = nullptr; m_nBotigues = 0; }
	Empresa(string name, int numBotigues, Magatzem* magatzemPrincipal, Proveidor& p);
	Empresa(string name, vector<Botiga*> botigues, vector<Aresta> conexionsBotigues, Magatzem* magatzemPrincipal, Proveidor& p);
	string getName() const { return m_nom; }
	Magatzem* getMagatzem() { return m_magatzem; }
	vector<Botiga*>& getBotigues() { return this->m_botigues; }
	void setProveidor(Proveidor& proveidor) { m_proveidor = proveidor; }
	Proveidor& getProveidor() { return m_proveidor; }
	void afegeixBotiga(Botiga* b);
	static int getSeguentCodiRus() { return m_codiUnic; }

	bool realitzaComanda(Comanda& c, Proveidor& p);
	string static generaCodiRus(const string& model);

	bool realitzaComanda(Comanda& c);
	static bool afegeixSeguiment(Bicicleta* bicicleta);
	static bool actualitzaEstat(const string& codiRus, EstatBicicleta nouEstat, Entitat* novaEntitat);
	static bool comprobaEstatCodi(string codiRus, EstatBicicleta objectiu);


private:
	string m_nom;
	int m_nBotigues;
	Magatzem* m_magatzem;
	Botiga m_botiga;
	Proveidor m_proveidor;
	vector<Botiga*> m_botigues;
	vector<Aresta> m_conexions;
};
