#include "Disco.h"


Disco::Disco(GLfloat radioInterior, GLfloat radioExterior, int numLados, int numRodajas) : ObjetoCuadrico(numLados, numRodajas) {
	this->radioInterior  = radioInterior;
	this->radioExterior  = radioExterior;
}

void Disco::dibuja() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		this->colorea();
		glMultMatrixf(this->dameMatrizAfin());
		gluDisk(this->q, this->radioInterior, this->radioExterior, this->numLados, this->numRodajas);
	glPopMatrix();
}