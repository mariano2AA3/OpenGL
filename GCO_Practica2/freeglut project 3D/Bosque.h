#ifndef Bosque_H_
#define Bosque_H_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>


class Bosque {

public:

	// Dibuja un tronco en vertical situado en el origen
	void dibujaTronco(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas);
	void dibujaAbeto(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioBaseCopa, GLfloat alturaCopa, int numLados, int numRodajas);	// Un cono
	void dibujaPino(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioBaseCopa, GLfloat alturaCopa, int numLados, int numRodajas);	// Dos conos
	void dibujaRoble(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioCopa, int numLados, int numRodajas);	// Una esfera de copa
	void dibujaAlamo(GLfloat radioBaseTronco, GLfloat radioCimaTronco, GLfloat alturaTronco, GLfloat radioCopaIzq, GLfloat radioCopaDr, int numLados, int numRodajas);	// Dos esferas de copa
	void dibuja();

};


#endif