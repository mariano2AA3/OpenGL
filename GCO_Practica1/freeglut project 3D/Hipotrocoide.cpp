#include "Hipotrocoide.h"

#include <iostream>
using namespace std;

Hipotrocoide::Hipotrocoide( int nP,  int nQ) {

	a = 7.0f;
	b = 4.0f;
	c = 2.0f;

	mode = GL_POLYGON;

	// Construimos el perfil sobre el plano XY
	construirPerfil(nP);

	// Inicializamos la matriz de la tranformacion
	mt = new GLfloat[16];

	// Tamaño de los arrays
	numeroVertices	= nP * nQ;
	numeroCaras		= nP * (nQ-1);
	numeroNormales	= numeroCaras;

	// Creamos los arrays
	vertice	= new PuntoVector3D*[numeroVertices];
	normal	= new PuntoVector3D*[numeroNormales];
	cara	= new Cara*[numeroCaras];

	// Construimos los vertices y las caras (y las normales)
	Hipotrocoide::construirVerticesMalla(nP, nQ);
	Hipotrocoide::construirCarasMalla(nP, nQ);

}

void Hipotrocoide::construirPerfil(int nP){
	
	GLfloat radio = 0.5f;
	perfil = new PuntoVector3D*[nP];
	GLfloat inc = (2 * 3.14159265f) / nP;

	for (int i = 0; i < nP; i++){
		perfil[i] = new PuntoVector3D(radio * cos(i * inc), radio * sin(i * inc), 0, 1);
	}

}

PuntoVector3D* Hipotrocoide::calcularCt(GLfloat t){
	return new PuntoVector3D((a - b)*cos(t) + c*cos(((a - b) / b)*t), 0.0f, (a - b)*sin(t) - c*sin(((a - b) / b)*t), 1);
}

PuntoVector3D* Hipotrocoide::calcularDerivadaCt(GLfloat t){
	return new PuntoVector3D(-(a - b)*sin(t) - c*sin(((a - b) / b)*t)*((a - b) / b),   
							0.0f,
							(a - b)*cos(t) - c*cos(((a - b) / b)*t)*((a - b) / b), 0);
}

PuntoVector3D* Hipotrocoide::calcularDerivadaSegundaCt(GLfloat t){
	return new PuntoVector3D(-(a - b)*cos(t) - c*cos(((a - b) / b)*t)*((a - b) / b)*((a - b) / b),
							0.0f,
							-(a - b)*sin(t) + c*sin(((a - b) / b)*t)*((a - b) / b)*((a - b) / b), 0);
}

PuntoVector3D* Hipotrocoide::calcularTt(GLfloat t){
	PuntoVector3D* aux = Hipotrocoide::calcularDerivadaCt(t);
	aux->normalizar();
	return aux;
}

PuntoVector3D* Hipotrocoide::calcularBt(GLfloat t){
	PuntoVector3D* derivada1 = Hipotrocoide::calcularDerivadaCt(t);
	PuntoVector3D* derivada2 = Hipotrocoide::calcularDerivadaSegundaCt(t);
	PuntoVector3D* pv = (derivada1->productoVectorial(derivada2));
	pv->normalizar();
	return pv;
}

PuntoVector3D* Hipotrocoide::calcularNt(GLfloat t){
	PuntoVector3D* bt = Hipotrocoide::calcularBt(t);
	PuntoVector3D* tt = Hipotrocoide::calcularTt(t);
	return bt->productoVectorial(tt);
}

void Hipotrocoide::darValoraMt(GLfloat t){
	mt[0] = Hipotrocoide::calcularNt(t)->getX();
	mt[1] = Hipotrocoide::calcularNt(t)->getY();
	mt[2] = Hipotrocoide::calcularNt(t)->getZ();
	mt[3] = 0.0f;
	mt[4] = Hipotrocoide::calcularBt(t)->getX();
	mt[5] = Hipotrocoide::calcularBt(t)->getY();
	mt[6] = Hipotrocoide::calcularBt(t)->getZ();
	mt[7] = 0.0f;
	mt[8] = Hipotrocoide::calcularTt(t)->getX();
	mt[9] = Hipotrocoide::calcularTt(t)->getY();
	mt[10] = Hipotrocoide::calcularTt(t)->getZ();
	mt[11] = 0.0f;
	mt[12] = Hipotrocoide::calcularCt(t)->getX();
	mt[13] = Hipotrocoide::calcularCt(t)->getY();
	mt[14] = Hipotrocoide::calcularCt(t)->getZ();
	mt[15] = 1.0f;
}

void Hipotrocoide::construirVerticesMalla( int nP,  int nQ) {
	int indice;

	// Generamos los perfiles desde 0..(nQ-1)
	for (int i = 0; i<nQ; i++) { //generar el perfil i-ésimo

		GLfloat t = (i * 8 * 3.14159265f) / (GLfloat)(nQ - 1);
		// Actualizamos el valor de la matriz de transformacion en funcion de la posicion del perfil
		Hipotrocoide::darValoraMt(t);		

		// Para cada pefil, generamos los vertices desde 0..(nP-1)
		for (int j = 0; j<nP; j++) {
			indice = i*nP + j;
			// Colocamos cada vertice en su posicion multiplicandolo por la mt.
			vertice[indice] = Hipotrocoide::calcularPerfilPorMt(j);		
		} //for
	} //for

}

PuntoVector3D* Hipotrocoide::calcularPerfilPorMt(int puntoPerfil) {
	
	GLfloat coord[3];

	for (int i = 0; i < 3; i++){
		coord[i] = perfil[puntoPerfil]->getX() * mt[i + 0];
		coord[i] += perfil[puntoPerfil]->getY() * mt[i + 4];
		coord[i] += perfil[puntoPerfil]->getZ() * mt[i + 8];
		coord[i] += mt[i + 12];
	}

	return new PuntoVector3D(coord[0], coord[1], coord[2], 1);


}

void Hipotrocoide::construirCarasMalla( int nP,  int nQ){
	//Construcción de las caras
	int indiceCara = 0;

	// Unimos el perfil i-ésimo con el (i+1)%nQ-ésimo	
	for (int i = 0; i<nQ; i++){ 
		for (int j = 0; j<nP; j++) {
			
			int indice = i*nP + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0]=new VerticeNormal(i*nP+j,indiceCara);
			vn[1]=new VerticeNormal(i*nP+((j+1)%nP),indiceCara);
			//vn[2]=new VerticeNormal((i*nP+((j+1)%nP)+nP) % numeroVertices,indiceCara);
			//vn[3]=new VerticeNormal((i*nP+j+nP) % numeroVertices,indiceCara);

			vn[2]=new VerticeNormal((i*nP+(j+1)+nP) % numeroVertices,indiceCara);
			vn[3]=new VerticeNormal(((i+1)*nP+j) % numeroVertices,indiceCara);
			
			
			cara[indiceCara] = new Cara(4, vn);

			PuntoVector3D* v = calcularVectorNormalPorProductoVectorial(cara[indiceCara]);
			normal[indiceCara] = v;
			indiceCara++;
		} //for
	} //for
}


PuntoVector3D* Hipotrocoide::calcularVectorNormalPorProductoVectorial(Cara* cara) {

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

void Hipotrocoide::setMode(int m) {	 	 
	mode = m; 
}

void Hipotrocoide::dibuja() {	 	

	glColor3f(0.160784f, 0.301960f, 1.0f);

	for (int i=0; i<numeroCaras; i++) {		
		glBegin(mode);		 
		for (int j=0; j<cara[i]->getNumeroVertices(); j++) {
			int iN=cara[i]->getIndiceNormalK(j);
			int iV=cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());            				 
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}	 
}
