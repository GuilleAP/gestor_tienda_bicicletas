#pragma once
#include "Magatzem.h"
#include "Entitat.h"
#include <string>

/**
* Clase para gestionar las acciones y el estoc de cada una de las tiendas que pertenecen a la empresa.
* Las tiendas pueden solicitar a un almacen un pedido.
* Cuando solicitien un pedido "recojeran" de almacen aquellos objetos que puedan, con tal de cubrir su pedido.
* Moveran los objetos del almacen a su propio estoc interno, que estar� ordenado igual que el del almacen.
* Ademas, la tienda necesita saber su estoc total.
**/

class Botiga : public Entitat
{
public:
	Botiga() { magatzem = nullptr; }
	Botiga(string nom, string codi) : Entitat(nom, codi) { magatzem = nullptr; }
	~Botiga() = default;
	bool solicitaComanda(const Comanda& c, Magatzem& m);
	bool solicitaComanda(Comanda& c);
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> getStockBotiga() const { return m_stockBotiga; }
	void mostraCataleg();
	int calculaStockTotal();
	/*string getNom() const {return m_nomBotiga;}
	void setNom(const string& nom) { m_nomBotiga = nom; }
	string getCodi() const {return m_codiBotiga;}
	void setCodi(const string& codi) { m_codiBotiga = codi; }*/

	vector<Botiga*> getBotiguesProperes();
	Magatzem* getMagatzem();
	void setMatgatzem(Magatzem* m);
	void setveinesOrdenades(vector<Botiga*> veines);

	bool solicitaBicicletaAMagatzem(const string& model, Bicicleta*& bicicleta);
	bool procesa_venda(const string& model, Bicicleta*& bicicleta);
	bool comprobaBicicletaEnStock(const string& model, Bicicleta*& bicicleta);
	bool ComprobaStockEnVeines(const string& model, Bicicleta*& bicicleta);

private:
	/*string m_nomBotiga;
	string m_codiBotiga;*/
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> m_stockBotiga;
	Magatzem* magatzem;
};
