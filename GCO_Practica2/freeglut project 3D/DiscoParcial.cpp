#include "DiscoParcial.h"


DiscoParcial::DiscoParcial(GLfloat radioInterior, GLfloat radioExterior, GLfloat anguloinicial, GLfloat anguloBarrido, int numLados, int numRodajas) : ObjetoCuadrico(numLados, numRodajas) {
	this->radioInterior  = radioInterior;
	this->radioExterior  = radioExterior;
	this->anguloInicial  = anguloInicial;
	this->anguloBarrido  = anguloBarrido;
}

void DiscoParcial::dibuja() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		//glColor3f(0.09f, 0.482f, 0.207f);		// Color verde
		glMultMatrixf(this->dameMatrizAfin());
		gluPartialDisk(this->q, this->radioInterior, this->radioExterior, this->numLados, this->numRodajas, this->anguloInicial, this->anguloBarrido);
	glPopMatrix();

}