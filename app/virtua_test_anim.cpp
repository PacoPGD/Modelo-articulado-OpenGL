#include <GL/glut.h>
#include "obj.h"
#include <math.h>
#include <stdlib.h>

using namespace virtua::objects::formats;

OBJ object;
int rotate=0;



void init(){

glEnable(GL_DEPTH_TEST);

//object.load("box.obj");
object.load("models/virus.obj");
object.enableColor(true);

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
                        10);      
                        

                   
	    
                   
                  
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
	 gluLookAt(0.0, 0.0, 5,       
                   0.0, 0.0, 0.0,    
        0.0, 1.0, 0.0);  
	 
    axis(5.0);
	// glScalef(0.001,0.001,0.001);
    glRotatef((float)rotate,1,0,0);
    rotate=(rotate+10)%360;
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
        glutCreateWindow("OBJ 3D");

	
        init(); 
	glutIdleFunc(vIdle);
        glutDisplayFunc(dibujar);           
        
        glutReshapeFunc(cambiarTamano);  //caso para saber que hace cuando la ventana es explícitamente reescalada. Esta acción afecta en principio directamente al render, puesto que se está cambiando el tamaño del plano de proyección
        
  

        
        glutMainLoop();
        return 0;
}
