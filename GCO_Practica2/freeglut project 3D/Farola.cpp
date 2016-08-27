#include "Farola.h"
#include "Cilindro.h"
#include "Bombilla.h"

Farola::Farola() {

	luz_bombilla = GL_LIGHT3;

	this->introduceObjeto(new Bombilla(1.0f, 30, 30, this->luz_bombilla));
	this->introduceObjeto(new Cilindro(0.25f, 0.25f, 10, 10, 20));

	this->traslada(-6.0f, 0.0f, -6.0f);

	// Rotamos la bombilla
	this->hijos[0]->setColor(1.0f, 1.0f, 1.0f);
	this->hijos[0]->traslada(0.0f, 10.0f, 0.0f);

	// Rotamos el poste
	this->hijos[1]->setColor(0.0f, 0.0f, 0.0f);
	this->hijos[1]->rota(-90, 1.0f, 0.0f, 0.0f);
	
	this->apagar();
}

Farola::~Farola() {}

void Farola::apagar() {
	glDisable(this->luz_bombilla);
}

void Farola::encender() {
	glEnable(this->luz_bombilla);
}
