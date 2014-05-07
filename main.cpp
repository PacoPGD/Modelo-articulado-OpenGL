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
//g++ -o ejecutable main.cpp -lGL -lglut -lGLU
/*
const int X=0;
const int Y=1;
const int Z=2;
const int D=3;
*/


#define ROOT 0
#define CUELLO 1
#define CINTURA 2
#define CABEZA 3
#define HOMBRO_DER 4
#define HOMBRO_IZQ 5
#define CADERA_DER 6
#define CADERA_IZQ 7
#define MANO_DER 8
#define MANO_IZQ 9
#define RODILLA_DER 10
#define RODILLA_IZQ 11
#define TALON_DER 13
#define TALON_IZQ 12


class Vector3f{
public:  
  float x;
  float y;
  float z;
  
  Vector3f(){
    x=0.0f;
    y=0.0f;
    z=0.0f;
  }
  
  Vector3f(float x2,float y2,float z2){
    x=x2;
    y=y2;
    z=z2;
  }
  
  void set(float x2,float y2,float z2){
    x=x2;
    y=y2;
    z=z2;
  }
  
};

class Join{
public:
	int id;
	int root;
	Vector3f limit;
	Vector3f angle;
	Vector3f pos;
	
	Join(){
    id=0;
    root=0;
	}
	
	Join(int id2, int root2, Vector3f pos2, Vector3f limit2){
    id=id2;
    root=root2;
    pos=pos2;
    limit=limit2;
    angle=Vector3f(0,0,0);
 	}
 	
 	void set(int id2, int root2, Vector3f pos2, Vector3f limit2){
    id=id2;
    root=root2;
    pos=pos2;
    limit=limit2;
 	}
 	
 	void rotate(Vector3f rot){
    angle=rot;
 	}
};

/********************************************************************/
int hsize=500;
std::vector<Join> joins;

void init(){

  
  Vector3f pos(0,0,0);
  Vector3f limit;
  Join j(0,0,pos,limit);
  joins.push_back(j);
  
  pos.set(0,20,0);
  limit.set(0,0,0);
  j.set(1,0,pos,limit);
  joins.push_back(j);
  
  pos.set(0,-20,0);
  limit.set(0,0,0);
  j.set(2,0,pos,limit);
  joins.push_back(j);
  
  pos.set(0,40,0);
  limit.set(0,0,0);
  j.set(3,1,pos,limit);
  joins.push_back(j);
  
  pos.set(20,20,0);
  limit.set(0,0,0);
  j.set(4,1,pos,limit);
  joins.push_back(j);
  
 
  pos.set(-20,20,0);
  limit.set(0,0,0);
  j.set(5,1,pos,limit);
  joins.push_back(j);
  
  pos.set(20,-20,0);
  limit.set(0,0,0);
  j.set(6,2,pos,limit);
  joins.push_back(j);
  
  pos.set(-20,-20,0);
  limit.set(0,0,0);
  j.set(7,2,pos,limit);
  joins.push_back(j);
  
  pos.set(40,20,0);
  limit.set(0,0,0);
  j.set(8,4,pos,limit);
  joins.push_back(j);
  
  pos.set(-40,20,0);
  limit.set(0,0,0);
  j.set(9,5,pos,limit);
  joins.push_back(j);
  
  pos.set(20,-40,0);
  limit.set(0,0,0);
  j.set(10,6,pos,limit);
  joins.push_back(j);
  
  /******************************/
  //Rotando
  /*******************************/
  Vector3f rot(0,0,45);
  j.rotate(rot);
  pos.set(-20,-40,0);
  limit.set(0,0,0);
  j.set(11,7,pos,limit);
  joins.push_back(j);
  j.rotate( Vector3f(0,0,0));
  
  
  pos.set(20,-60,0);
  limit.set(0,0,0);
  j.set(12,10,pos,limit);
  joins.push_back(j);
  
  pos.set(-20,-60,0);
  limit.set(0,0,0);
  j.set(13,11,pos,limit);
  joins.push_back(j);
}

void move(int id, Vector3f giro){
  
  	/*for(size_t i=0; i<joins.size(); ++i)
  	{
      if(joins[i].root==id)
        {
          glRotatef(45,1,1,1);
        }
		}*/
  
}


void rotate(Vector3f rot){
	if(rot.x>0){	glRotatef(rot.x,1,0,0);}
	if(rot.y>0){	glRotatef(rot.y,0,1,0);}
	if(rot.z>0){	glRotatef(rot.z,0,0,1); printf("->rotate\n");}
}

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

void punto(int j){
	glBegin(GL_POINTS);
		glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
	glEnd();
}

void linea(int j){
	glBegin(GL_LINES);
		glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
		int r=joins[j].root;
		glVertex3f(joins[r].pos.x,joins[r].pos.y, joins[r].pos.z);
	glEnd();
}

void DibujaEscena(){
		glClearColor(1.,1.,1.,1.);
		glClear(GL_COLOR_BUFFER_BIT);
		int currentRoot=0;
		
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
		dibujarEje();
    /*
		glPushMatrix();
    dibujarEje();
    glLineWidth(3.0f);
		glBegin(GL_LINES);
				glVertex3f(0.0f,5.0f,0.0f);
				glVertex3f(100.0f,5.0f,0.0f);
		glEnd();
		
    
        glTranslatef(10 ,10, 10);
        glRotatef(45,0,0,1);
        glTranslatef(-10.0 ,-10.0,-10.0);
				glBegin(GL_LINES);
						glVertex3f(0.0f,0.0f,0.0f);
						glVertex3f(100.0f,0.0f,0.0f);
				glEnd();
        //dibujarEje();
    glPopMatrix();
    */
    
    glColor3f(1,0,0);
    glPointSize(10.0f);
    //glPushMatrix();
    //glScalef(5.0f,1.0f,1.0f);
    
    //glRotatef(45.0f,0,0,1);
    //glTranslatef(10.0f,0,0);
    
    //glutWireCube(10.0);
    //glPopMatrix();


    
    /*glPushMatrix();
    	printf("------------abro\n");
			for(size_t i=0; i<joins.size(); ++i){
				int newRoot=joins[i].root;
				if(newRoot!=currentRoot){
					printf("abro\n");
		      glPushMatrix();
				}
				if(i==11){
					printf("->%d<-",i);
					glTranslatef(joins[newRoot].pos.x*(-1.0),joins[newRoot].pos.y*(-1.0), joins[newRoot].pos.z*(-1.0));
		    	//rotate(joins[i].angle);
		    	
		    	glRotatef(45.0f,0,0,1);
		    	glTranslatef(joins[newRoot].pos.x,joins[newRoot].pos.y, joins[newRoot].pos.z);
		    }
		    glBegin(GL_POINTS);
		    	glVertex3f(joins[i].pos.x,joins[i].pos.y, joins[i].pos.z);
		    glEnd();
		    if(i>0){
					glBegin(GL_LINES);
						glVertex3f(joins[i].pos.x,joins[i].pos.y, joins[i].pos.z);
						int r=joins[i].root;
						glVertex3f(joins[r].pos.x,joins[r].pos.y, joins[r].pos.z);
				  glEnd();
		    }
		    if(newRoot!=currentRoot){
		      glPopMatrix();
		      printf("cierro\n");
		      currentRoot=newRoot;
				}
			}
			printf("cierro---------\n");
		glPopMatrix();*/
		glLoadIdentity();
	glPushMatrix();
		punto(ROOT);
		
		//cuello
		glPushMatrix();
			glRotatef(20.0f,0,0,1);
			punto(CUELLO);
			linea(CUELLO);
			//hombroDer
			glPushMatrix();
				//
				//glTranslatef(joins[CUELLO].pos.x,joins[CUELLO].pos.y, joins[CUELLO].pos.z);
				punto(HOMBRO_DER);
				linea(HOMBRO_DER);
				glPushMatrix();
				        glTranslatef(joins[HOMBRO_DER].pos.x,joins[HOMBRO_DER].pos.y, joins[HOMBRO_DER].pos.z);
								glRotatef(-45.0f,0,0,1);
								glTranslatef(-joins[HOMBRO_DER].pos.x,-joins[HOMBRO_DER].pos.y, -joins[HOMBRO_DER].pos.z);
					punto(MANO_DER);
					linea(MANO_DER);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		//cintura
		glPushMatrix();
			punto(CINTURA);
			linea(CINTURA);
		glPopMatrix();
	glPopMatrix();
    
    
		glutSwapBuffers();
		glFinish();
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
	GLdouble eyeX=0;
	GLdouble eyeY=0;
	GLdouble eyeZ=-200.0f;
	GLdouble centerX=0;
	GLdouble centerY=0;
	GLdouble centerZ=0;
	GLdouble upX=0;
	GLdouble upY=1.0f;
	GLdouble upZ=0;
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	//glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -50.0, 50.0);
}
void myKeyboard(unsigned char key,int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
	}
}

int main(int argcp, char **argv){
  init();

  glutInit(&argcp,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(hsize,hsize);
	glutCreateWindow("Esqueleto");
	glutDisplayFunc(DibujaEscena);
	glutReshapeFunc(EscalaVentana);
	glutKeyboardFunc(myKeyboard);
	/*glutIdleFunc(MueveCuadrado);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(myKeyboardSpecial);
	glutMouseFunc(myMouseClick);
	glutMotionFunc(myMotion);*/
	glutMainLoop();
}
