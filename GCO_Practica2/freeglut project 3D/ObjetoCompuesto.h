
#ifndef ObjetoCompuestoH
#define ObjetoCompuestoH

#include "Objeto3D.h"

class ObjetoCompuesto : public Objeto3D {
	protected:
		int numHijos;
		Objeto3D** hijos;

	public:
		ObjetoCompuesto();
		~ObjetoCompuesto();
		void introduceObjeto(Objeto3D* objeto);
		virtual void dibuja();
};

#endif