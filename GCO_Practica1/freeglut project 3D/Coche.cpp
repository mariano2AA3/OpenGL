#include "Coche.h"
 
Coche::Coche(GLfloat radioRuedas, GLfloat grosorRuedas, GLfloat radioFaros) {
	this->pos				= 0;
	this->radioRuedas		= radioRuedas;
	this->grosorRuedas		= grosorRuedas;
	this->radioFaros		= radioFaros;
	this->ladosRueda		= 10;
	this->rodajasRueda		= 15;
	this->chasis			= new Cubo();
	this->cilindroRueda		= gluNewQuadric();
	this->tapaRueda			= gluNewQuadric();
	this->cilindroFaro		= gluNewQuadric();
	this->tapaFaro			= gluNewQuadric();
}

Coche::~Coche() {
	this->chasis->~Cubo();
	gluDeleteQuadric(this->cilindroRueda);
	gluDeleteQuadric(this->tapaRueda);
	gluDeleteQuadric(this->cilindroFaro);
	gluDeleteQuadric(this->tapaFaro);
}

void Coche::dibuja() {
	glMatrixMode(GL_MODELVIEW);
	
	glScalef(0.4f, 0.4f, 0.4f);

	// Dibujamos el coche en la posición que corresponda del eje X (inicialmente 0)
	glTranslated(pos, 0, 0);

	//Dibuja chasis
	glColor3f(0.9f, 0, 0.7f);	// Color magenta
	this->chasis->dibuja();

	glColor3f(0, 0, 0);			// Color negro (para las ruedas)

	//Dibuja rueda inferior derecha (rueda 0)
	glPushMatrix();
		glTranslated(-5.0f, -5.0f, 4.0f);
		glRotated(pos * -5.0f, 0, 0, 1.0f); // Rotamos la rueda en función de la posición actual del coche
		gluCylinder(this->cilindroRueda, this->radioRuedas, this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda);
		glTranslated(0, 0, grosorRuedas);
		gluDisk(this->tapaRueda, 0, this->radioRuedas, this->ladosRueda, this->rodajasRueda);
	glPopMatrix();

	//Dibuja rueda superior derecha (rueda 1)
	glPushMatrix();
		glTranslated(5.0f, -5.0f, 4.0f);
		glRotated(pos * -5.0f, 0, 0, 1.0f); // Rotamos la rueda en función de la posición actual del coche
		gluCylinder(this->cilindroRueda, this->radioRuedas, this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda);
		glTranslated(0, 0, grosorRuedas);
		gluDisk(this->tapaRueda, 0, this->radioRuedas, this->ladosRueda, this->rodajasRueda);
	glPopMatrix();

	//Dibuja rueda superior izquierda (rueda 2)
	glPushMatrix();
		glTranslated(5.0f, -5.0f, -4.0f - this->grosorRuedas);
		glRotated(pos * -5.0f, 0, 0, 1.0f); // Rotamos la rueda en función de la posición actual del coche
		gluCylinder(this->cilindroRueda, this->radioRuedas, this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda);
		gluDisk(this->tapaRueda, 0, this->radioRuedas, this->ladosRueda, this->rodajasRueda);
	glPopMatrix();

	//Dibuja rueda inferior izquierda (rueda 3)
	glPushMatrix();
		glTranslated(-5.0f, -5.0f, -4.0f - this->grosorRuedas);
		glRotated(pos * -5.0f, 0, 0, 1.0f); // Rotamos la rueda en función de la posición actual del coche
		gluCylinder(this->cilindroRueda, this->radioRuedas, this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda);
		gluDisk(this->tapaRueda, 0, this->radioRuedas, this->ladosRueda, this->rodajasRueda);
	glPopMatrix();

	glColor3f(0.1f, 0.9f, 0.2f);	// Color verde (para los faros)

	//Dibuja faro izquierdo
	glPushMatrix();
		glTranslated(5.5f, -1.0f, -2.2f);
		glRotated(90.0f, 0, 1.0f, 0);
		gluCylinder(this->cilindroFaro, this->radioFaros, this->radioFaros, 0.8f, 20, 30);
		glTranslated(0, 0, 0.8f);
		gluDisk(this->tapaFaro, 0, this->radioFaros, 20, 30);
	glPopMatrix();

	//Dibuja faro derecho
	glPushMatrix();
		glTranslated(5.5f, -1.0f, 2.2f);
		glRotated(90.0f, 0, 1.0f, 0);
		gluCylinder(this->cilindroFaro, this->radioFaros, this->radioFaros, 0.8f, 20, 30);
		glTranslated(0, 0, 0.8f);
		gluDisk(this->tapaFaro, 0, this->radioFaros, 20, 30);
	glPopMatrix();
}

void Coche::avanza(GLfloat distancia) {
	this->pos += distancia;
}