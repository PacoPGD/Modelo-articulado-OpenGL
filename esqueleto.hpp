#define ROOT 0
#define TORSO 1
#define CUELLO 2
#define CINTURA 3
#define CABEZA 4
#define HOMBRO_DER 5
#define HOMBRO_IZQ 6
#define CADERA_DER 7
#define CADERA_IZQ 8
#define CODO_DER 9
#define CODO_IZQ 10
#define MUNECA_DER 11
#define MUNECA_IZQ 12
#define MANO_DER 13
#define MANO_IZQ 14
#define RODILLA_DER 15
#define RODILLA_IZQ 16
#define TALON_DER 17
#define TALON_IZQ 18
#define PIE_DER 19
#define PIE_IZQ 20


#include "glm.cpp"

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

  void devuelveMayor(Vector3f vectorA, Vector3f vectorB){
		if(vectorA.x>=vectorB.x)
			x=vectorA.x;
		else
			x=vectorB.x;

		if(vectorA.y>=vectorB.y)
			y=vectorA.y;
		else
			y=vectorB.y;

		if(vectorA.z>=vectorB.z)
			z=vectorA.z;
		else
			z=vectorB.z;
  }
	

  void devuelveMenor(Vector3f vectorA, Vector3f vectorB){
		if(vectorA.x<=vectorB.x)
			x=vectorA.x;
		else
			x=vectorB.x;

		if(vectorA.y<=vectorB.y)
			y=vectorA.y;
		else
			y=vectorB.y;

		if(vectorA.z<=vectorB.z)
			z=vectorA.z;
		else
			z=vectorB.z;
  }

};

class Join{
public:
	int id;
	int root;
	Vector3f topLimit;
	Vector3f botLimit;
	Vector3f angle;
	Vector3f pos;
	
	Join(){
    id=0;
    root=0;
	}
	
	Join(int id2, int root2, Vector3f pos2, Vector3f topLimit2, Vector3f botLimit2){
    id=id2;
    root=root2;
    pos=pos2;
    topLimit=topLimit2;
    botLimit=botLimit2;
    angle=Vector3f(0,0,0);
 	}
 	
 	void set(int id2, int root2, Vector3f pos2, Vector3f topLimit2, Vector3f botLimit2){
    id=id2;
    root=root2;
    pos=pos2;
    topLimit=topLimit2;
    botLimit=botLimit2;
 	}
 	
 	void rotate(Vector3f rot){
	 Vector3f rotacion;
	 rotacion.devuelveMenor(topLimit,rot);
	 rotacion.devuelveMayor(botLimit,rotacion);
    angle=rotacion;

	 printf("AngleX=%f AngleY=%f AngleZ=%f\n",angle.x,angle.y,angle.z);
 	}
};


class Esqueleto{
public:
	std::vector<Join> joins;
	Vector3f globalPos;
	int joinSelect;

	GLMmodel* model;

	Esqueleto(){
		joinSelect=0;
	}
	
	void init(){
		char modelFile[] = "Cybermen/Cyberman.obj";
		model = (GLMmodel*)malloc(sizeof(GLMmodel));
		model = glmReadOBJ(modelFile);
	
		poseReposo();

		
		
		asignarPuntos();
	}
	
	void poseReposo(){
		Vector3f pos(0,40,10);
		Vector3f topLimit(360,360,360);
		Vector3f botLimit(-360,-360,-360);
		
		//0
		Join j(ROOT,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//1
		pos.set(0,55,10);
		topLimit.set(0,90,40);
		botLimit.set(-0,-90,-40);
		j.set(TORSO,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		
		//2
		pos.set(0,60,10);
		topLimit.set(20,0,30);
		botLimit.set(-60,-0,-30);
		j.set(CUELLO,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);

	
		//3
		pos.set(0,10,10);
		topLimit.set(30,20,10);
		botLimit.set(-30,-20,-10);
		j.set(CINTURA,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//4
		pos.set(0,85,10);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(CABEZA,CUELLO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//5
		pos.set(20,50,10);
		topLimit.set(150,120,80);
		botLimit.set(-90,-60,-90);
		j.set(HOMBRO_DER,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
	 	//6
		pos.set(-20,50,10);
		topLimit.set(90,60,80);
		botLimit.set(-150,-120,-90);
		j.set(HOMBRO_IZQ,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//7
		pos.set(12,10,10);
		topLimit.set(50,10,0);
		botLimit.set(-30,-10,-0);
		j.set(CADERA_DER,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//8
		pos.set(-14,10,10);
		topLimit.set(50,10,0);
		botLimit.set(-30,-10,-0);
		j.set(CADERA_IZQ,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//9
		pos.set(30,30,10);
		topLimit.set(0,0,140);
		botLimit.set(-0,-0,-0);
		j.set(CODO_DER,HOMBRO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//10
		pos.set(-30,30,10);
		topLimit.set(0,0,140);
		botLimit.set(-0,-0,-0);
		j.set(CODO_IZQ,HOMBRO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//11
		pos.set(40,10,10);
		topLimit.set(360,30,50);
		botLimit.set(-360,-30,-50);
		j.set(MUNECA_DER,CODO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//12
		pos.set(-40,10,10);
		topLimit.set(360,30,50);
		botLimit.set(-360,-30,-50);
		j.set(MUNECA_IZQ,CODO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);

		//13
		pos.set(46,-5,10);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(MANO_DER,MUNECA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//14
		pos.set(-46,-5,10);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(MANO_IZQ,MUNECA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//15
		pos.set(12,-20,10);
		topLimit.set(0,0,0);
		botLimit.set(-60,-0,-0);
		j.set(RODILLA_DER,CADERA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//16
		pos.set(-14,-20,10);
		topLimit.set(0,0,0);
		botLimit.set(-60,-0,-0);
		j.set(RODILLA_IZQ,CADERA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//17
		pos.set(12,-65,10);
		topLimit.set(0,0,0);
		botLimit.set(-0,-0,-0);
		j.set(TALON_DER,RODILLA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//18
		pos.set(-14,-65,10);
		topLimit.set(0,0,0);
		botLimit.set(-0,-0,-0);
		j.set(TALON_IZQ,RODILLA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//19
		pos.set(12,-70,-15);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(PIE_DER,TALON_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//20
		pos.set(-12,-70,-15);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(PIE_IZQ,TALON_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
	}


	void asignarPuntos(){
	
	}


	void rotate(int id){
		Join j=joins[id];
	
		glTranslatef(joins[id].pos.x,joins[id].pos.y, joins[id].pos.z);

		glRotatef(j.angle.x,1,0,0);
		glRotatef(j.angle.y,0,1,0);
		glRotatef(j.angle.z,0,0,1);

		glTranslatef(-joins[id].pos.x, -joins[id].pos.y, -joins[id].pos.z);
	}


	void punto(int j){
		glBegin(GL_POINTS);
			if(j==joinSelect)
				glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
			glColor3f(1.0f,0.0f,0.0f);
		glEnd();
	}

	void linea(int j){
		glBegin(GL_LINES);
			glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
			int r=joins[j].root;
			glVertex3f(joins[r].pos.x,joins[r].pos.y, joins[r].pos.z);
		glEnd();
	}
	
	void dibujarVertices(int id){
		//aqui solo se deben de dibujar los vertices asignados a cada punto
		//temporalmente se dibuja todo el modelo para facilitar ajustar el 
		//esqueleto
		static GLuint i;
		static GLMgroup* group;
		static GLMtriangle* triangle;
		static GLMmaterial* material;
		if(id==100){
				group = model->groups;
		  glBegin(GL_TRIANGLES);
				for (i = 0; i < group->numtriangles; i++) {
				  triangle = &T(group->triangles[i]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[0]]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[1]]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[2]]);
				}
		  glEnd();
    }
	}	

	void move(float x, float y, float z){
		globalPos.x=x;
		globalPos.y=y;
		globalPos.z=z;
	}
	
	


	void dibujar(){
		glMatrixMode(GL_MODELVIEW);
		
	
		glColor3f(0.5f,0.5f,0.5f);
		glLoadIdentity();
		glScalef(0.8f,0.8f,0.8f);
		glTranslatef(0.0f,-90.0f,0.0f);
		glRotatef(180.0f,0,1,0);
		//glmDraw(model, GLM_SMOOTH/*GLM_FLAT*/);	
		dibujarVertices(100);


  glColor3f(1,0,0);
  glPointSize(10.0f);
glLoadIdentity();
glPushMatrix();
	glTranslatef(globalPos.x,globalPos.y,globalPos.z);
	punto(ROOT);
	rotate(ROOT);
	//Torso
	glPushMatrix();
		dibujarVertices(TORSO);
		punto(TORSO);
		linea(TORSO);
		rotate(TORSO);
		//cuello
		glPushMatrix();
			dibujarVertices(CUELLO);
			punto(CUELLO);
			linea(CUELLO);
			rotate(CUELLO);
			//cabeza
			glPushMatrix();
				dibujarVertices(CABEZA);
				punto(CABEZA);
				linea(CABEZA);
				rotate(CABEZA);
			glPopMatrix();
		glPopMatrix();
		//hombroDer
		glPushMatrix();
			dibujarVertices(HOMBRO_DER);
			punto(HOMBRO_DER);
			linea(HOMBRO_DER);
			rotate(HOMBRO_DER);
			//codoDer
			glPushMatrix();
				dibujarVertices(CODO_DER);
				punto(CODO_DER);
				linea(CODO_DER);
				rotate(CODO_DER);
				//munecaDer
				glPushMatrix();
					dibujarVertices(MUNECA_DER);
					punto(MUNECA_DER);
					linea(MUNECA_DER);
					rotate(MUNECA_DER);
					//manoDer
					glPushMatrix();
						dibujarVertices(MANO_DER);
						punto(MANO_DER);
						linea(MANO_DER);
						rotate(MANO_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//hombroIzq
		glPushMatrix();
			dibujarVertices(HOMBRO_IZQ);
			punto(HOMBRO_IZQ);
			linea(HOMBRO_IZQ);
			rotate(HOMBRO_IZQ);
			//codoIzq
			glPushMatrix();
				dibujarVertices(CODO_IZQ);
				punto(CODO_IZQ);
				linea(CODO_IZQ);
				rotate(CODO_IZQ);
				//munecaIzq
				glPushMatrix();
					dibujarVertices(MUNECA_IZQ);
					punto(MUNECA_IZQ);
					linea(MUNECA_IZQ);
					rotate(MUNECA_IZQ);
					//manoIzq
					glPushMatrix();
						dibujarVertices(MANO_IZQ);
						punto(MANO_IZQ);
						linea(MANO_IZQ);
						rotate(MANO_IZQ);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//cintura
	glPushMatrix();
		dibujarVertices(CINTURA);
		punto(CINTURA);
		linea(CINTURA);
		rotate(CINTURA);
		//caderaDer
		glPushMatrix();
			dibujarVertices(CADERA_DER);
			punto(CADERA_DER);
			linea(CADERA_DER);
			rotate(CADERA_DER);
			//rodillaDer
			glPushMatrix();
				dibujarVertices(RODILLA_DER);
				punto(RODILLA_DER);
				linea(RODILLA_DER);
				rotate(RODILLA_DER);
				//talonDer
				glPushMatrix();
					dibujarVertices(TALON_DER);
					punto(TALON_DER);
					linea(TALON_DER);
					rotate(TALON_DER);
					//pieDer
					glPushMatrix();
						dibujarVertices(PIE_DER);
						punto(PIE_DER);
						linea(PIE_DER);
						rotate(PIE_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//caderaIzq
		glPushMatrix();
			dibujarVertices(CADERA_IZQ);
			punto(CADERA_IZQ);
			linea(CADERA_IZQ);
			rotate(CADERA_IZQ);
			//rodillaIzq
			glPushMatrix();
				dibujarVertices(RODILLA_IZQ);
				punto(RODILLA_IZQ);
				linea(RODILLA_IZQ);
				rotate(RODILLA_IZQ);
				//talonIzq
				glPushMatrix();
					dibujarVertices(TALON_IZQ);
					punto(TALON_IZQ);
					linea(TALON_IZQ);
					rotate(TALON_IZQ);
					//pideIzq
					glPushMatrix();
						dibujarVertices(PIE_IZQ);
						punto(PIE_IZQ);
						linea(PIE_IZQ);
						rotate(PIE_IZQ);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
	}
};
