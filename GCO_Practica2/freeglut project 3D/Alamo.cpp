#include "Alamo.h"
#include "CopaDoble.h"
#include "Cilindro.h"
#include "Esfera.h"

Alamo::Alamo() {

	// Preparamos la copa doble
	Esfera* c1 = new Esfera(1.5f, 10, 20);
	Esfera* c2 = new Esfera(1.5f, 10, 20);
	c1->traslada(-0.7f, 0.0f, 0.7f);
	c2->traslada(0.7f, 0.0f, -0.7f);
	CopaDoble* copa = new CopaDoble(c1, c2);
	
	// Guardamos los objetos que forman parte del álamo (copa y tronco)
	this->introduceObjeto(copa);
	this->introduceObjeto(new Cilindro(0.5f, 0.25f, 4, 10, 20));

	// Colocamos el álamo en su posición
	this->traslada(-4.0f, 0.0f, -4.0f);

	// Rotamos la copa
	this->hijos[0]->setColor(0.09f, 0.482f, 0.207f);
	this->hijos[0]->traslada(0.0f, 4.0f, 0.0f);

	// Rotamos el tronco
	this->hijos[1]->setColor(0.549f, 0.29f, 0.03f);
	this->hijos[1]->rota(-90, 1.0f, 0.0f, 0.0f);
	
}

Alamo::~Alamo() {}