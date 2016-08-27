#include "EsferaConMaterial.h"


EsferaConMaterial::EsferaConMaterial(GLfloat radio, int numLados, int numRodajas) : Esfera(radio, numLados, numRodajas) {
	
	this->material_especular[0] = 0.0f;
	this->material_especular[1] = 0.0f;
	this->material_especular[2] = 0.0f;
	this->material_especular[3] = 1.0f;
}

void EsferaConMaterial::dibuja() {

	GLfloat material_original[4];
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, material_original);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->material_especular);

	//this->setColor(this->material_especular[0], this->material_especular[1], this->material_especular[2]);
	Esfera::dibuja();

	glMaterialfv(GL_FRONT, GL_SPECULAR, material_original);
}

void EsferaConMaterial::setMaterialEspecular(GLfloat inc) {
	
	for (int i = 0; i < 4; ++i) {
		this->material_especular[i] += inc;
		if (this->material_especular[i] < 0.0f)
			this->material_especular[i] = 0.0f;
		else if (this->material_especular[i] > 1.0f)
			this->material_especular[i] = 1.0f;
	}
}