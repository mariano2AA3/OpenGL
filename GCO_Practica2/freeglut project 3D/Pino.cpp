#include "Pino.h"
#include "CopaDoble.h"
#include "Cilindro.h"

Pino::Pino() {

	// Preparamos la copa doble
	Cilindro* c1 = new Cilindro(1.0f, 0.0f, 2.5f, 10, 20);
	Cilindro* c2 = new Cilindro(1.0f, 0.0f, 2.5f, 10, 20);
	c2->traslada(0.0f, 0.0f, 1.0f);
	CopaDoble* copa = new CopaDoble(c1, c2);
	
	// Guardamos los objetos que forman parte del pino (copa y tronco)
	this->introduceObjeto(copa);
	this->introduceObjeto(new Cilindro(0.5f, 0.25f, 4, 10, 20));

	// Colocamos el pino en su posición
	this->traslada(4.0f, 0.0f, -4.0f);

	// Rotamos la copa
	this->hijos[0]->setColor(0.09f, 0.482f, 0.207f);
	this->hijos[0]->traslada(0.0f, 4.0f, 0.0f);
	this->hijos[0]->rota(-90, 1.0f,0.0f,0.0f);

	// Rotamos el tronco
	this->hijos[1]->setColor(0.549f, 0.29f, 0.03f);
	this->hijos[1]->rota(-90, 1.0f, 0.0f, 0.0f);
	
}

Pino::~Pino() {}