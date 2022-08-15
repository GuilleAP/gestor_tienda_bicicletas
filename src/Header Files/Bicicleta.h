#pragma once

#include <string>

#include "Data.h"


/**
* Enumeraciones necesarias para la creacion de bicicletas.
* Los valores son necesarios para poder realizar un control de errores eficiente.
* Si algun constructor recibe un parametro "ileagal" debeis establecer como valor por defecto
* el valor permitido mas peque�o del enum.
* 
**/

enum class TipusBicicleta
{
	INFANTIL = 100,
	MTB = 200,
	CARRETERA = 250
};

enum class Fre
{
	DISC = 0,
	RIM = 1,
};

enum class Quadre
{
	ALUMINI = 0,
	CARBONO = 1,
};

enum class Roda
{
	RODA_26 = 0,
	RODA_27 = 1,
	RODA_29 = 2,
	RODA_14 = 3,
	RODA_20 = 4,
	RODA_700 = 5,
};

enum class Talla
{
	XS = 0,
	S = 1,
	M = 2,
	L = 3,
	XL = 4,
};


/**
* Bicicleta es una clase que contiene toda la informacion relevante para definir una bicicleta generica.
**/
class Bicicleta {
public:
	Bicicleta();
	Bicicleta(const Bicicleta& b);
	virtual ~Bicicleta() {}
	
	string getModel() const { return m_model; }
	string getDescripcio() const { return m_descripcio; }
	string getCodiRus() const { return m_codiRus; }
	int getTemporada() const { return m_temporada; }
	Talla getTalla() const { return m_talla; }
	Quadre getQuadre() const { return m_quadre; }
	Roda getRoda() const { return m_roda; }
	Fre getFre() const { return m_fre; }
	TipusBicicleta getTipus() const { return m_tipus; }
	Data getDataEntrada() const { return m_dataEntrada; }
	virtual void setModel(const string& model) final { m_model = model; }
	virtual void setDescripcio(const string& descripcio) final { m_descripcio = descripcio; }
	virtual void setCodiRus(const string& codirus) final { m_codiRus = codirus; }
	virtual void setTemporada(const int& temporada) final { m_temporada = temporada; }
	virtual void setTalla(const Talla& talla) final { m_talla = talla; }
	virtual void setRoda(const Roda& roda) { m_roda = roda; }
	virtual void setQuadre(const Quadre& quadre) { m_quadre = quadre; }
	virtual void setFre(const Fre& fre) { m_fre = fre; }
	virtual void setTipus(TipusBicicleta tipus) { m_tipus = tipus; }
	virtual void setPreu(TipusBicicleta cost) { m_cost = cost; }
	//Para diferenciar el precio de cada uno de los tipos de bicicleta, utilizamos el getter de esta forma.
	virtual float getPreu() const { 
	    float cost = 0.0;
		switch (this->m_tipus)
		{
		case (TipusBicicleta::INFANTIL):
			return (float)TipusBicicleta::INFANTIL;
			break;
		case (TipusBicicleta::CARRETERA):
			return (float)TipusBicicleta::CARRETERA;
			break;
		case (TipusBicicleta::MTB):
			return (float)TipusBicicleta::MTB;
			break;
		default:
			break;
		}
	}

	void setDataEntrada(Data d) { m_dataEntrada = d; }

	bool operator<(const Bicicleta &b1) const;

	//virtual ostream& format(ostream& os) const final = 0;		
	
protected:
	string m_model;
	string m_descripcio;
	string m_codiRus;
	int m_temporada;
	Talla m_talla;
	Quadre m_quadre;
	Roda m_roda;
	Fre m_fre;
	TipusBicicleta m_tipus;
	Data m_dataEntrada;
	float m_preu;
	TipusBicicleta m_cost;
};

struct CmpBicicleta {
	bool operator()(Bicicleta* a, Bicicleta* b) const
	{
		return b->getDataEntrada() < a->getDataEntrada();
	}

};
