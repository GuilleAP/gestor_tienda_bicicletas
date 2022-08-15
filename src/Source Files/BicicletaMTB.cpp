#include "BicicletaMTB.h"
#include "utils.h"

BicicletaMTB::BicicletaMTB() {

}

BicicletaMTB::BicicletaMTB(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, Categoria categoria, Modalitat modalitat, bool electrica) {
	m_model = model;
	m_descripcio = descripcio;
	m_temporada = temporada;
	m_talla = talla;
	m_quadre = quadre;
	m_roda = Roda::RODA_26;
	m_fre = Fre::DISC;
	m_tipus = TipusBicicleta::MTB;
	m_categoria = categoria;
	m_modalitat = modalitat;
	m_electrica = electrica;
}
