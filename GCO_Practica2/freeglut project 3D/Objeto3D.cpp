#include "Objeto3D.h"

Objeto3D::Objeto3D(){
	mt = new TAfin();
	azul = 1;
	verde = 1;
	rojo = 1;
	colorSet = false;
}

Objeto3D::~Objeto3D(){
	delete mt;
}

void Objeto3D::setColor(GLfloat rojo, GLfloat verde, GLfloat azul) {
	this->rojo = rojo;
	this->verde = verde;
	this->azul = azul;
	this->colorSet = true;
}

void Objeto3D::colorea() {
	if (colorSet)
		glColor3f(rojo, verde, azul);
}

void Objeto3D::traslada(GLfloat x, GLfloat y, GLfloat z) {
	mt->traslada(x, y, z);
}

void Objeto3D::rota(GLfloat ang, GLfloat fx, GLfloat fy, GLfloat fz){
	mt->rota(ang, fx, fy, fz);
}

void Objeto3D::escala(GLfloat fx, GLfloat fy, GLfloat fz){
	mt->escala(fx, fy, fz);
}

GLfloat* Objeto3D::dameMatrizAfin(){
	return mt->dameMatrizModelado();
}