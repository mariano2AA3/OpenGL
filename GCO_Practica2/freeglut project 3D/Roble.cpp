#include "Roble.h"
#include "CopaSimple.h"
#include "Cilindro.h"

Roble::Roble() {

	this->copa = new EsferaConMaterial(1.5f, 10, 20);
	
	this->introduceObjeto(new CopaSimple(copa));
	this->introduceObjeto(new Cilindro(0.5f, 0.25f, 5, 10, 20));

	this->traslada(-4.0f, 0.0f, 6.0f);

	// Rotamos la copa
	this->hijos[0]->setColor(0.09f, 0.482f, 0.207f);
	this->hijos[0]->traslada(0.0f, 5.0f, 0.0f);

	// Rotamos el tronco
	this->hijos[1]->setColor(0.549f, 0.29f, 0.03f);
	this->hijos[1]->rota(-90, 1.0f, 0.0f, 0.0f);
	
}

Roble::~Roble() {}

void Roble::setMaterialEspecular(GLfloat inc) {
	this->copa->setMaterialEspecular(inc);
}