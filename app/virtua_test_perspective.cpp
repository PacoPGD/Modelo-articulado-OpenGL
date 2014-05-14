#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>




GLfloat lightPos[4] = {0.0, 5.8 ,0.0, 1.0};  ////posicion de la luz
////////
GLfloat luzAmbient[4] = {0.0,0.0,0.0,1.0};
GLfloat luzDiff[4] = {1.0, 1.0, 1.0,1.0};
GLfloat luzSpec[4] = {1.0, 1.0, 1.0,1.0};
///////



////////
GLfloat matAmbient[4] = {0.11,0.06,0.11,1.0};
GLfloat matDiff[4] = {0.42, 0.0, 0.79,1.0};
GLfloat matSpec[4] = {0.33, 0.33, 0.52,1.0};
GLfloat matEmision[4] = {0.0,0.0,0.0,0.0};
GLint shininess=128;
///////






void init(){

glEnable(GL_DEPTH_TEST);


}

void cambiarTamano(int largo, int ancho) {   // esta funcion resive los parametros largo y ancho del callback que lo llamo  (glutReshapeFunc)
        if(ancho==0) ancho=1;           // Previene que dividamos por 0
       
       
       
       
       
////////////////// Afectaciones de vistas o tomas de perspectiva
        glMatrixMode(GL_PROJECTION);    // Escojemos la matriz de proyeccion
        glLoadIdentity();               // Se resetea la matriz
        glViewport(0,0,largo, ancho);   // Se va a usar toda la ventana para mostrar graficos
        
        

        /*
        gluPerspective( 60 ,           
                        (float)largo/(float)ancho,  
                        1,             
                        100);      
          */              

	glFrustum(-5, 5, -5, 5, 1, 10);

                                   
       
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
     glLoadIdentity();	/* clear the matrix */
     gluLookAt (10.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /* viewing transformation  */

     glScalef (1.0, 1.0, 1.0);      /* modeling transformation */ 
             
     axis(10.0); 
     glutWireTeapot(8.0);
	 
     glFlush();
}





int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);        
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
        glutCreateWindow("The teapot");

        init(); 
        glutDisplayFunc(dibujar);           

	
        glutReshapeFunc(cambiarTamano);  //caso para saber que hace cuando la ventana es explícitamente reescalada. Esta acción afecta en principio directamente al render, puesto que se está cambiando el tamaño del plano de proyección
        
  

        
        glutMainLoop();
        return 0;
}
