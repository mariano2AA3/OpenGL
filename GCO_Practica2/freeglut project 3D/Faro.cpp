#include "Faro.h"


Faro::Faro(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas, int luz) : Cilindro(radioBase, radioCima, altura, numLados, numRodajas) {
	this->luz = luz;
}

void Faro::dibuja() {

	GLfloat p1[] = { 0.0f, 0.0f, 0.0f, 1.0f };		// Posicion

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		colorea();
		glMultMatrixf(this->dameMatrizAfin());
		gluCylinder(this->q, this->radioBase, this->radioCima, this->altura, this->numLados, this->numRodajas);


		glLightf(this->luz, GL_SPOT_CUTOFF, 10.0f);
		glLightf(this->luz, GL_SPOT_EXPONENT, 4.0f);
		GLfloat dir[] = { 0.0f, 0.0f, 1.0f }; // Dirección del foco
		glLightfv(this->luz, GL_SPOT_DIRECTION, dir);

		glLightfv(this->luz, GL_POSITION, p1);
	glPopMatrix();
}