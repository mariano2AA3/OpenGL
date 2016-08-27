#include "Rueda.h"
#include "Cilindro.h"
#include "Disco.h"

#include "Esfera.h"

Rueda::Rueda(GLfloat radioRuedas, GLfloat grosorRuedas, int ladosRueda, int rodajasRueda) {
	
	this->introduceObjeto( new Cilindro(radioRuedas, radioRuedas, grosorRuedas, ladosRueda, rodajasRueda) );
	this->hijos[0]->setColor(0.0f, 0.0f, 0.0f);

	this->introduceObjeto( new Disco(0.0f, radioRuedas, ladosRueda, rodajasRueda) );
	this->hijos[1]->setColor(0.2f, 0.2f, 0.2f);
	this->hijos[1]->traslada(0.0f, 0.0f, grosorRuedas);
}

Rueda::~Rueda() {
	for( int i=0; i<this->numHijos; ++i) {
		this->hijos[i]->~Objeto3D();
	}
}