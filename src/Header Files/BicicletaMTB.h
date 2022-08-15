#pragma once

#include "Bicicleta.h"
#include <string>


enum class Categoria {
	RIGIDA = 0,
	DOBLE = 1,
};

enum class Modalitat {
	DESCENS = 0,
	ENDURO = 1,
	RALLY = 2,
	TRAIL = 3,
};

/**
* BicicletaMTB contine la inforacion relenavte para definir una bicicleta MTB.
*
**/

class BicicletaMTB : public Bicicleta {
public:
	BicicletaMTB();
	BicicletaMTB(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, Categoria categoria, Modalitat modalitat, bool electrica);
	~BicicletaMTB() override {}
	void setCategoria(const Categoria& categoria) { m_categoria = categoria; }
	Categoria getCategoria() const { return m_categoria; }
	void setModalitat(const Modalitat& modalitat) { m_modalitat = modalitat; }
	Modalitat getModalitat() const { return m_modalitat; }
	void setElectrica(const bool& electrica) { m_electrica = electrica; }
	bool getElectrica() const { return m_electrica; }
	//Comprobamos que este tipo de bicicleta tiene sus componentes específicos.
	void setQuadre(const Quadre& quadre) override { if (quadre == Quadre::ALUMINI || quadre == Quadre::CARBONO) { this->m_quadre = quadre; } }
	void setRoda(const Roda& roda) override { if (roda == Roda::RODA_26 || roda == Roda::RODA_27 || roda == Roda::RODA_29) { this->m_roda = roda; } }
	void setFre(const Fre& fre) override { if (fre == Fre::DISC) { this->m_fre = fre; } }
	void setTipus(TipusBicicleta tipus) override { if (tipus == TipusBicicleta::MTB) { this->m_tipus = tipus; } }

protected:
	//ostream& format(ostream& os) const override;
private:
	Categoria m_categoria;
	Modalitat m_modalitat;
	bool m_electrica;

};
