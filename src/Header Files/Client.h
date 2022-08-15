#pragma once
#include <vector>
#include <algorithm>


#include "Bicicleta.h"
#include "Botiga.h"
#include "Entitat.h"


class Client : public Entitat
{
public:
	Client() = default;
	Client(string nom, string dni) : Entitat(nom, dni) {}
	bool comprarBicicleta(string model, Botiga &b);
	vector<Bicicleta*>& getBicicletes();
	void setBicicletes(vector<Bicicleta*> bicis);
	/*string getNom() { return m_nom; }
	string getDNI() { return m_dni; }
	void setNom(string nom) { m_nom = nom; }
	void setDNI(string dni) { m_dni = dni; }*/

private:
	/*string m_nom;
	string m_dni;*/
	vector<Bicicleta*> m_bicicletes;
};

