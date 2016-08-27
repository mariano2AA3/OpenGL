#include "Cubo.h"

Cubo::Cubo(GLdouble lado) {
	this->lado = lado;
	this->modo = 0;
}

Cubo::Cubo(GLdouble lado, int modo) {
	this->lado = lado;
	this->modo = modo;
}

void Cubo::dibuja() {
	this->colorea();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glMultMatrixf(this->dameMatrizAfin());
		if (this->modo == 0)
			glutSolidCube(this->lado);
		else
			glutWireCube(this->lado);
	glPopMatrix();
}