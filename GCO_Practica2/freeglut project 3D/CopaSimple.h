#ifndef CopaSimpleH
#define CopaSimpleH

#include "ObjetoCompuesto.h"
#include "ObjetoCuadrico.h"

class CopaSimple : public ObjetoCompuesto {

public:

	CopaSimple(ObjetoCuadrico* cuadrico);
	~CopaSimple();

};

#endif