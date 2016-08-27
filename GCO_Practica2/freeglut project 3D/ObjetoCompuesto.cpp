#include "ObjetoCompuesto.h"

ObjetoCompuesto::ObjetoCompuesto(){
	this->hijos = new Objeto3D*[1000000];
	this->numHijos = 0;
}

ObjetoCompuesto::~ObjetoCompuesto(){
	for (int i = 0; i < numHijos; i++)
		delete hijos[i];
}

void ObjetoCompuesto::introduceObjeto(Objeto3D* objeto) {
	this->hijos[this->numHijos] = objeto;
	this->numHijos++;
}

void ObjetoCompuesto::dibuja() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glMultMatrixf(this->dameMatrizAfin());
		this->colorea();
		for (int i = 0; i < this->numHijos; ++i) {
			this->hijos[i]->dibuja();
		}
	glPopMatrix();
}
