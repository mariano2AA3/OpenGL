
#ifndef EsferaH
#define EsferaH

#include "ObjetoCuadrico.h"

class Esfera : public ObjetoCuadrico {

protected:

	GLfloat radio;

public:
	
	Esfera(GLfloat radio, int numLados, int numRodajas);
	virtual void dibuja();

};
#endif