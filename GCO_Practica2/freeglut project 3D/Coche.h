#ifndef Coche_H
#define Coche_H

#include "ObjetoCompuesto.h"
#include "Malla.h"

class Coche : public ObjetoCompuesto {

private:

	GLfloat ladoChasis;
	GLfloat radioRuedas;
	GLfloat grosorRuedas;
	GLfloat radioFaros;
	int ladosRueda;
	int rodajasRueda;
	GLfloat pos;
	Malla* chasis;

	// Luces
	// GL_LIGHT0	// Luz escena
	// GL_LIGHT1	// Luz faro izquierdo
	// GL_LIGHT2	// Luz faro derecho

	PuntoVector3D* calcularVectorNormalPorProductoVectorial(PuntoVector3D** vertices, Cara* cara);
	Malla* construirChasis();
	void iniciarLuces();

public:

	Coche();
	~Coche();
	void avanza(GLfloat distancia);
	void gira(GLfloat angulo);
	void encenderFaros();
	void apagarFaros();
};

#endif