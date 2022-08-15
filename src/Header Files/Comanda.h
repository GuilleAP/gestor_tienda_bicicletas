#pragma once
#include <vector>

#include "Bicicleta.h"
#include "Data.h"

/**
* Entrada que agrupa los datos de cada pedido. Contiene el tipo, la cantidad y el modelo.
**/
struct lineaComanda{
	TipusBicicleta tipus;
	int m_quantitat;
	string m_model;
};

/**
* Clase que almacena el pedido y los datos relacionados con �l.
* Una comanda debe de ser capaz de saber el totl de bicicletas pedidas, la fecha de entrega y el coste asociado a la misma.
**/
class Comanda
{
public:

	Comanda(const Data& entregaPrevista, vector<lineaComanda>& comanda) {
		m_dataEntregaPrevista = entregaPrevista;
		m_llistaComanda = comanda;
		int num = 0;
		float cost = 0;
		float costBici = 0;
		for (int i = 0; i < comanda.size(); i++) {
			num = num + comanda[i].m_quantitat;
		}
		for (int i = 0; i < comanda.size(); i++) {
			costBici = float(comanda[i].tipus);
			cost = cost + (costBici) * comanda[i].m_quantitat;
		}
		m_totalBicicletes = num;
		m_costTotal = cost;
	}

	int getTotalBicicletes() const { return m_totalBicicletes; }
	Data getDataEntregaPrevista() const { return m_dataEntregaPrevista; }
	float getCostTotal() const { return m_costTotal; }
	vector<lineaComanda> getLlistaComanda() const { return m_llistaComanda; }

private:
	int m_totalBicicletes;
	float m_costTotal;
	Data m_dataEntregaPrevista;
	vector<lineaComanda> m_llistaComanda;
};

