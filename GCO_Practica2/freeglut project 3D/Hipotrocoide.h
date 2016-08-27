#ifndef Hipotrocoide_H_
#define Hipotrocoide_H_

#include "Malla.h"
#include "Camara.h"

class Hipotrocoide : public Malla {

public:

	Hipotrocoide(int nP,  int nQ, Camara* camara);
	void dibuja();
	void setMode(int m);
	void avanza();

private:

	Camara* camara;
	PuntoVector3D** perfil;
	GLfloat* mt;
	GLfloat a, b, c;
	int nP, nQ;
	int mode;
	int distancia;
	
	void construirPerfil();
	PuntoVector3D* calcularCt(GLfloat t);
	PuntoVector3D* calcularDerivadaCt(GLfloat t);
	PuntoVector3D* calcularDerivadaSegundaCt(GLfloat t);
	PuntoVector3D* calcularTt(GLfloat t);
	PuntoVector3D* calcularBt(GLfloat t);
	PuntoVector3D* calcularNt(GLfloat t);
	void darValoraMt(GLfloat t);
	PuntoVector3D* calcularPerfilPorMt(int puntoPerfil);
	PuntoVector3D* calcularPosCamara();
	void construirVerticesMalla();
	void construirCarasMalla();
	PuntoVector3D* calcularVectorNormalPorProductoVectorial(Cara* cara);
	void dibujaAux();
};


#endif