#include "Cilindro.h"


Cilindro::Cilindro(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas) : ObjetoCuadrico(numLados, numRodajas) {
	this->radioBase  = radioBase;
	this->radioCima  = radioCima;
	this->altura	 = altura;
}

void Cilindro::dibuja() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		colorea();
		glMultMatrixf(this->dameMatrizAfin());
		gluCylinder(this->q, this->radioBase, this->radioCima, this->altura, this->numLados, this->numRodajas);
	glPopMatrix();
}