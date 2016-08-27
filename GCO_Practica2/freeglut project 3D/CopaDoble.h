#ifndef CopaDobleH
#define CopaDobleH

#include "ObjetoCompuesto.h"
#include "ObjetoCuadrico.h"

class CopaDoble : public ObjetoCompuesto {

public:

	CopaDoble(ObjetoCuadrico* c1, ObjetoCuadrico* c2);
	~CopaDoble();

};

#endif