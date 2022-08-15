#include "Client.h"

bool Client::comprarBicicleta(string model, Botiga& b)
{
    
	Bicicleta* bici = nullptr;
    if (b.procesa_venda(model, bici)) {
        m_bicicletes.push_back(bici);
        return true;
    }
    return false;
}

vector<Bicicleta*>& Client::getBicicletes()
{
	// TODO: Insertar una instrucción "return" aquí
	return this->m_bicicletes;
}

void Client::setBicicletes(vector<Bicicleta*> bicis)
{
    m_bicicletes = bicis;
}
 