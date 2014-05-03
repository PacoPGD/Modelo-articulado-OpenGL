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
  /******************************/
  //Rotando codo  
  /*******************************/
  Vector3f rot(45,45,45);
  j.rotate(rot);
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
  
  pos.set(-20,-40,0);
  limit.set(0,0,0);
  j.set(11,7,pos,limit);
  joins.push_back(j);
  
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

void dibujarEje(){
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(100.0f,0.0f,0.0f);
  
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,100.0f,0.0f);
  
  glColor3f(0.0f,0.0f,1.0f);
  glVertex3f(0.0f,0.0f,0.0f);
  glVertex3f(0.0f,0.0f,100.0f);
}

void DibujaEscena(){
		glClearColor(1.,1.,1.,1.);
		glClear(GL_COLOR_BUFFER_BIT);
		int currentRoot=0;

    glMatrixMode(GL_MODELVIEW);
    glColor3f(1,0,0);
    glLoadIdentity();
    glPushMatrix();
    glScalef(5.0f,1.0f,1.0f);
    
    glRotatef(45.0f,0,0,1);
    glTranslatef(10.0f,0,0);
    
    glutWireCube(10.0);
    glPopMatrix();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glPushMatrix();
			for(size_t i=0; i<joins.size(); ++i){
				int newRoot=joins[i].root;
				if(newRoot!=currentRoot){
		      glPushMatrix();
				}
				//glTranslatef(0,0,0);
		    //glRotatef(45, 0, 0,1.0f);
		    //glTranslatef(0,0,0);
		    glVertex3f(joins[i].pos.x,joins[i].pos.y, joins[i].pos.z);
		    if(newRoot!=currentRoot){
		      glPopMatrix();
		      currentRoot=newRoot;
				}
			}
		glPopMatrix();
    glEnd();
    
    glBegin(GL_LINES);
			for(size_t i=1; i<joins.size(); ++i){
		    glVertex3f(joins[i].pos.x,joins[i].pos.y, joins[i].pos.z);
		    int r=joins[i].root;
		    glVertex3f(joins[r].pos.x,joins[r].pos.y, joins[r].pos.z);
			}
    glEnd();
    
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
