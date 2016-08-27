#include "Hipotrocoide.h"

#include <iostream>
using namespace std;

Hipotrocoide::Hipotrocoide( int nP,  int nQ, Camara* camara) {

	// Guardamos la referencia de la cámara en el hipotrocoide para que éste pueda moverla por sí mismo.
	this->camara = camara;

	//camara->switchMode();
	//camara->setProjection(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 5.0f);

	camara->setProjection(500.0f, 50.0f, 50.0f, 50.0f, 1, 1000);

	this->nP = nP;
	this->nQ = nQ;
	distancia = 0;

	a = 7.0f;
	b = 4.0f;
	c = 2.0f;
	mode = GL_POLYGON;

	construirPerfil();

	mt = new GLfloat[16];

	// Tamaño de los arrays
	numeroVertices = nP * nQ;
	numeroCaras = nP * (nQ-1);
	numeroNormales = numeroCaras;

	// Creamos los arrays
	vertice = new PuntoVector3D*[numeroVertices];
	normal = new PuntoVector3D*[numeroNormales];
	cara = new Cara*[numeroCaras];

	Hipotrocoide::construirVerticesMalla();
	Hipotrocoide::construirCarasMalla();
	Hipotrocoide::avanza();
}

void Hipotrocoide::construirPerfil() {
	
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

void Hipotrocoide::construirVerticesMalla() {
	int indice;
	for (int i = 0; i<nQ; i++) { //generar el perfil i-ésimo

		GLfloat t = (i * 8 * 3.14159265f) / (GLfloat)(nQ - 1);
		Hipotrocoide::darValoraMt(t);

		for (int j = 0; j<nP; j++) {
			indice = i*nP + j;
			// Calculamos la multiplicación del perfil con Mt.
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

PuntoVector3D* Hipotrocoide::calcularPosCamara() {
	GLfloat coord[3];

	for (int i = 0; i < 3; i++){
		coord[i] = mt[i + 12];
	}

	return new PuntoVector3D(coord[0], coord[1], coord[2], 1);
}

void Hipotrocoide::avanza() {
	GLfloat t;
	PuntoVector3D* p;
	
	// Calculamos la posicion donde debe estar la cámara.
	t = (distancia * 8 * 3.14159265f) / (GLfloat)(nQ - 1);
	Hipotrocoide::darValoraMt(t);
	p = calcularPosCamara();
	camara->setEye(p->getX(), p->getY(), p->getZ());

	// Calculamos dónde debe mirar la cámara.
	t = ((distancia + 1) * 8 * 3.14159265f) / (GLfloat)(nQ - 1);
	Hipotrocoide::darValoraMt(t);
	p = calcularPosCamara();
	camara->setLook(p->getX(), p->getY(), p->getZ());

	// Sumamos 1 a la distancia recorrida por la cámara dentro del hipotrocoide.
	distancia++;
}

void Hipotrocoide::construirCarasMalla(){
	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i<nQ; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo	
		for (int j = 0; j<nP; j++) {
			// indiceCara = i*(m-1) + j;
			int indice = i*nP + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0]=new VerticeNormal(i*nP+j,indiceCara);
			vn[1]=new VerticeNormal(i*nP+((j+1)%nP),indiceCara);
			vn[2]=new VerticeNormal((i*nP+((j+1)%nP)+nP) % numeroVertices,indiceCara);
			vn[3]=new VerticeNormal((i*nP+j+nP) % numeroVertices,indiceCara);
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

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glColor3f(0.274509f, 0.447058f, 0.65098f);

	Hipotrocoide::dibujaAux();

	glCullFace(GL_FRONT);
	glColor3f(0.6f, 0.729411f, 0.878431f);

	Hipotrocoide::dibujaAux();


}

void Hipotrocoide::dibujaAux() {
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glColor3f(0.09f, 0.482f, 0.207f);		// Color verde
	//glMultMatrixf(this->dameMatrizAfin());
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	for (int i = 0; i<numeroCaras; i++) {
		glBegin(mode);
		for (int j = 0; j<cara[i]->getNumeroVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
	glPopMatrix();
}
