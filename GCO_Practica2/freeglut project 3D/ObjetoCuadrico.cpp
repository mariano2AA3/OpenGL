#include "ObjetoCuadrico.h"

ObjetoCuadrico::ObjetoCuadrico(int numLados, int numRodajas) {
	this->q = gluNewQuadric();
	this->numLados = numLados;
	this->numRodajas = numRodajas;
}

ObjetoCuadrico::~ObjetoCuadrico() {
	gluDeleteQuadric(this->q);
}