#ifndef RobleH
#define RobleH

#include "ObjetoCompuesto.h"
#include "EsferaConMaterial.h"

class Roble : public ObjetoCompuesto {

private:

	EsferaConMaterial* copa;


public:

	Roble();
	~Roble();
	void setMaterialEspecular(GLfloat inc);

};

#endif