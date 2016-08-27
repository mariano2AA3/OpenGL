
#ifndef ObjetoCuadricoH
#define ObjetoCuadricoH

#include "Objeto3D.h"

class ObjetoCuadrico : public Objeto3D {
	
public:

	ObjetoCuadrico(int numLados, int numRodajas);
	~ObjetoCuadrico();

protected:
	
	GLUquadric* q;
	int numLados;
	int numRodajas;

};
#endif