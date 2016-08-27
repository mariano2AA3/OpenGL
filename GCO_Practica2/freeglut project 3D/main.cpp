/*
 * Authors: Jorge Casas Hernan
 *	        Mariano Hernandez Garcia
 */

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>

#include "Camara.h"
#include "Abeto.h"
#include "Roble.h"
#include "Pino.h"
#include "Alamo.h"
#include "Hipotrocoide.h"
#include "Coche.h"
#include "Esfera.h"
#include "Farola.h"

using namespace std;


#define bosque
//#define camara_hipotrocoide

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

bool baldosas = false;
bool luzDireccional = false;

// Viewport size

int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
#if defined camara_hipotrocoide
	GLdouble xRight=0.5, xLeft=-xRight, yTop=0.5, yBot=-yTop, N=0.5, F=1000;
#else
	GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;
#endif

// Camera parameters
//GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
//GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
//GLdouble upX=0, upY=1, upZ=0;

// Scene variables
GLfloat angX, angY, angZ; 

// Objetos a dibujar de la práctica 1

Camara* camara;
Abeto* abeto;
Roble* roble;
Pino* pino;
Alamo* alamo;
Hipotrocoide* hipotrocoide;
Coche* coche;
Esfera* esfera;
Farola* farola;

void buildSceneObjects() {	 
    angX=0.0f;
    angY=0.0f;
    angZ=0.0f;	

	// Instanciación de objetos de la práctica 2

	camara = new Camara();

	
#if defined bosque
	abeto = new Abeto();
	roble = new Roble();
	pino = new Pino();
	alamo = new Alamo();
	coche = new Coche();
	farola = new Farola();
	esfera = new Esfera(1.0f, 100, 100);
	esfera->traslada(10.0f, 0.0f, 0.0f);
	esfera->escala(5.0f, 5.0f, 5.0f);
	esfera->setColor(1.0f, 0.5f, 0.0f);

#elif defined camara_hipotrocoide
	hipotrocoide = new Hipotrocoide(15, 200, camara);
#endif
}

void encenderLuzAmbiental() {
	
	GLfloat amb[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

void apagarLuzAmbiental() {
	
	GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

void encenderLuzDireccional() {
	
	glEnable(GL_LIGHT0);

	GLfloat pos[] = { 1.0f, 1.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	GLfloat af[] = {0.5f , 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, af);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, af);

}

void apagarLuzDireccional() {
	glDisable(GL_LIGHT0);
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
      
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); // Shading by default

	buildSceneObjects();

	
	glEnable(GL_LIGHTING);  
	apagarLuzAmbiental();

    
	/*// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);*/

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT); 	
 }



void drawScene(){
	glMatrixMode(GL_MODELVIEW);	 
	glPushMatrix();

	if (luzDireccional)
		encenderLuzDireccional();
	else
		apagarLuzDireccional();
	
		// Rotating the scene
		glRotatef(angX, 1.0f, 0.0f, 0.0f);
        glRotatef(angY, 0.0f, 1.0f, 0.0f);
        glRotatef(angZ, 0.0f, 0.0f, 1.0f);
		
		glLineWidth(1.5f);
		// Drawing axes
		glBegin( GL_LINES );			
			glColor3f(1.0,0.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(20, 0, 0);	     
	 
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 20, 0);	 
	 
			glColor3f(0.0,0.0,1.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 20);	     
		glEnd();
		 		
		// Drawing the scene	 		 
		glColor3f(1.0, 1.0, 1.0);
		


#if defined bosque
		abeto->dibuja();
		roble->dibuja();
		pino->dibuja();
		alamo->dibuja();
		coche->dibuja();
		esfera->dibuja();
		farola->dibuja();

#elif defined camara_hipotrocoide
		hipotrocoide->dibuja();
#endif
		


	glPopMatrix();
}


void embaldosar(int nCol){
	
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble) WIDTH / (GLdouble) nCol;
	GLdouble h = w/SVAratio;
	int cameraCount = 0;

	for (GLint c = 0; c < nCol; c++){
		GLdouble currentH = 0;
		while( (currentH + h) <= HEIGHT){
			glViewport( (GLint)(c * w), (GLint)currentH, (GLint)w, (GLint)h );	

			switch (cameraCount) {
				case 0:
					camara->lateral();
				break;

				case 1:
					camara->frontal();
				break;

				case 2:
					camara->cenital();
				break;

				case 3:
					camara->rincon();
				break;
			}
			
			drawScene();
			currentH += h;
			cameraCount++;
		}
	}
}

void desembaldosar(){
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}

void zoom(float f) {

	GLdouble newHeight = (yTop -yBot) / f;
	GLdouble yMiddle = (yBot + yTop) / 2.0;
	yTop = yMiddle + newHeight / 2.0;
	yBot = yMiddle - newHeight / 2.0;

	GLdouble newWidth = (xRight - xLeft) / f;
	GLdouble xMiddle = (xLeft + xRight) / 2.0;
	xRight = xMiddle + newWidth / 2.0;
	xLeft = xMiddle - newWidth / 2.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	camara->setProjection(xLeft, xRight, yBot, yTop, N, F);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(baldosas) embaldosar(2);
	else desembaldosar();
 
	glFlush();
	glutSwapBuffers();
}

void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;

	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	camara->setProjection(xLeft, xRight, yBot, yTop, N, F);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;		 
		case 'a': angX=angX+5; break;
		case 'z': angX=angX-5; break; 
		case 's': angY=angY+5; break;
		case 'x': angY=angY-5; break;
		case 'd': angZ=angZ+5; break;
		case 'c': angZ=angZ-5; break;
		case '1': camara->giraX(); break;
		case '2': camara->giraY(); break;
		case '3': camara->giraZ(); break;
		case '4': camara->lateral(); break;
		case '5': camara->frontal(); break;
		case '6': camara->cenital(); break;
		case '7': camara->rincon(); break;
		case '8': baldosas = true; break;
		case '9': baldosas = false; break;
		case 'q': camara->roll(25); break;
		case 'w': camara->yaw(25); break;
		case 'e': camara->pitch(25); break;
		case 'p': 
			camara->switchMode(); 
			camara->setProjection(xLeft, xRight, yBot, yTop, N, F);  
			break;
		case 'i': zoom(0.8f); break;
		case 'k': zoom(1.2f); break;
		#ifdef camara_hipotrocoide:  
			case 'ñ': hipotrocoide->avanza(); break; 
		#endif
		case 'n': coche->avanza(0.3f); break;
		case 'm': coche->avanza(-0.3f); break;
		case 't': coche->encenderFaros(); break;
		case 'g': coche->apagarFaros(); break;
		case 'v': coche->gira(0.7f); break;
		case 'b': coche->gira(-0.7f); break;
		case 'u': encenderLuzAmbiental(); break;
		case 'j': apagarLuzAmbiental(); break;
		case 'y': luzDireccional = true; break;
		case 'h': luzDireccional = false; break;
		case 'r': farola->encender(); break;
		case 'f': farola->apagar(); break;
		case 'l': roble->setMaterialEspecular(0.05f); break;
		case 'o': roble->setMaterialEspecular(-0.05f); break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

void showControls() {
	cout << "Controls " << endl;
	cout << "1 - GiraX()" << endl;
	cout << "2 - GiraY()" << endl;
	cout << "3 - GiraZ()" << endl;
	cout << "4 - Lateral()" << endl;
	cout << "5 - Frontal()" << endl;
	cout << "6 - Cenital()" << endl;
	cout << "7 - Rincon()" << endl;
	cout << "8 - Proyeccion perspectiva u ortogonal()" << endl;
	cout << "q - Roll()" << endl;
	cout << "w - Yaw()" << endl;
	cout << "e - Pitch()" << endl;
	cout << "i - ZoomOut()" << endl;
	cout << "k - ZoomIn()" << endl;
	cout << "n - cocheAdelante()" << endl;
	cout << "m - cocheAtras()" << endl;
	cout << "v - cocheGira(antihorario)" << endl;
	cout << "b - cocheGira(horario)" << endl;
	cout << "t - encenderFaros()" << endl;
	cout << "g - apagarFaros()" << endl;
	cout << "u - encenderLuzAmbiental()" << endl;
	cout << "j - apagarLuzAmbiental()" << endl;
	cout << "y - encenderLuzDireccional()" << endl;
	cout << "h - apagarLuzDireccional()" << endl;
	cout << "r - encenderFarola()" << endl;
	cout << "f - apagarFarola()" << endl;

}

int main(int argc, char *argv[]){
	cout << "Starting console..." << endl;
	showControls();

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Practica 2");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 

   
	return 0;
}
