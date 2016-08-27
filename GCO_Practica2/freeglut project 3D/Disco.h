
#ifndef DiscoH
#define DiscoH

#include "ObjetoCuadrico.h"

class Disco : public ObjetoCuadrico {

private:

	GLfloat radioInterior;
	GLfloat radioExterior;

public:
	
	Disco(GLfloat radioInterior, GLfloat radioExterior, int numLados, int numRodajas);
	virtual void dibuja();

};
#endif