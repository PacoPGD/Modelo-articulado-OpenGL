#include <GL/glut.h>
#include "3ds.h"
#include "matrix3d.h"
#include <math.h>
#include <stdlib.h>

using namespace virtua::objects::formats;
using namespace virtua::math;


DS3 object;
int rotate=180;

GLfloat lightPos[4] = {0.0, 5.8 ,0.0, 1.0};  ////posicion de la luz
////////
GLfloat luzAmbient[4] = {0.0,0.0,0.0,1.0};
GLfloat luzDiff[4] = {1.0, 1.0, 1.0,1.0};
GLfloat luzSpec[4] = {1.0, 1.0, 1.0,1.0};
///////



void init(){

glEnable(GL_DEPTH_TEST);
//glEnable(GL_LIGHTING);
//glEnable(GL_LIGHT0);

object.load("goku.3ds");
//object.load("game_buggy.3DS");
//object.load("3DS.3ds");

}

void luz(){
     	        ///luces del modelo
     	        
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDiff);
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzSpec);
        
     }




void cambiarTamano(int largo, int ancho) {   // esta funcion resive los parametros largo y ancho del callback que lo llamo  (glutReshapeFunc)
        if(ancho==0) ancho=1;           // Previene que dividamos por 0
       
       
       
       
       
////////////////// Afectaciones de vistas o tomas de perspectiva
        glMatrixMode(GL_PROJECTION);    // Escojemos la matriz de proyeccion
        glLoadIdentity();               // Se resetea la matriz
        glViewport(0,0,largo, ancho);   // Se va a usar toda la ventana para mostrar graficos
        
        

        
        gluPerspective( 60 ,           
                        (float)largo/(float)ancho,  
                        1,             
                        100);      
                        

                                   
       
                   
                  
}

/************************************
 *
 *
 *
 *
 ************************************/
void axis(float size)
{
    glColor3f (1,0,0 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f(size,0.0f, 0.0f); // ending point of the line
    glEnd( );

    glColor3f ( 0,1,0 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f( 0.0f,size, 0.0f); // ending point of the line
    glEnd( );


    glColor3f (0,0,1 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f(0.0f, 0.0f, size); // ending point of the line
    glEnd( );


}

void dibujar() {
     
     glClearColor (0.0,0.0,0.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
     glMatrixMode(GL_MODELVIEW);    
     glLoadIdentity();
	    
     gluLookAt(0.0, 5.0, 0,       
                   0.0, 0.0, 0.0,    
        0.0, 0.0, 1.0); 
	
	 
     //luz();
   
     axis(5.0);

     glRotatef((float)rotate,0,0,1);
     //rotate=(rotate+1)%360;
     //glScalef(0.05,0.05,0.05);
     glScalef(0.1,0.1,0.1);
     //object.enableBoundingBox();
     object.draw();
     
    
     glutSwapBuffers();
}

void vIdle() {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);        
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Goku");

        init(); 
        glutDisplayFunc(dibujar);
	glutIdleFunc(vIdle);

        glutReshapeFunc(cambiarTamano);  //caso para saber que hace cuando la ventana es explícitamente reescalada. Esta acción afecta en principio directamente al render, puesto que se está cambiando el tamaño del plano de proyección
        
  

        
        glutMainLoop();
        return 0;
}
