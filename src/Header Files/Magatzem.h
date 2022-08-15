#pragma once
#include <map>
#include <queue>
#include <string>
#include <fstream>
#include <cmath>

#include "Comanda.h"
#include "Entitat.h"

/**
* La clase Magatzem gestiona el estoc de la empresa antes de ser enviado a tiendas.
* En el almacen se pasan controles de calidad para notificar a la empresa del estado en el que llega el pedido.
* El almacen tambien genera la factura final en funcion del estado con el que llega el pedido.
* 
**/

class Magatzem : public Entitat
{
public:
	Magatzem() {}
	Magatzem(string nom, string codi) : Entitat(nom, codi) { m_stock = {}; }
	void enmagatzemarComanda(vector<Bicicleta*>& paquet, Data dataEntrada);
	float procesQA(Comanda& c, vector<Bicicleta*>& paquet, Data dataActual);
	bool rebreComanda(Comanda& c, vector<Bicicleta*>& paquet, Data dataRecepcioPaquet);
	void generaFactura(bool paquetComplet, float costCorregit, Comanda& c);
	Bicicleta* agafaBicicletaAntiga(const string& model);
	void mostraCataleg();

	/*string getNom() const { return m_nomMagatzem; }
	void setNom(string nom) { m_nomMagatzem = nom; }
	string getCodi() const { return m_codiMagatzem; }
	void setCodi(string codi) { m_codiMagatzem = codi; }*/
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> getStock() const { return m_stock; }
	
private:
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> m_stock;
	/*string m_nomMagatzem;
	string m_codiMagatzem;*/
	float m_taxaEndarreriment = 1.1f;
};
