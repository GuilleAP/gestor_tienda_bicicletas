#include "BicicletaInfantil.h"

BicicletaInfantil::BicicletaInfantil(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, const bool& plegable) {
	m_model = model;
	m_descripcio = descripcio;
	m_temporada = temporada;
	m_talla = talla;
	m_quadre = Quadre::ALUMINI;
	m_roda = Roda::RODA_14;
	m_fre = Fre::RIM;
	m_tipus = TipusBicicleta::INFANTIL;
	m_plegable = plegable;
}
