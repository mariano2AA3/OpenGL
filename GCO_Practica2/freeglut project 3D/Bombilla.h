
#ifndef BombillaH
#define BombillaH

#include "Esfera.h"

class Bombilla : public Esfera {

private:
	int luz;

public:

	Bombilla(GLfloat radio, int numLados, int numRodajas, int luz);
	virtual void dibuja();

};
#endif