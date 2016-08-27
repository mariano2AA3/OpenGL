#ifndef CuboH
#define CuboH

#include "Objeto3D.h"

class Cubo : public Objeto3D {

private:

	GLdouble lado;
	int modo;		// modo == 0 -> filled, modo == 1 -> wired

public:

	Cubo(GLdouble lado);
	Cubo(GLdouble lado, int modo);
	virtual void dibuja();

};

#endif