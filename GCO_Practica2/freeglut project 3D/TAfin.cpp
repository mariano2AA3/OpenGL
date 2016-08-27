#include "TAfin.h"


TAfin::TAfin() {
	m = new GLfloat[16];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();

}

TAfin::~TAfin() {
	delete[] m;
}

void TAfin::traslada(GLfloat x, GLfloat y, GLfloat z) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glTranslated(x, y, z);
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	 
	TAfin::postMultiplica(m1);
}

void TAfin::rota(GLfloat ang, GLfloat fx, GLfloat fy, GLfloat fz) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glRotated(ang, fx, fy, fz);
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();

	TAfin::postMultiplica(m1);
}

void TAfin::escala(GLfloat fx, GLfloat fy, GLfloat fz) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glScaled(fx, fy, fz);
		GLfloat m1[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();

	TAfin::postMultiplica(m1);
}

void TAfin::postMultiplica(GLfloat* m1) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		// Cargamos m como matriz actual de modelado-vista
		glLoadMatrixf(m);
		// Post-multiplicamos por m1: m * m1
		glMultMatrixf(m1);
		// Guardamos el resultado en m: m = m * m1
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();
}

GLfloat* TAfin::dameMatrizModelado() {
	return m;
}