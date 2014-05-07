


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
    angle=rot;
 	}
};


class Esqueleto{
public:
	std::vector<Join> joins;
	
	Esqueleto(){}
	
	void init(){
		Vector3f pos(0,0,0);
		Vector3f topLimit(0,0,0);
		Vector3f botLimit(0,0,0);
		
		//0
		Join j(ROOT,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//1
		pos.set(0,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(TORSO,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//2
		pos.set(0,40,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CUELLO,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//3
		pos.set(0,-20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CINTURA,ROOT,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//4
		pos.set(0,60,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CABEZA,CUELLO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//5
		pos.set(20,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(HOMBRO_DER,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
	 	//6
		pos.set(-20,20,0);
		topLimit.set(0,0,0);
		j.set(HOMBRO_IZQ,TORSO,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//7
		pos.set(20,-20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CADERA_DER,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//8
		pos.set(-20,-20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CADERA_IZQ,CINTURA,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//9
		pos.set(40,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CODO_DER,HOMBRO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//10
		pos.set(-40,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(CODO_IZQ,HOMBRO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//11
		pos.set(60,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(MUNECA_DER,CODO_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//12
		pos.set(-60,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(MUNECA_IZQ,CODO_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//13
		pos.set(80,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(MANO_DER,MUNECA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//14
		pos.set(-80,20,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(MANO_IZQ,MUNECA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//15
		pos.set(20,-40,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(RODILLA_DER,CADERA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//16
		/*******************************/
		// Rotando
		/*******************************/
		Vector3f rot(0,0,45);
		j.rotate(rot);
		pos.set(-20,-40,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(RODILLA_IZQ,CADERA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		j.rotate(Vector3f(0,0,0));
		
		//17
		pos.set(20,-60,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(TALON_DER,RODILLA_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//18
		pos.set(-20,-60,0);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(TALON_IZQ,RODILLA_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//19
		pos.set(20,-60,-20);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(PIE_DER,TALON_DER,pos,topLimit,botLimit);
		joins.push_back(j);
		
		//20
		pos.set(-20,-60,-20);
		topLimit.set(0,0,0);
		botLimit.set(0,0,0);
		j.set(PIE_IZQ,TALON_IZQ,pos,topLimit,botLimit);
		joins.push_back(j);
	}


	void rotate(int id){
		Join j=joins[id];
		int root=j.root;
		glTranslatef(joins[root].pos.x,joins[root].pos.y, joins[root].pos.z);
		//glRotatef(-45.0f,0,0,1);
		if(j.angle.x>0){	glRotatef(j.angle.x,1,0,0);}
		if(j.angle.y>0){	glRotatef(j.angle.y,0,1,0);}
		if(j.angle.z>0){	glRotatef(j.angle.z,0,0,1);}
		glTranslatef(-joins[root].pos.x,-joins[root].pos.y, -joins[root].pos.z);
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
	
	void dibujar(){
glMatrixMode(GL_MODELVIEW);
  glColor3f(1,0,0);
  glPointSize(10.0f);
glLoadIdentity();
glPushMatrix();
	punto(ROOT);
	//Torso
	glPushMatrix();
		glRotatef(20.0f,0,0,1);
		punto(TORSO);
		linea(TORSO);
		//cuello
		glPushMatrix();
			punto(CUELLO);
			linea(CUELLO);
			//cabeza
			glPushMatrix();
				punto(CABEZA);
				linea(CABEZA);
			glPopMatrix();
		glPopMatrix();
		//hombroDer
		glPushMatrix();
			punto(HOMBRO_DER);
			linea(HOMBRO_DER);
			//codoDer
			glPushMatrix();
        glTranslatef(joins[HOMBRO_DER].pos.x,joins[HOMBRO_DER].pos.y, joins[HOMBRO_DER].pos.z);
				glRotatef(-45.0f,0,0,1);
				glTranslatef(-joins[HOMBRO_DER].pos.x,-joins[HOMBRO_DER].pos.y, -joins[HOMBRO_DER].pos.z);
				punto(CODO_DER);
				linea(CODO_DER);
				//munecaDer
				glPushMatrix();
					punto(MUNECA_DER);
					linea(MUNECA_DER);
					//manoDer
					glPushMatrix();
						punto(MANO_DER);
						linea(MANO_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			//hombroIzq
			glPushMatrix();
			punto(HOMBRO_IZQ);
			linea(HOMBRO_IZQ);
				//codoIzq
				glPushMatrix();
					punto(CODO_IZQ);
					linea(CODO_IZQ);
					//munecaIzq
					glPushMatrix();
						punto(MUNECA_IZQ);
						linea(MUNECA_IZQ);
						//manoIzq
						glPushMatrix();
							punto(MANO_IZQ);
							linea(MANO_IZQ);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//cintura
	glPushMatrix();
		punto(CINTURA);
		linea(CINTURA);
		//caderaDer
		glPushMatrix();
			punto(CADERA_DER);
			linea(CADERA_DER);
			//rodillaDer
			glPushMatrix();
				punto(RODILLA_DER);
				linea(RODILLA_DER);
				//talonDer
				glPushMatrix();
					punto(TALON_DER);
					linea(TALON_DER);
					//pieDer
					glPushMatrix();
						punto(PIE_DER);
						linea(PIE_DER);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//caderaIzq
		glPushMatrix();
			punto(CADERA_IZQ);
			linea(CADERA_IZQ);
			//rodillaIzq
			glPushMatrix();
				punto(RODILLA_IZQ);
				linea(RODILLA_IZQ);
				//talonIzq
				glPushMatrix();
					punto(TALON_IZQ);
					linea(TALON_IZQ);
					//pideIzq
					glPushMatrix();
						punto(PIE_IZQ);
						linea(PIE_IZQ);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
	}
};
