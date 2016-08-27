#include "Bosque.h"

void Bosque::dibujaTronco(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas) {

	GLUquadric* tronco;
	GLUquadric* base;

	tronco	= gluNewQuadric();
	base	= gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);

	// Dibujamos el tronco y su base a la vez
	glPushMatrix();
		// Tronco
		glRotated(-90, 1, 0, 0);				// Rotamos sobre el eje X -90º para "levantar" el tronco e iluminarlo bien
		glColor3f(0.549f, 0.29f, 0.03f);		// Color marron
		gluCylinder(tronco, radioBase, radioCima, altura, numLados, numRodajas);
		
		// Base
		glRotated(180, 1, 0, 0);				// Rotamos sobre el eje X 180º para rotar el disco 90º e iluminarlo bien
		gluDisk(base, 0, radioBase, numLados, numRodajas);
	glPopMatrix();

	gluDeleteQuadric(tronco);
	gluDeleteQuadric(base);
}

void Bosque::dibujaAbeto(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioBaseCopa, GLfloat alturaCopa, int numLados, int numRodajas) {

	GLUquadric* abeto;
	GLUquadric* base;

	abeto	= gluNewQuadric();
	base	= gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		// Tronco
		dibujaTronco(radioBaseTronco, radioCimaTronco, alturaTronco, numLados, numRodajas);

		// Copa
		glColor3f(0.09f, 0.482f, 0.207f);		// Color verde
		glTranslated(0, alturaTronco, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(abeto, radioBaseCopa, 0.0f, alturaCopa, numLados, numRodajas);

		// Base de la copa
		glRotated(180, 1, 0, 0);
		gluDisk(base, 0, radioBaseCopa, numLados, numRodajas);
	glPopMatrix();

	gluDeleteQuadric(abeto);
	gluDeleteQuadric(base);
}

void Bosque::dibujaPino(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioBaseCopa, GLfloat alturaCopa, int numLados, int numRodajas) {

	GLUquadric* pino;
	GLUquadric* base;

	pino = gluNewQuadric();
	base = gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		dibujaTronco(radioBaseTronco, radioCimaTronco, alturaTronco, numLados, numRodajas);

		glColor3f(0.09f, 0.482f, 0.207f);

		// Dibujamos el cono de abajo
		glTranslated(0, alturaTronco, 0);
		glRotated(-90, 1, 0, 0);
		gluCylinder(pino, radioBaseCopa, 0.0f, alturaCopa, numLados, numRodajas);

		// Dibujamos la base del cono de abajo
		glRotated(180, 1, 0, 0);
		gluDisk(base, 0, radioBaseCopa, numLados, numRodajas);

		// Dibujamos el cono de arriba
		glRotated(-180, 1, 0, 0);
		glTranslated(0, 0, alturaCopa/3);
		gluCylinder(pino, radioBaseCopa, 0.0f, alturaCopa, numLados, numRodajas);

		// Dibujamos la base del cono de arriba
		glRotated(180, 1, 0, 0);
		gluDisk(base, 0, radioBaseCopa, numLados, numRodajas);
		
	glPopMatrix();

	gluDeleteQuadric(pino);
	gluDeleteQuadric(base);
}


void Bosque::dibujaRoble(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioCopa, int numLados, int numRodajas) {

	GLUquadric* roble;

	roble = gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		dibujaTronco(radioBaseTronco, radioCimaTronco, alturaTronco, numLados, numRodajas);

		glColor3f(0.09f, 0.482f, 0.207f);
		glTranslated(0, alturaTronco + radioCopa, 0);
		gluSphere(roble, radioCopa, numLados, numRodajas);
		
	glPopMatrix();

	gluDeleteQuadric(roble);
}


void Bosque::dibujaAlamo(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioCopaIzq, GLfloat radioCopaDr, int numLados, int numRodajas) {

	GLUquadric* copaIzq;
	GLUquadric* copaDr;

	copaIzq = gluNewQuadric();
	copaDr	= gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		// Tronco
		dibujaTronco(radioBaseTronco, radioCimaTronco, alturaTronco, numLados, numRodajas);

		// Copa (2 esferas)
		glRotated(-45, 0, 1, 0);
		glColor3f(0.09f, 0.482f, 0.207f);
		glRotated(90, 0, 1, 0);
		glTranslated(radioCopaIzq/2, alturaTronco + (radioCopaIzq/2), 0);
		gluSphere(copaIzq, radioCopaIzq, numLados, numRodajas);

		glTranslated(-(radioCopaDr/2) - (radioCopaIzq / 2) , 0, 0);
		gluSphere(copaDr, radioCopaDr, numLados, numRodajas);
	glPopMatrix();

	gluDeleteQuadric(copaIzq);
	gluDeleteQuadric(copaDr);
}

void Bosque::dibuja() {
	glMatrixMode(GL_MODELVIEW);

	// Dibujamos un bosque
	glPushMatrix();
		glTranslated(9.0f, 0, 8.0f);
		dibujaAbeto(0.3f, 0.2f, 3, 1.0f, 3.0f, 20, 30);
		glTranslated(-3.0f, 0, -9.0f);
		dibujaPino(0.4f, 0.3f, 5, 1.3f, 4, 20, 30);
		glTranslated(-9.0f, 0, -1.0f);
		dibujaAlamo(0.4f, 0.3f, 3, 1.3f, 1.7f, 20, 30);
		glTranslated(0, 0, 8.0f);
		dibujaRoble(0.4f, 0.3f, 5.5f, 1.5f, 20, 30);
	glPopMatrix();
}