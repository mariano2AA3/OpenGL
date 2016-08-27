
#ifndef Objeto3DH
#define Objeto3DH

#include "PuntoVector3D.h"
#include "TAfin.h"

class Objeto3D {

private:
	GLfloat rojo;
	GLfloat verde;
	GLfloat azul;
	bool colorSet;

protected:
	TAfin* mt;

public:

	Objeto3D();
	~Objeto3D();
	void colorea();
	virtual void dibuja()=0; // Método virtual puro.
	void setColor(GLfloat rojo, GLfloat verde, GLfloat azul);
	void traslada(GLfloat x, GLfloat y, GLfloat z);
	void rota(GLfloat ang, GLfloat fx, GLfloat fy, GLfloat fz);
	void escala(GLfloat fx, GLfloat fy, GLfloat fz);
	GLfloat* dameMatrizAfin();
	
};
#endif