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


#include <math.h>

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
	std::vector<std::vector<int> > asignacion;
	GLMmodel* model;

	Esqueleto(){
		joinSelect=0;
	}
	
	void init(){
		char modelFile[] = "Cybermen/Cyberman.obj";
		model = (GLMmodel*)malloc(sizeof(GLMmodel));
		model = glmReadOBJ(modelFile);
		
		poseReposo();
		
		asignacion.resize(joins.size());
		
		asignarPuntos();
		
	}
	
	void poseReposo(){
		joins.clear();
	
		Vector3f pos(1,140,-12);
		Vector3f topLimit(360,360,360);
		Vector3f botLimit(-360,-360,-360);
		
		//0
		Join j(ROOT,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//1
		pos.set(1,155,-12);
		topLimit.set(0,90,40);
		botLimit.set(-0,-90,-40);
		j.set(TORSO,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		
		//2
		pos.set(1,170,-12);
		topLimit.set(20,0,30);
		botLimit.set(-60,-0,-30);
		j.set(CUELLO,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);

	
		//3
		pos.set(1,100,-12);
		topLimit.set(30,20,10);
		botLimit.set(-30,-20,-10);
		j.set(CINTURA,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//4
		pos.set(1,185,-12);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(CABEZA,CUELLO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//5
		pos.set(28,150,-12);
		topLimit.set(90,120,80);
		botLimit.set(-150,-60,-90);
		j.set(HOMBRO_DER,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
	 	//6
		pos.set(-26,150,-12);
		topLimit.set(90,120,80);
		botLimit.set(-150,-60,-90);
		j.set(HOMBRO_IZQ,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//7
		pos.set(15,100,-12);
		topLimit.set(50,10,0);
		botLimit.set(-30,-10,-0);
		j.set(CADERA_DER,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//8
		pos.set(-13,100,-12);
		topLimit.set(50,10,0);
		botLimit.set(-30,-10,-0);
		j.set(CADERA_IZQ,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//9
		pos.set(40,125,-12);
		topLimit.set(0,0,0);
		botLimit.set(-0,-0,-140);
		j.set(CODO_DER,HOMBRO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//10
		pos.set(-38,125,-12);
		topLimit.set(0,0,140);
		botLimit.set(-0,-0,0);
		j.set(CODO_IZQ,HOMBRO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//11
		pos.set(56,95,-12);
		topLimit.set(360,30,50);
		botLimit.set(-360,-30,-50);
		j.set(MUNECA_DER,CODO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//12
		pos.set(-54,95,-12);
		topLimit.set(360,30,50);
		botLimit.set(-360,-30,-50);
		j.set(MUNECA_IZQ,CODO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);

		//13
		pos.set(58,85,-12);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(MANO_DER,MUNECA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//14
		pos.set(-56,85,-12);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(MANO_IZQ,MUNECA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//15
		pos.set(15,68,-12);
		topLimit.set(60,0,0);
		botLimit.set(0,0,0);
		j.set(RODILLA_DER,CADERA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//16
		pos.set(-13,68,-12);
		topLimit.set(60,0,0);
		botLimit.set(0,0,0);
		j.set(RODILLA_IZQ,CADERA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//17
		pos.set(17,5,-12);
		topLimit.set(0,0,0);
		botLimit.set(-0,-0,-0);
		j.set(TALON_DER,RODILLA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//18
		pos.set(-14,5,-12);
		topLimit.set(0,0,0);
		botLimit.set(-0,-0,-0);
		j.set(TALON_IZQ,RODILLA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//19
		pos.set(17,5,20);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(PIE_DER,TALON_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//20
		pos.set(-14,5,20);
		topLimit.set(360,360,360);
		botLimit.set(-360,-360,-360);
		j.set(PIE_IZQ,TALON_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);

	}

  double distancia(Vector3f v,Vector3f v2){
  	return pow((v2.x-v.x),2)+pow((v2.y-v.y),2)+pow((v2.z-v.z),2);
  }

	double distanciaPuntoTriangulo(GLMtriangle *t, Vector3f p){
		Vector3f t1(model->vertices[3 * t->vindices[0]], 
								model->vertices[3 * t->vindices[0]+1], 
								model->vertices[3 * t->vindices[0]+2]);
		Vector3f t2(model->vertices[3 * t->vindices[1]], 
								model->vertices[3 * t->vindices[1]+1], 
								model->vertices[3 * t->vindices[1]+2]); 
		Vector3f t3(model->vertices[3 * t->vindices[2]], 
								model->vertices[3 * t->vindices[2]+1], 
								model->vertices[3 * t->vindices[2]+2]);  
		
		Vector3f media((t1.x+t2.x+t3.x)/3,(t1.y+t2.y+t3.y)/3,(t1.z+t2.z+t3.z)/3);
		
		return distancia(media,p);

	}

	/****************************** Asignacion de puntos */
	void asignarPuntos(){

	 	GLuint k;
	 	GLMgroup* group;
	 	GLMtriangle* triangle;
		group = model->groups;
		double min,dist;
		int indiceSelect;
		
		for (int i = 0; i < group->numtriangles; i++) {
				triangle = &T(group->triangles[i]);
				min=distanciaPuntoTriangulo(triangle,joins[0].pos);
				indiceSelect=0;
				for(int k=1;k<joins.size();k++){
					Vector3f p((joins[k].pos.x+joins[joins[k].root].pos.x)/2.0,
										(joins[k].pos.y+joins[joins[k].root].pos.y)/2.0,
										(joins[k].pos.z+joins[joins[k].root].pos.z)/2.0
										);
				  dist=distanciaPuntoTriangulo(triangle,p);
				  if(min>dist){
				  	min=dist;
				  	indiceSelect=k;
				  }
				}
				asignacion[indiceSelect].push_back(i);
		}
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
			glColor3f(1.0f,0.0f,0.0f);
			if(j==joinSelect)
				glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
		glEnd();
	}

	void linea(int j){
		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(joins[j].pos.x,joins[j].pos.y, joins[j].pos.z);
			int r=joins[j].root;
			glVertex3f(joins[r].pos.x,joins[r].pos.y, joins[r].pos.z);
		glEnd();
	}
	
	void dibujarVertices(int id){
	 	GLuint i;
	 	GLMgroup* group;
	 	GLMtriangle* triangle;
	 	group = model->groups;
	 	glPushMatrix();
	 	glColor3f(0.5f,0.5f,0.5f);

		
		glBegin(GL_TRIANGLES);
			for(int i=0;i<asignacion[id].size();i++){
					int itri=asignacion[id][i];
					triangle = &T(group->triangles[itri]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[0]]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[1]]);
					glVertex3fv(&model->vertices[3 * triangle->vindices[2]]);
			}
		glEnd();
		glPopMatrix();
	}	

	void move(float x, float y, float z){
		globalPos.x=x;
		globalPos.y=y;
		globalPos.z=z;
	}
	
	void dibujarParte(int id){
			dibujarVertices(id);
			linea(id);
			punto(id);
			rotate(id);
	}
	


	void dibujar(){
		glMatrixMode(GL_MODELVIEW);

  glColor3f(1,0,0);
  glPointSize(10.0f);
glLoadIdentity();
// pongo de cara al esqueleto
glRotatef(180.0f,0,1,0);
glPushMatrix();
	glTranslatef(globalPos.x,globalPos.y,globalPos.z);
	dibujarVertices(ROOT);
	punto(ROOT);
	rotate(ROOT);
	//Torso
	glPushMatrix();
		dibujarParte(TORSO);
		//cuello
		glPushMatrix();
			dibujarParte(CUELLO);
			//cabeza
			glPushMatrix();
				dibujarParte(CABEZA);
			glPopMatrix();
		glPopMatrix();
		//hombroDer
		glPushMatrix();
			dibujarParte(HOMBRO_DER);
			//codoDer
			glPushMatrix();
				dibujarParte(CODO_DER);
				//munecaDer
				glPushMatrix();
					dibujarParte(MUNECA_DER);
					//manoDer
					glPushMatrix();
						dibujarParte(MANO_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//hombroIzq
		glPushMatrix();
			dibujarParte(HOMBRO_IZQ);
			//codoIzq
			glPushMatrix();
				dibujarParte(CODO_IZQ);
				//munecaIzq
				glPushMatrix();
					dibujarParte(MUNECA_IZQ);
					//manoIzq
					glPushMatrix();
						dibujarParte(MANO_IZQ);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//cintura
	glPushMatrix();
		dibujarParte(CINTURA);
		//caderaDer
		glPushMatrix();
			dibujarParte(CADERA_DER);
			//rodillaDer
			glPushMatrix();
				dibujarParte(RODILLA_DER);
				//talonDer
				glPushMatrix();
					dibujarParte(TALON_DER);
					//pieDer
					glPushMatrix();
						dibujarParte(PIE_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//caderaIzq
		glPushMatrix();
			dibujarParte(CADERA_IZQ);
			//rodillaIzq
			glPushMatrix();
				dibujarParte(RODILLA_IZQ);
				//talonIzq
				glPushMatrix();
					dibujarParte(TALON_IZQ);
					//pideIzq
					glPushMatrix();
						dibujarParte(PIE_IZQ);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
	}
};
