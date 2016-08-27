#include "Abeto.h"
#include "CopaSimple.h"
#include "Cilindro.h"

Abeto::Abeto() {
	
	this->introduceObjeto(new CopaSimple(new Cilindro(1.0f, 0.0f, 2.5f, 10, 20)));
	this->introduceObjeto(new Cilindro(0.5f, 0.25f, 3, 10, 20));

	this->traslada(7.0f, 0.0f, 7.0f);

	// Rotamos la copa
	this->hijos[0]->setColor(0.09f, 0.482f, 0.207f);
	this->hijos[0]->traslada(0.0f, 2.0f, 0.0f);
	this->hijos[0]->rota(-90, 1.0f,0.0f,0.0f);

	// Rotamos el tronco
	this->hijos[1]->setColor(0.549f, 0.29f, 0.03f);
	this->hijos[1]->rota(-90, 1.0f, 0.0f, 0.0f);
	
}

Abeto::~Abeto() {}