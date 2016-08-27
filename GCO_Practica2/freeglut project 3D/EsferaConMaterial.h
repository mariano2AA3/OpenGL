
#ifndef EsferaConMaterialH
#define EsferaConMaterialH

#include "Esfera.h"

class EsferaConMaterial : public Esfera {

private:
	GLfloat material_especular[4];

protected:

	GLfloat radio;

public:

	EsferaConMaterial(GLfloat radio, int numLados, int numRodajas);
	virtual void dibuja();
	void setMaterialEspecular(GLfloat inc);

};
#endif