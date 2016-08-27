#ifndef FarolaH
#define FarolaH

#include "ObjetoCompuesto.h"

class Farola : public ObjetoCompuesto {

private:
	int luz_bombilla;

public:

	Farola();
	~Farola();
	void apagar();
	void encender();

};

#endif