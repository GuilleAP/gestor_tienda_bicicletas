#include "BicicletaCarretera.h"

BicicletaCarretera::BicicletaCarretera(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, ModalitatC modalitat, bool electrica) {
	m_model = model;
	m_descripcio = descripcio;
	m_temporada = temporada;
	m_talla = talla;
	m_quadre = quadre;
	m_roda = Roda::RODA_700;
	m_fre = fre;
	m_tipus = TipusBicicleta::CARRETERA;
	m_modalitatC = modalitat;
	m_electrica = electrica;
}
