#include "Bombilla.h"


Bombilla::Bombilla(GLfloat radio, int numLados, int numRodajas, int luz) : Esfera(radio, numLados, numRodajas) {
	this->luz = luz;

	glEnable(this->luz);
	GLfloat af[] = { 0.9f, 0.0f, 0.7f, 1.0f };
	glLightfv(this->luz, GL_DIFFUSE, af);
	glLightfv(this->luz, GL_SPECULAR, af);
	glLightfv(this->luz, GL_AMBIENT, af);
}

void Bombilla::dibuja() {

	GLfloat p1[] = { 0.0f, 0.0f, 0.0f, 1.0f };		// Posicion

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		colorea();
		glMultMatrixf(this->dameMatrizAfin());
		gluSphere(this->q, this->radio, this->numLados, this->numRodajas);
		glLightfv(this->luz, GL_POSITION, p1);
	glPopMatrix();
}