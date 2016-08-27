 
#include "Camara.h"
#include <math.h>


Camara::Camara() {           
	eye  = new PuntoVector3D(20, 20, 20, 1);
    look = new PuntoVector3D(0, 0, 0, 1);
    up   = new PuntoVector3D(0, 1, 0, 0);

	modeOrtho = true;
	
	setView();  
	setCameraCoordinateSystem();
	setModelViewMatrix();
}

Camara::~Camara() {           
	delete eye;
	delete look;
	delete up;
	delete u;
	delete v;
	delete n;
}

void Camara::setEye(GLfloat x, GLfloat y, GLfloat z) {
	delete eye;
	eye = new PuntoVector3D(x, y, z, 1);

	setView();  
	setCameraCoordinateSystem();
}

void Camara::setLook(GLfloat x, GLfloat y, GLfloat z) {
	delete look;
	look = new PuntoVector3D(x, y, z, 1);

	setView();  
	setCameraCoordinateSystem();
}

void Camara::setView() {
/*Define la matriz de vista con el comando gluLookAt() */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());
}

void Camara::setCameraCoordinateSystem() {
/*Obtiene el valor de los vectores u, v, n  */

	// n = (eye - look) normalizado
	n = new PuntoVector3D(eye->getX() - look->getX(), eye->getY() - look->getY(), eye->getZ() - look->getZ(), 0);
	n->normalizar();
	
	// u = (upxn) normalizado
	u = up->productoVectorial(n);
	u->normalizar();

	// v = nxu
	v = n->productoVectorial(u);
}

void Camara::switchMode() {
	this->modeOrtho = !(this->modeOrtho);
}

void Camara::setProjection(GLdouble xLeft, GLdouble xRight, GLdouble yBot, GLdouble yTop, GLdouble N, GLdouble F) {
/*Define la matriz de proyección con el comando */ 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (this->modeOrtho)
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
}

void Camara::setModelViewMatrix() {
    glMatrixMode(GL_MODELVIEW);		 
    GLfloat m[16];  
    m[0]=u->getX(); m[4]=u->getY(); m[8]=u->getZ(); m[12]=-eye->productoEscalar(u);
    m[1]=v->getX(); m[5]=v->getY(); m[9]=v->getZ(); m[13]=-eye->productoEscalar(v);
    m[2]=n->getX(); m[6]=n->getY(); m[10]=n->getZ(); m[14]=-eye->productoEscalar(n);
    m[3]=0; m[7]=0; m[11]=0; m[15]=1;
    glLoadMatrixf(m); 
}

void Camara::giraX() {
/*Gira la cámara alrededor del eje X sobre un plano perpendicular a este eje */

	GLfloat d     = sqrtf(pow(eye->getY() - look->getY(), 2) + pow(eye->getZ() - look->getZ(), 2));
	GLfloat theta = atan2(eye->getZ(), eye->getY()) + 0.1f;

	eye = new PuntoVector3D(eye->getX(), d * cosf(theta), d * sinf(theta), 1);
    
	setView();
    setCameraCoordinateSystem();     
}

void Camara::giraY() {
	//Gira la cámara alrededor del eje Y sobre un plano perpendicular a este eje
	
	GLfloat d	  = sqrtf(pow(eye->getZ() - look->getZ(), 2) + pow(eye->getX() - look->getX(), 2));
	GLfloat theta = atan2(eye->getX(), eye->getZ()) + 0.1f;

	eye = new PuntoVector3D(d * sinf(theta), eye->getY(), d * cosf(theta), 1);

	setView();
	setCameraCoordinateSystem();
}

void Camara::giraZ() {
	//Gira la cámara alrededor del eje Z sobre un plano perpendicular a este eje

	GLfloat d	  = sqrtf(pow(eye->getX() - look->getX(), 2) + pow(eye->getY() - look->getY(), 2));
	GLfloat theta = atan2(eye->getY(), eye->getX()) + 0.1f;

	eye = new PuntoVector3D(d * cosf(theta), d * sinf(theta), eye->getZ(), 1);

	setView();
	setCameraCoordinateSystem();
}

void Camara::lateral() {
	//Coloca la cámara de forma que se muestra una visión lateral 
	//de la escena (desde el eje X)

	eye = new PuntoVector3D(20.0f, 0, 0, 1);
	up  = new PuntoVector3D(0, 1.0f, 0, 0);
	
	setView();
	setCameraCoordinateSystem();
}

void Camara::frontal() {
	//Coloca la cámara de forma que se muestra una visión frontal 
	//de la escena (desde el eje Z) 

	eye = new PuntoVector3D(0, 0, 20.0f, 1);
	up  = new PuntoVector3D(0, 1.0f, 0, 0);

	setView();
	setCameraCoordinateSystem();
}

void Camara::cenital() {
    //Coloca la cámara de forma que se muestra una visión cenital 
	//de la escena (desde el eje Y) 

	eye = new PuntoVector3D(0, 20.0f, 0, 1);
	up  = new PuntoVector3D(1.0f, 0, 0, 0);

	setView();
	setCameraCoordinateSystem();
}

void Camara::rincon() {
    //Coloca la cámara de forma que se muestra
	//la escena en un rincón
	
	eye = new PuntoVector3D(20.0f, 20.0f, 20.0f, 1);
	up  = new PuntoVector3D(0, 1.0f, 0, 0);

	setView();
	setCameraCoordinateSystem();
}
 
void Camara::roll(float ang) {
	//Rota la cámara tal como se explica en las transparencias
	

	PuntoVector3D* u2 = new PuntoVector3D(u->getX()*cosf(ang) + v->getX()*sinf(ang), u->getY()*cosf(ang) + v->getY()*sinf(ang), u->getZ()*cosf(ang) + v->getZ()*sinf(ang), 0);
	PuntoVector3D* v2 = new PuntoVector3D(-u->getX()*sinf(ang) + v->getX()*cosf(ang), -u->getY()*sinf(ang) + v->getY()*cosf(ang), -u->getZ()*sinf(ang) + v->getZ()*cosf(ang), 0);
	
	u->~PuntoVector3D();
	v->~PuntoVector3D();

	u = u2;
	v = v2;

	setModelViewMatrix();
}

void Camara::pitch(float ang) {		
    
	PuntoVector3D* v2 = new PuntoVector3D(v->getX()*cosf(ang) + n->getX()*sinf(ang), v->getY()*cosf(ang) + n->getY()*sinf(ang), v->getZ()*cosf(ang) + n->getZ()*sinf(ang), 0);
	PuntoVector3D* n2 = new PuntoVector3D(-v->getX()*sinf(ang) + n->getX()*cosf(ang), -v->getY()*sinf(ang) + n->getY()*cosf(ang), -v->getZ()*sinf(ang) + n->getZ()*cosf(ang), 0);
	
	v->~PuntoVector3D();
	n->~PuntoVector3D();

	v = v2;
	n = n2;

	setModelViewMatrix();
}

void Camara::yaw(float ang) {		
    
	PuntoVector3D* u2 = new PuntoVector3D(u->getX()*cosf(ang) - n->getX()*sinf(ang), u->getY()*cosf(ang) - n->getY()*sinf(ang), u->getZ()*cosf(ang) - n->getZ()*sinf(ang), 0);
	PuntoVector3D* n2 = new PuntoVector3D(u->getX()*sinf(ang) + n->getX()*cosf(ang), u->getY()*sinf(ang) + n->getY()*cosf(ang), u->getZ()*sinf(ang) + n->getZ()*cosf(ang), 0);
	
	u->~PuntoVector3D();
	n->~PuntoVector3D();

	u = u2;
	n = n2;

	setModelViewMatrix();
}


