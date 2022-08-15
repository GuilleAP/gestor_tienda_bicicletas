#pragma once

#include "Bicicleta.h"

enum class ModalitatC {
	AERO,
	GRANFONDO,
	GRAVEL,
	RENDIMIENTO,
};

/**
* BicicletaCarretera contine la inforacion relenavte para definir una bicicleta de carretera.
* 
**/
class BicicletaCarretera : public Bicicleta {
public:
	BicicletaCarretera(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, ModalitatC modalitat, bool electrica);
	~BicicletaCarretera() {}
	void setModalitat(const ModalitatC& modalitat) { m_modalitatC = modalitat; }
	ModalitatC getModalitat() const { return m_modalitatC; }

	void setElectrica(const bool& electrica) { m_electrica = electrica; }
	bool getElectrica() const { return m_electrica; }
	//Comprobamos que este tipo de bicicleta tiene sus componentes específicos.
	void setQuadre(const Quadre& quadre) override { if (quadre == Quadre::ALUMINI || quadre == Quadre::CARBONO) { this->m_quadre = quadre; } }
	void setRoda(const Roda& roda) override { if (roda == Roda::RODA_700) { this->m_roda = roda; } }
	void setFre(const Fre& fre) override { if (fre == Fre::RIM || fre == Fre::DISC) { this->m_fre = fre; } }
	void setTipus(TipusBicicleta tipus) override { if (tipus == TipusBicicleta::CARRETERA) { this->m_tipus = tipus; } }

protected:
	//ostream& format(ostream& os) const override;
private:
	bool m_electrica;
	ModalitatC m_modalitatC;

};

