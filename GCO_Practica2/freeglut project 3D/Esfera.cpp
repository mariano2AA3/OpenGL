#include "Esfera.h"


Esfera::Esfera(GLfloat radio, int numLados, int numRodajas) : ObjetoCuadrico(numLados, numRodajas) {
	this->radio  = radio;
}

void Esfera::dibuja() {
	this->colorea();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glMultMatrixf(this->dameMatrizAfin());
		gluSphere(this->q, this->radio, this->numLados, this->numRodajas);
	glPopMatrix();

}