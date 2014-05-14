#include "obj.h"

namespace virtua{
  
  namespace objects{
    
    namespace formats{
      
      /**
       */
      OBJ::OBJ(){
	_3dmodel=new GLMmodel;
	_loaded=false;
	_mat=false;
	_col=true;
	_mtl=true;
	_first=true;
      }
      /**
       */
      OBJ::~OBJ(){
	if(_loaded)
	  glmDelete(_3dmodel);
	delete _3dmodel;
      }
      /** Loads the object from the specified file.
      */
      void OBJ::load(string file) throw (VException)
      {
	if(_loaded)
	  glmDelete(_3dmodel);
	_3dmodel=glmReadOBJ((char*)file.c_str());
	if(_3dmodel==NULL)
	  throw VException("virtua::objects::formats::OBJ::load(): can't open data file.");
	GLfloat dimensions[3];
	GLfloat bmin[3];
	GLfloat bmax[3];
	glmBoundingBox(_3dmodel, dimensions,bmin,bmax);
	_d.x=dimensions[0];
	_d.y=dimensions[1];
	_d.z=dimensions[2];
	_d.t=0.0;
	_bmin.xyzh[0]=bmin[0];
	_bmin.xyzh[1]=bmin[1];
	_bmin.xyzh[2]=bmin[2];
	_bmax.xyzh[0]=bmax[0];
	_bmax.xyzh[1]=bmax[1];
	_bmax.xyzh[2]=bmax[2];
	initBB();
	_loaded=true;
      }
      /** Saves the object to the specified file.
      */
      void OBJ::save(string file){
	if(_loaded)
	  glmWriteOBJ(_3dmodel,(char*)file.c_str(),GLM_SMOOTH|GLM_TEXTURE|GLM_MATERIAL);
      }
      /**
      */
      void OBJ::draw(){
	updateBB();
	glPushMatrix();
	float m[16];
	_matrix3d.getMatrixCMO(m);
	glMultMatrixf(m);
	if((_drawBB)||(_drawAABB)){
	  drawBoundingBoxGL();
	}
	if(!_mtl){
	    glmDraw(_3dmodel, GLM_SMOOTH);
	}
	else{
	  GLfloat color[4];
	  glGetFloatv(GL_CURRENT_COLOR,color);
	   if(_col){
	     if(_first){
	       _list=glmList(_3dmodel,GLM_SMOOTH|GLM_COLOR);
	       _first=false;
	     }
	     glCallList(_list);
	      //glmDraw(_3dmodel, GLM_SMOOTH | GLM_COLOR);
	   }
	   else{
	      //glColor3f(1,1,1);
	      /*
	      glEnable(GL_TEXTURE_2D);
	      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	      */
	      if(_first){
		_list=glmList(_3dmodel,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
		_first=false;
	      }
	      glCallList(_list);
	      //glmDraw(_3dmodel, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	      //glDisable(GL_TEXTURE_2D);
	   }
	  
	  glColor4fv(color);
	  }
	glPopMatrix();
	
      }
      /**
      */
      void OBJ::enableMaterials(bool mat){
	if(mat)
	  _col=false;
	else
	  _col=true;
	_mat=mat;
      }
       /**
      */
      void OBJ::enableColor(bool col){
	if(col)
	  _mat=false;
	else
	  _mat=true;
	_col=col;
      }
       /**
      */
      void OBJ::disableMTL(bool mtl){
	if(mtl){
	  _col=false;
	  _mat=false;
	}
	else{
	  _col=true;
	  _mat=false;
	}
	_mtl=!mtl;
      }
     
    }
    
  }
  
}