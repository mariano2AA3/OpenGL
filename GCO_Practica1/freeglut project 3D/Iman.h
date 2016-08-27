#ifndef Iman_H_
#define Iman_H_

#include "Malla.h"

class Iman : public Malla {

public:

	Iman(unsigned int nQ, GLfloat rInt, GLfloat rExt, GLfloat h);
	PuntoVector3D* Iman::calcularVectorNormalPorProductoVectorial(Cara* cara);
	void dibuja();

private:

	int m, n, indice, indiceCara, carasRevolucion;
	PuntoVector3D** perfil;

	void construirPerfil(GLfloat rInt, GLfloat rExt, GLfloat lado);
	void construirVerticesMalla();
	void construirCarasIman();
	void construirPoloDerecho();
	void construirPoloIzquierdo();
};


#endif