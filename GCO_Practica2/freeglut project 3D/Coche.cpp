#include "Coche.h"
#include "Rueda.h"
#include "Faro.h"

Coche::Coche() {

/* Inicializamos las variables */
	this->pos				= 0;
	this->ladoChasis		= 3.0f;
	this->radioFaros		= 0.25f;
	this->radioRuedas		= 1.0f;
	this->grosorRuedas		= 0.85f;
	this->ladosRueda		= 10;
	this->rodajasRueda		= 15;
	
	// Chasis
	this->introduceObjeto( Coche::construirChasis() );
	this->hijos[0]->traslada(0.0f, 0.0f, this->ladoChasis);
	this->hijos[0]->rota(90.0f, 0.0f, 1.0f, 0.0f);
	this->hijos[0]->setColor(0.9f, 0, 0.7f);


/* Faros*/
	// Izquierdo
	this->introduceObjeto(new Faro(this->radioFaros, this->radioFaros, 1.0f, 10, 10, GL_LIGHT1));
	this->hijos[1]->setColor(0.1f, 0.9f, 0.2f);
	this->hijos[1]->traslada(this->ladoChasis - this->radioFaros - 0.3f, this->ladoChasis/3.0f, this->ladoChasis - this->radioFaros - this->radioFaros);
	this->hijos[1]->rota(90.0f, 0.0f, 1.0f, 0.0f);

	// Derecho
	//this->introduceObjeto( new Cilindro(this->radioFaros, this->radioFaros, 1.0f, 10, 10) );
	this->introduceObjeto(new Faro(this->radioFaros, this->radioFaros, 1.0f, 10, 10, GL_LIGHT2));
	this->hijos[2]->setColor(0.1f, 0.9f, 0.2f);
	this->hijos[2]->traslada(this->ladoChasis - this->radioFaros - 0.3f, this->ladoChasis/3.0f, this->radioFaros + this->radioFaros);
	this->hijos[2]->rota(90.0f, 0.0f, 1.0f, 0.0f);

/* Ruedas */
	// Rueda trasera izquierda
	this->introduceObjeto( new Rueda(this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda) );
	this->hijos[3]->traslada(0.0f, 0.0f, this->ladoChasis);

	// Rueda trasera derecha
	this->introduceObjeto( new Rueda(this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda) );
	this->hijos[4]->rota(180.0f, 1.0f, 0.0f, 0.0f);
	this->hijos[4]->traslada(0.0f, 0.0f, 0.0f);

	// Rueda delantera izquierda
	this->introduceObjeto( new Rueda(this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda) );
	this->hijos[5]->traslada(this->ladoChasis, 0.0f, this->ladoChasis);

	// Rueda delantera derecha
	this->introduceObjeto( new Rueda(this->radioRuedas, this->grosorRuedas, this->ladosRueda, this->rodajasRueda) );
	this->hijos[6]->rota(180.0f, 1.0f, 0.0f, 0.0f);
	this->hijos[6]->traslada(this->ladoChasis, 0.0f, 0.0f);

	this->traslada(0.0f, this->radioRuedas, 0.0f);

/* Luces */
	this->iniciarLuces();
}

Coche::~Coche() { 
	for( int i=0; i<this->numHijos; ++i) {
		this->hijos[i]->~Objeto3D();
	}
}

void Coche::avanza(GLfloat distancia) {

	GLfloat sentido = -1;

	// Trasladamos todo el coche
	this->traslada(distancia, 0.0f, 0.0f);
	
	// Giramos las ruedas
	if (distancia < 0)
		sentido = 1;

	this->hijos[3]->rota(distancia + 50 * sentido, 0.0f, 0.0f, 1.0f);
	this->hijos[5]->rota(distancia + 50 * sentido, 0.0f, 0.0f, 1.0f);
	this->hijos[4]->rota(distancia - 50 * sentido, 0.0f, 0.0f, 1.0f);
	this->hijos[6]->rota(distancia - 50 * sentido, 0.0f, 0.0f, 1.0f);
}

void Coche::gira(GLfloat angulo) {

	this->rota(angulo, 0.0f, 1.0f, 0.0f);
}

void Coche::iniciarLuces() {
	GLfloat d1[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat s1[] = { 1.0f, 1.0f, 0.0f, 1.0f };

	// Faro izquiero
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, d1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, d1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, s1);

	// Faro derecho
	glDisable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, d1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, d1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, s1);
	
}

void Coche::encenderFaros() {
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

void Coche::apagarFaros() {
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
}

Malla* Coche::construirChasis() {
		
	// Tamaño de los arrays
	int numVertices = 8;
	int numCaras	= 6;
	int numNormales = numCaras;

	// Creamos los arrays
	PuntoVector3D** vertices = new PuntoVector3D*[numVertices];
	PuntoVector3D** normales = new PuntoVector3D*[numNormales];
	Cara** caras			 = new Cara*[numCaras];

	// Base inferior del chasis (sentido horario mirando el plano XZ)
	vertices[0] = new PuntoVector3D(0.0f, 0.0f, 0.0f, 1);
	vertices[1] = new PuntoVector3D(this->ladoChasis, 0.0f, 0.0f, 1);
	vertices[2] = new PuntoVector3D(this->ladoChasis, 0.0f, this->ladoChasis, 1);
	vertices[3] = new PuntoVector3D(0.0f, 0.0f, this->ladoChasis, 1);
	
	// Base superior del chasis (sentido horario mirando el plano XZ)
	vertices[4] = new PuntoVector3D(0.0f, this->ladoChasis, 0.0f, 1);
	vertices[5] = new PuntoVector3D(this->ladoChasis, this->ladoChasis, 0.0f, 1);
	vertices[6] = new PuntoVector3D(this->ladoChasis, this->ladoChasis, this->ladoChasis,1);
	vertices[7] = new PuntoVector3D(0.0f, this->ladoChasis, this->ladoChasis, 1);

	// Contruimos la cara inferior
	VerticeNormal** vn;
	PuntoVector3D* v;

	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(0, 0);
	vn[1] = new VerticeNormal(1, 0);
	vn[2] = new VerticeNormal(2, 0);
	vn[3] = new VerticeNormal(3, 0);
	caras[0] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[0]);
	normales[0]= v;
	
	// Contruimos la cara lateral izquiera
	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(7, 1);
	vn[1] = new VerticeNormal(3, 1);
	vn[2] = new VerticeNormal(2, 1);
	vn[3] = new VerticeNormal(6, 1);
	caras[1] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[1]);
	normales[1]= v;

	// Contruimos la cara superior
	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(7, 2);
	vn[1] = new VerticeNormal(6, 2);
	vn[2] = new VerticeNormal(5, 2);
	vn[3] = new VerticeNormal(4, 2);
	caras[2] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[2]);
	normales[2]= v;
	
	// Contruimos la cara lateral derecha
	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(5, 3);
	vn[1] = new VerticeNormal(1, 3);
	vn[2] = new VerticeNormal(0, 3);
	vn[3] = new VerticeNormal(4, 3);
	caras[3] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[3]);
	normales[3]= v;

	// Contruimos la cara posterior
	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(3, 4);
	vn[1] = new VerticeNormal(7, 4);
	vn[2] = new VerticeNormal(4, 4);
	vn[3] = new VerticeNormal(0, 4);
	caras[4] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[4]);
	normales[4]= v;

	// Contruimos la cara frontal
	vn	  = new VerticeNormal*[4];
	vn[0] = new VerticeNormal(5, 5);
	vn[1] = new VerticeNormal(6, 5);
	vn[2] = new VerticeNormal(2, 5);
	vn[3] = new VerticeNormal(1, 5);
	caras[5] = new Cara(4, vn);
	v = calcularVectorNormalPorProductoVectorial(vertices, caras[5]);
	normales[5]= v;

	return new Malla(numVertices, numNormales, numCaras, vertices, normales, caras);
}

PuntoVector3D* Coche::calcularVectorNormalPorProductoVectorial(PuntoVector3D** vertices, Cara* cara) {

	float v1x = vertices[cara->getIndiceVerticeK(2)]->getX() - vertices[cara->getIndiceVerticeK(1)]->getX();
	float v1y = vertices[cara->getIndiceVerticeK(2)]->getY() - vertices[cara->getIndiceVerticeK(1)]->getY();
	float v1z = vertices[cara->getIndiceVerticeK(2)]->getZ() - vertices[cara->getIndiceVerticeK(1)]->getZ();

	float v2x = vertices[cara->getIndiceVerticeK(0)]->getX() - vertices[cara->getIndiceVerticeK(1)]->getX();
	float v2y = vertices[cara->getIndiceVerticeK(0)]->getY() - vertices[cara->getIndiceVerticeK(1)]->getY();
	float v2z = vertices[cara->getIndiceVerticeK(0)]->getZ() - vertices[cara->getIndiceVerticeK(1)]->getZ();

	PuntoVector3D* pv1 = new PuntoVector3D(v1x, v1y, v1z, 0);
	PuntoVector3D* pv2 = new PuntoVector3D(v2x, v2y, v2z, 0);

	return pv1->productoVectorial(pv2);

}
