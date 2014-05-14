#include "vobject.h"

namespace virtua{  
  
namespace objects{
  
  /**
    */
  VObject::VObject(){
    _name="";
    _drawBB=false;
    _drawAABB=false;
  }
  /** Releases the memory
    */
  VObject::~VObject(){}
  /**
    */
  void VObject::setName(string name){
    _name=name;
  }
  /**
    */
  void VObject::applyTransformMatrix(Matrix3D MT){
    _matrix3d=MT*_matrix3d;
    _d.applyScaleFactor(MT.getScaleX(),MT.getScaleY(),MT.getScaleZ());
  }
  Matrix3D VObject::getTransformMatrix(){
    return _matrix3d;
  }
   /**
    */
  string VObject::getName(){
    return _name;
  }
  /**
    */
  Dimension VObject::getDimension(){
    return _d;
  }
  /**
  */
  string VObject::getClassName(){
	return typeid(*this).name();
  }
  /**
  */
  Point3D<float> VObject::getBBMin(){
      return _bmin;
  }
  /**
  */
  Point3D<float> VObject::getBBMax(){
    return _bmax;
  }
  /**
  */
  Point3D<float>* VObject::getBB(){
    return _bb;
  }
  /**
  */
  void VObject::drawBoundingBoxGL(){
      GLfloat color[4];	
      glGetFloatv(GL_CURRENT_COLOR,color);
	
    if(_drawBB){
    glColor3f(1,1,1);
    drawBox(_bb);
    }
    if(_drawAABB){
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,0,0);
    drawBox(_drawn_bb);
    glPopMatrix();
    }
      glColor4fv(color);
  }
  /**
   */
  void VObject::drawBox(Point3D<float>* box){
    glBegin(GL_LINE_LOOP);						
    glVertex3f(box[0].xyzh[0], box[0].xyzh[1], box[0].xyzh[2]);			
    glVertex3f(box[1].xyzh[0], box[1].xyzh[1], box[1].xyzh[2]);
    glVertex3f(box[2].xyzh[0], box[2].xyzh[1], box[2].xyzh[2]);
    glVertex3f(box[3].xyzh[0], box[3].xyzh[1], box[3].xyzh[2]);
    glEnd();
    glBegin(GL_LINE_LOOP);						
    glVertex3f(box[4].xyzh[0], box[4].xyzh[1], box[4].xyzh[2]);			
    glVertex3f(box[5].xyzh[0], box[5].xyzh[1], box[5].xyzh[2]);
    glVertex3f(box[6].xyzh[0], box[6].xyzh[1], box[6].xyzh[2]);
    glVertex3f(box[7].xyzh[0], box[7].xyzh[1], box[7].xyzh[2]);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(box[0].xyzh[0], box[0].xyzh[1], box[0].xyzh[2]);			
    glVertex3f(box[4].xyzh[0], box[4].xyzh[1], box[4].xyzh[2]);			
    glVertex3f(box[1].xyzh[0], box[1].xyzh[1], box[1].xyzh[2]);
    glVertex3f(box[5].xyzh[0], box[5].xyzh[1], box[5].xyzh[2]);
    glVertex3f(box[2].xyzh[0], box[2].xyzh[1], box[2].xyzh[2]);
    glVertex3f(box[6].xyzh[0], box[6].xyzh[1], box[6].xyzh[2]);
    glVertex3f(box[3].xyzh[0], box[3].xyzh[1], box[3].xyzh[2]);
    glVertex3f(box[7].xyzh[0], box[7].xyzh[1], box[7].xyzh[2]);
    glEnd();
   
  }
  /**
   */
  void VObject::enableBoundingBox(){
    _drawBB=true;
  }
  /**
   */
  void VObject::disableBoundingBox(){
    _drawBB=false;
  }
  /**
   */
  void VObject::enableAxisAlignedBoundingBox(){
    _drawAABB=true;
  }
  /**
   */
  void VObject::disableAxisAlignedBoundingBox(){
    _drawAABB=false;
  }
  /**
  */
  void VObject::initBB(){
    buildAxisAlignedBB(_bmin,_bmax,_bb);
  }
  /**
   */
  void VObject::updateBB(){
	glPushMatrix();
	GLfloat model[16];
	
	glGetFloatv(GL_MODELVIEW_MATRIX, model);
	
	Matrix3D _current_modelview;
	_current_modelview.setMatrixCMO(model);
	Matrix3D  new_modelview=_current_modelview*_matrix3d;
	for(int i=0;i<8;i++)
	_drawn_bb[i]=_bb[i];
	new_modelview.transform(_drawn_bb,8);
	Point3D<float> drawn_bb_min=_drawn_bb[0];
	Point3D<float> drawn_bb_max=_drawn_bb[0];
	for(int i=1;i<8;i++){
	  if(_drawn_bb[i].xyzh[0]<drawn_bb_min.xyzh[0])
	    drawn_bb_min.xyzh[0]=_drawn_bb[i].xyzh[0];
	  if(_drawn_bb[i].xyzh[1]<drawn_bb_min.xyzh[1])
	    drawn_bb_min.xyzh[1]=_drawn_bb[i].xyzh[1];
	  if(_drawn_bb[i].xyzh[2]<drawn_bb_min.xyzh[2])
	    drawn_bb_min.xyzh[2]=_drawn_bb[i].xyzh[2];
	  if(_drawn_bb[i].xyzh[0]>drawn_bb_max.xyzh[0])
	    drawn_bb_max.xyzh[0]=_drawn_bb[i].xyzh[0];
	  if(_drawn_bb[i].xyzh[1]>drawn_bb_max.xyzh[1])
	    drawn_bb_max.xyzh[1]=_drawn_bb[i].xyzh[1];
	  if(_drawn_bb[i].xyzh[2]>drawn_bb_max.xyzh[2])
	    drawn_bb_max.xyzh[2]=_drawn_bb[i].xyzh[2];
	}
	buildAxisAlignedBB(drawn_bb_min,drawn_bb_max,_drawn_bb);
	glPopMatrix();
  }
  /**
   */
  void VObject::buildAxisAlignedBB(Point3D<float> bmin, Point3D<float> bmax, Point3D<float>* bb){
    	bb[0]=bmin;
	bb[1]=bmin;
	bb[1].xyzh[0]=bmax.xyzh[0];
	bb[2]=bb[1];
	bb[2].xyzh[2]=bmax.xyzh[2];
	bb[3]=bb[2];
	bb[3].xyzh[0]=bmin.xyzh[0];
	bb[4]=bmin;
	bb[4].xyzh[1]=bmax.xyzh[1];
	bb[5]=bb[4];
	bb[5].xyzh[0]=bmax.xyzh[0];
	bb[6]=bmax;
	bb[7]=bb[6];
	bb[7].xyzh[0]=bmin.xyzh[0];
  }
  /**
   */
  Point3D<float> VObject::getAABBMin(){
	return _drawn_bb[0];
  }
  /**
   */
  Point3D<float> VObject::getAABBMax(){
	return _drawn_bb[6];
  }
}

}
