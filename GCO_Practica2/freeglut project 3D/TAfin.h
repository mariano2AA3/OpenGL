
#ifndef TAfinH
#define TAfinH

#include "PuntoVector3D.h"

class TAfin {
	private:
		GLfloat* m;

	public:
		TAfin();
		~TAfin();
		void traslada(GLfloat x, GLfloat y, GLfloat z);
		void rota(GLfloat ang, GLfloat fx, GLfloat fy, GLfloat fz);
		void escala(GLfloat fx, GLfloat fy, GLfloat fz);
		void postMultiplica(GLfloat* m1);
		GLfloat* dameMatrizModelado();
};
#endif