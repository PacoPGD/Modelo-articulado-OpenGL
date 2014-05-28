
//g++ -o ejecutable main.cpp -lGL -lglut -lGLU
//g++ -o ejecutable main.cpp -lGL -lglut -lGLU -L/usr/X11R6/lib -L/usr/local/lib


#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>



#include "esqueleto.hpp"




Esqueleto e;
GLdouble camX=0.0, camY=100.0, camZ=-250.0;


/********************************************************************/
int hsize=500;

GLdouble eyeX=100;
GLdouble eyeY=0;
GLdouble eyeZ=-200.0f;

void dibujarEje(){
		glLineWidth(1.0f);
		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(100.0f,0.0f,0.0f);
	
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,100.0f,0.0f);
	
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,100.0f);
			glLineWidth(3.0f);
		glEnd();
}


void DibujaEscena(){
	glClearColor(1.,1.,1.,1.);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 100.0, 500.0);
	gluLookAt(camX, camY, camZ, 0, 100, 0, 0, 1.0, 0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	dibujarEje();
  e.dibujar();
  

	glutSwapBuffers();
	glFinish();
}


void aniSalto(int t){
	Vector3f aux;
	
	if(t<50){
		aux = e.joins[ROOT].angle;
		aux.x+=0.3f;
		e.joins[ROOT].rotate(aux);
	
		aux = e.joins[RODILLA_DER].angle;
		aux.x+=0.8f;
		e.joins[RODILLA_DER].rotate(aux);
		e.joins[RODILLA_IZQ].rotate(aux);
		
		aux = e.joins[CADERA_DER].angle;
		aux.x-=0.5f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
		
		aux = e.joins[HOMBRO_DER].angle;
		aux.x+=0.5f;
		e.joins[HOMBRO_DER].rotate(aux);
		e.joins[HOMBRO_IZQ].rotate(aux);
		
		aux = e.joins[CINTURA].angle;
		aux.x-=0.5f;
		e.joins[CINTURA].rotate(aux);
		
		e.move(e.globalPos.x, e.globalPos.y-0.1f, e.globalPos.z);
	}else if(t<75){
		aux = e.joins[ROOT].angle;
		aux.x-=0.2f;
		e.joins[ROOT].rotate(aux);
	
		aux = e.joins[RODILLA_DER].angle;
		aux.x+=0.2f;
		e.joins[RODILLA_DER].rotate(aux);
		e.joins[RODILLA_IZQ].rotate(aux);
		
		aux = e.joins[CADERA_DER].angle;
		aux.x-=0.1f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
		
		aux = e.joins[HOMBRO_DER].angle;
		aux.x-=0.2f;
		e.joins[HOMBRO_DER].rotate(aux);
		e.joins[HOMBRO_IZQ].rotate(aux);
		
		aux = e.joins[CINTURA].angle;
		aux.x+=0.2f;
		e.joins[CINTURA].rotate(aux);
	}else if(t<150){
		if(t<125){
			aux = e.joins[HOMBRO_DER].angle;
			aux.x-=2.8f;
			e.joins[HOMBRO_DER].rotate(aux);
			e.joins[HOMBRO_IZQ].rotate(aux);
		}
		
		aux = e.joins[ROOT].angle;
		aux.x-=0.1f;
		e.joins[ROOT].rotate(aux);
	
		aux = e.joins[RODILLA_DER].angle;
		aux.x-=0.8f;
		e.joins[RODILLA_DER].rotate(aux);
		e.joins[RODILLA_IZQ].rotate(aux);
		
		aux = e.joins[CADERA_DER].angle;
		aux.x+=1.0f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
		

		
		aux = e.joins[CINTURA].angle;
		aux.x-=0.5f;
		e.joins[CINTURA].rotate(aux);
		
		e.move(e.globalPos.x, e.globalPos.y+0.5f, e.globalPos.z);
	}else if(t<200){
		e.move(e.globalPos.x, e.globalPos.y+0.2f, e.globalPos.z);
	}else if(t<225){
		aux = e.joins[CADERA_DER].angle;
		aux.x-=0.1f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
		
		e.move(e.globalPos.x, e.globalPos.y-0.3f, e.globalPos.z);
	}else if(t<275){
		aux = e.joins[CINTURA].angle;
		aux.x-=0.5f;
		e.joins[CINTURA].rotate(aux);
	
		aux = e.joins[CADERA_DER].angle;
		aux.x-=0.5f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
			
		aux = e.joins[RODILLA_DER].angle;
		aux.x+=0.5f;
		e.joins[RODILLA_DER].rotate(aux);
		e.joins[RODILLA_IZQ].rotate(aux);
		
		e.move(e.globalPos.x, e.globalPos.y-0.8f, e.globalPos.z);
	}else if(t<300){
		aux = e.joins[CINTURA].angle;
		aux.x-=0.5f;
		e.joins[CINTURA].rotate(aux);
	
		aux = e.joins[CADERA_DER].angle;
		aux.x-=0.1f;
		e.joins[CADERA_DER].rotate(aux);
		e.joins[CADERA_IZQ].rotate(aux);
			
		aux = e.joins[RODILLA_DER].angle;
		aux.x-=0.5f;
		e.joins[RODILLA_DER].rotate(aux);
		e.joins[RODILLA_IZQ].rotate(aux);
		
		aux = e.joins[HOMBRO_DER].angle;
		aux.x+=1.0f;
		e.joins[HOMBRO_DER].rotate(aux);

		e.joins[HOMBRO_IZQ].rotate(aux);
		e.move(e.globalPos.x, e.globalPos.y+0.1f, e.globalPos.z);
	}else if(t<350){
		aux = e.joins[HOMBRO_DER].angle;
		aux.x+=1.3f;
		e.joins[HOMBRO_DER].rotate(aux);
		e.joins[HOMBRO_IZQ].rotate(aux);
	}

	printf("-> %d\n",t);
	if(t<350){
		glutTimerFunc(1000.0/60.0, aniSalto, t+1);
	}else{
		e.poseReposo();
	}
	glutPostRedisplay();
}

void aniSaludo(int t){
	Vector3f aux;
	
	if(t<60){
		aux = e.joins[ROOT].angle;
		aux.y+=0.5f;
		e.joins[ROOT].rotate(aux);
	}
	else if(t<90)
	{
		aux = e.joins[TORSO].angle;
		aux.y-=0.5f;
		e.joins[TORSO].rotate(aux);
	}

	else if(t<200)
	{
		aux = e.joins[HOMBRO_DER].angle;
		aux.x+=1.0f;
		e.joins[HOMBRO_DER].rotate(aux);
		aux = e.joins[CODO_IZQ].angle;
		aux.z+=1.2f;
		e.joins[CODO_IZQ].rotate(aux);
	}


	printf("-> %d\n",t);
	if(t<300){
		glutTimerFunc(1000.0/60.0, aniSaludo, t+1);
	}else{
		e.poseReposo();
	}
	glutPostRedisplay();
}

	

void EscalaVentana(GLsizei w, GLsizei h){
	if(h==0) h=1;
	glViewport(0,0,w,h); // 0, 0, w, h
	hsize=h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLdouble fovy=60;
	GLdouble aspect=1.0;
	GLdouble  zNear=100.0;
	GLdouble  zFar=500.0;
	gluPerspective(  fovy,    aspect,    zNear,    zFar);
	GLdouble centerX=0;
	GLdouble centerY=100;
	GLdouble centerZ=0;
	GLdouble upX=0;
	GLdouble upY=1.0f;
	GLdouble upZ=0;	
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void myKeyboard(unsigned char key,int x, int y){
	Vector3f aux;
	aux = e.joins[e.joinSelect].angle;

	switch(key){
		case 'o':
			if(e.joinSelect<(e.joins.size()-1)){
				e.joinSelect++;
			}
			else{
				e.joinSelect=0;
			}
		break;
		case 'l':
			if(e.joinSelect>0){
				e.joinSelect--;
			}
			else{
				e.joinSelect=e.joins.size()-1;
			}
		break;

		case 'a':
			aux.y++;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 'd':
			aux.y--;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 'w':
			aux.x++;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 's':
			aux.x--;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 'e':
			aux.z++;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 'q':
			aux.z--;
			e.joins[e.joinSelect].rotate(aux);
		break;
		case 't':
			aniSaludo(0);
		break;
		case 'g':
			aniSalto(0);
		break;
		case 27:
			exit (0);
	}
	glutPostRedisplay();
}



void myKeyboardSpecial(int key,int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
		camX-=5.0f;
		break;
		case GLUT_KEY_RIGHT:
		camX+=5.0f;
		break;
		case GLUT_KEY_UP:
		camY+=5.0f;
		break;
		case GLUT_KEY_DOWN:
		camY-=5.0f;
		break;
		case GLUT_KEY_PAGE_DOWN:
		camZ-=5.0f;
		break;
		case GLUT_KEY_PAGE_UP:
		camZ+=5.0f;
		break;
	}
	glutPostRedisplay();
}


int main(int argcp, char **argv){
  e.init();
  glutInit(&argcp,argv);
  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA /*| GLUT_DEPTH*/);
	glutInitWindowSize(hsize,hsize);
	glutCreateWindow("Esqueleto");
	
	glutDisplayFunc(DibujaEscena);
	glutReshapeFunc(EscalaVentana);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(myKeyboardSpecial);

	glutMainLoop();

}
