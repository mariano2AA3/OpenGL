
#ifndef DiscoParcialH
#define DiscoParcialH

#include "ObjetoCuadrico.h"

class DiscoParcial : public ObjetoCuadrico {

private:

	GLfloat radioInterior;
	GLfloat radioExterior;
	GLfloat anguloInicial;
	GLfloat anguloBarrido;

public:
	
	DiscoParcial(GLfloat radioInterior, GLfloat radioExterior, GLfloat anguloinicial, GLfloat anguloBarrido, int numLados, int numRodajas);
	virtual void dibuja();

};
#endif