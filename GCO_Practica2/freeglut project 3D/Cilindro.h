
#ifndef CilindroH
#define CilindroH

#include "ObjetoCuadrico.h"

class Cilindro : public ObjetoCuadrico {

protected:

	GLfloat radioBase;
	GLfloat radioCima;
	GLfloat altura;

public:
	
	Cilindro(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas);
	virtual void dibuja();

};
#endif