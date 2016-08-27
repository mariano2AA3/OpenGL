#include "Iman.h"
#include <math.h>

Iman::Iman(unsigned int nQ, GLfloat rInt, GLfloat rExt, GLfloat h) {

	m = 4;
	n = nQ;

	// Construimos el perfil
	perfil = new PuntoVector3D*[m];
	Iman::construirPerfil(rInt, rExt, h);

	// Tamaño de los arrays
	numeroVertices	= (n * m) + (2 * m);				// Vertices de la parte revolucionada (n*m) + vertices de los polos (2*m)
	numeroCaras		= ((n - 1) * m) + (2 * (m + 1));
	numeroNormales	= numeroCaras;
	carasRevolucion = (n - 1) * m;

	// Creamos los arrays
	vertice	= new PuntoVector3D*[numeroVertices];
	normal	= new PuntoVector3D*[numeroNormales];
	cara	= new Cara*[numeroCaras];

	//Colocar el perfil original en la tabla de vertices
	for (int j=0; j<m; j++) {
		vertice[j] = perfil[j]->clonar();
	}

	//Vertices de la malla
	Iman::construirVerticesMalla();

/*Vértices de los rectángulos del imán */
	//Rectángulo derecho
	vertice[indice+1] = new PuntoVector3D(rInt, 0.0f, h, 1);
	vertice[indice+2] = new PuntoVector3D(rExt, 0.0f, h, 1);
	vertice[indice+3] = new PuntoVector3D(rExt, h, h, 1);
	vertice[indice+4] = new PuntoVector3D(rInt, h, h, 1);

	//Rectángulo izquierdo
	vertice[indice+5] = new PuntoVector3D(-rInt, 0.0f, h, 1);
	vertice[indice+6] = new PuntoVector3D(-rExt, 0.0f, h, 1);
	vertice[indice+7] = new PuntoVector3D(-rExt, h, h, 1);
	vertice[indice+8] = new PuntoVector3D(-rInt, h, h, 1);

	//Construcción de las caras
	Iman::construirCarasIman();

	
/* Caras de los polos del imán */
	//Polo derecho
	Iman::construirPoloDerecho();

	//Polo izquierdo
	Iman::construirPoloIzquierdo();
}

void Iman::construirPerfil(GLfloat rInt, GLfloat rExt, GLfloat h) {

	perfil[0] = new PuntoVector3D(rInt, 0.0f, 0.0f, 1);
	perfil[1] = new PuntoVector3D(rExt, 0.0f, 0.0f, 1);
	perfil[2] = new PuntoVector3D(rExt, h, 0.0f, 1);
	perfil[3] = new PuntoVector3D(rInt, h, 0.0f, 1);

}

void Iman::construirVerticesMalla() {

	// Generamos los perfiles desde 0..nQ-1
	for (int i=1; i<n; i++) { 
		
		double theta = i*3.14159265/(double)(n-1);
		double c	 = cos(theta);
		double s	 = sin(theta);

		//R_y es la matriz de rotación sobre el eje Y
		for (int j=0; j<m; j++) {
			indice = i*m+j;
			//Transformar el punto j-ésimo del perfil original
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PuntoVector3D* p = new PuntoVector3D(x, perfil[j]->getY(), z, 1);
			vertice[indice]  = p;
		} //for
	} //for

}

void Iman::construirCarasIman() {

	indiceCara = 0;
	for (int i=0; i<n-1; i++) { //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j=0; j<m; j++) { //esquina inferior-izquierda de una cara
		//indiceCara = i*(m-1) + j;
		VerticeNormal** vn = new VerticeNormal*[4];
		vn[0]=new VerticeNormal(i*m+j,indiceCara);
		vn[1]=new VerticeNormal(((i+1)*m+j),indiceCara);
		vn[2]=new VerticeNormal((i*m+((j+1)%m)+m),indiceCara);
		vn[3]=new VerticeNormal(i*m+((j+1)%m),indiceCara);
		cara[indiceCara] = new Cara(4, vn);

		PuntoVector3D* v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
		normal[indiceCara]= v;
		indiceCara++;

		} //for
	} //for

}

PuntoVector3D* Iman::calcularVectorNormalPorProductoVectorial(Cara* cara) {

	
	float v1x = vertice[cara->getIndiceVerticeK(2)]->getX() - vertice[cara->getIndiceVerticeK(1)]->getX();
	float v1y = vertice[cara->getIndiceVerticeK(2)]->getY() - vertice[cara->getIndiceVerticeK(1)]->getY();
	float v1z = vertice[cara->getIndiceVerticeK(2)]->getZ() - vertice[cara->getIndiceVerticeK(1)]->getZ();

	float v2x = vertice[cara->getIndiceVerticeK(0)]->getX() - vertice[cara->getIndiceVerticeK(1)]->getX();
	float v2y = vertice[cara->getIndiceVerticeK(0)]->getY() - vertice[cara->getIndiceVerticeK(1)]->getY();
	float v2z = vertice[cara->getIndiceVerticeK(0)]->getZ() - vertice[cara->getIndiceVerticeK(1)]->getZ();

	PuntoVector3D* pv1 = new PuntoVector3D(v1x, v1y, v1z, 0);
	PuntoVector3D* pv2 = new PuntoVector3D(v2x, v2y, v2z, 0);

	return pv1->productoVectorial(pv2);

}

void Iman::construirPoloDerecho() {

	VerticeNormal** vn;
	PuntoVector3D* v;

	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(0,indiceCara);
	vn[1] = new VerticeNormal(indice+1,indiceCara);
	vn[2] = new VerticeNormal(indice+4,indiceCara);
	vn[3] = new VerticeNormal(3,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+1,indiceCara);
	vn[1] = new VerticeNormal(0,indiceCara);
	vn[2] = new VerticeNormal(1,indiceCara);
	vn[3] = new VerticeNormal(indice+2,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+2,indiceCara);
	vn[1] = new VerticeNormal(1,indiceCara);
	vn[2] = new VerticeNormal(2,indiceCara);
	vn[3] = new VerticeNormal(indice+3,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(3,indiceCara);
	vn[1] = new VerticeNormal(indice+4,indiceCara);
	vn[2] = new VerticeNormal(indice+3,indiceCara);
	vn[3] = new VerticeNormal(2,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+1,indiceCara);
	vn[1] = new VerticeNormal(indice+2,indiceCara);
	vn[2] = new VerticeNormal(indice+3,indiceCara);
	vn[3] = new VerticeNormal(indice+4,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

}

void Iman::construirPoloIzquierdo() {

	VerticeNormal** vn;
	PuntoVector3D* v;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice-2,indiceCara);
	vn[1] = new VerticeNormal(indice+6,indiceCara);
	vn[2] = new VerticeNormal(indice+7,indiceCara);
	vn[3] = new VerticeNormal(indice-1,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+6,indiceCara);
	vn[1] = new VerticeNormal(indice-2,indiceCara);
	vn[2] = new VerticeNormal(indice-3,indiceCara);
	vn[3] = new VerticeNormal(indice+5,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+5,indiceCara);
	vn[1] = new VerticeNormal(indice-3,indiceCara);
	vn[2] = new VerticeNormal(indice,indiceCara);
	vn[3] = new VerticeNormal(indice+8,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice-1,indiceCara);
	vn[1] = new VerticeNormal(indice+7,indiceCara);
	vn[2] = new VerticeNormal(indice+8,indiceCara);
	vn[3] = new VerticeNormal(indice,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

	vn    = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(indice+6,indiceCara);
	vn[1] = new VerticeNormal(indice+5,indiceCara);
	vn[2] = new VerticeNormal(indice+8,indiceCara);
	vn[3] = new VerticeNormal(indice+7,indiceCara);
	cara[indiceCara] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
	normal[indiceCara]= v;
	indiceCara++;

}


void Iman::dibuja() {
	
	int mitad = carasRevolucion / 2;

	for (int i = 0; i<numeroCaras; i++) {
		glBegin(GL_POLYGON);
		glColor3f(0.0f,0.0f,1.0f);

		if (i > mitad)
			glColor3f(1.0f,0.0f,0.0f);

		if (i >= carasRevolucion)
			glColor3f(0.8f,0.8f,0.8f);

		for (int j = 0; j<cara[i]->getNumeroVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}
