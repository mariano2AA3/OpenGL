#ifndef Rueda_H
#define Rueda_H

#include "ObjetoCompuesto.h"

class Rueda : public ObjetoCompuesto {

public:

	Rueda(GLfloat radioRuedas, GLfloat grosorRuedas, int ladosRueda, int rodajasRueda);
	~Rueda();
	
};

#endif