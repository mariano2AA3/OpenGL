 
#ifndef CamaraH
#define CamaraH

#include "PuntoVector3D.h"
 
class Camara {
	private:
		PuntoVector3D *eye, *up, *look, *u, *v, *n;				               
		bool modeOrtho;			// false -> perspectiva, true-> ortogonal

		void setView();	
		void setCameraCoordinateSystem();
        void setModelViewMatrix();

	public:				
		Camara();
		~Camara();
        
		void setEye(GLfloat x, GLfloat y, GLfloat z);
		void setLook(GLfloat x, GLfloat y, GLfloat z);
        void giraX();
        void giraY();
        void giraZ();
        void lateral();
        void frontal();
        void cenital();
        void rincon();
		void switchMode();
		void setProjection(GLdouble xLeft, GLdouble xRight, GLdouble yBot, GLdouble yTop, GLdouble N, GLdouble F);
		void roll(float ang);
        void pitch(float ang);
        void yaw(float ang);
		void zoom(float f);
};
#endif
