
#ifndef FaroH
#define FaroH

#include "Cilindro.h"

class Faro : public Cilindro {

private:
	int luz;

public:

	Faro(GLfloat radioBase, GLfloat radioCima, GLfloat altura, int numLados, int numRodajas, int luz);
	virtual void dibuja();

};
#endif