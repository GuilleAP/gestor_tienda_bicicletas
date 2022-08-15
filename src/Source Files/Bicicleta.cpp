#include "Bicicleta.h"
#include "utils.h"

Bicicleta::Bicicleta() {
	m_quadre = randomQuadre();
	m_fre = randomFre();
	m_roda = randomRoda();
	m_talla = randomTalla();
	m_temporada = 2020;
	m_preu = 200;
	m_cost = TipusBicicleta::CARRETERA;
	m_tipus = TipusBicicleta::CARRETERA;
}

Bicicleta::Bicicleta(const Bicicleta& b){
	m_quadre = b.m_quadre;
	m_fre = b.m_fre;
	m_roda = b.m_roda;
	m_talla = b.m_talla;
	m_temporada = b.m_temporada;
	m_preu = b.m_preu;
	m_cost = b.m_cost;
	m_tipus = b.m_tipus;
}

bool Bicicleta::operator<(const Bicicleta& b1) const {
	return false;

}

