#ifndef Coche_H_
#define Coche_H_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include "Cubo.h"


class Coche {

public:

	Coche(GLfloat radioRuedas, GLfloat grosorRuedas, GLfloat radioFaros);
	~Coche();
	void dibuja();
	void avanza(GLfloat distancia);

private:
	
	GLfloat pos;
	GLfloat radioRuedas;
	GLfloat grosorRuedas;
	GLfloat radioFaros;
	GLint ladosRueda;
	GLint rodajasRueda;
	Cubo* chasis;
	GLUquadric* cilindroRueda;
	GLUquadric* tapaRueda;
	GLUquadric* cilindroFaro;
	GLUquadric* tapaFaro;

};


#endif