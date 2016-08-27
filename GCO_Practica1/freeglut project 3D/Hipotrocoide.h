#ifndef Hipotrocoide_H_
#define Hipotrocoide_H_

#include "Malla.h"

class Hipotrocoide : public Malla {

public:

	Hipotrocoide(int nP,  int nQ);
	void dibuja();
	void setMode(int m);

private:

	PuntoVector3D** perfil;
	GLfloat* mt;		// Matriz de transformacion
	GLfloat a, b, c;
	int mode;

	void construirPerfil( int nP);
	PuntoVector3D* calcularCt(GLfloat t);
	PuntoVector3D* calcularDerivadaCt(GLfloat t);
	PuntoVector3D* calcularDerivadaSegundaCt(GLfloat t);
	PuntoVector3D* calcularTt(GLfloat t);
	PuntoVector3D* calcularBt(GLfloat t);
	PuntoVector3D* calcularNt(GLfloat t);
	void darValoraMt(GLfloat t);
	PuntoVector3D* calcularPerfilPorMt(int puntoPerfil);
	void construirVerticesMalla( int nP,  int nQ);
	void construirCarasMalla( int nP,  int nQ);
	PuntoVector3D* calcularVectorNormalPorProductoVectorial(Cara* cara);
};


#endif