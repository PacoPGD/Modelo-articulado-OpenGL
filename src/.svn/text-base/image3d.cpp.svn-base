#include "image3d.h"

namespace virtua{
  
  namespace objects{
    /**
     */
    Image3D::Image3D(){
      _img=NULL;
      _loaded=false;
      _xframe=1.0;
      _yframe=1.0;
    }
    /**
     */
    Image3D::~Image3D(){
      if(_loaded){
	cvReleaseImage(&_img);
      }
    }
    /**
     */
    void Image3D::load(string file) throw (VException){
      if(_loaded)
	cvReleaseImage(&_img);
      _img=cvLoadImage(file.c_str(),CV_LOAD_IMAGE_UNCHANGED);
      if(_img==NULL)
	  throw VException("virtua::objects::Image3D::load(): can't open data file.");
      _d.x=_xframe;
      _d.y=_yframe;
      _d.z=0.0;
      _d.t=0.0;
      _bmin.xyzh[0]=-_xframe/2.;
      _bmin.xyzh[1]=-_yframe/2.;
      _bmin.xyzh[2]=-0.0001;
      _bmax.xyzh[0]=_xframe/2.;
      _bmax.xyzh[1]=_yframe/2.;
      _bmax.xyzh[2]=0.0001;
      initBB();
      _loaded=true;
    }
    /**
     */
    void Image3D::save(string file){
      cvSaveImage(file.c_str(),_img);
    }
    /**
     */
    void Image3D::draw(){
	updateBB();
	glPushMatrix();
	float m[16];
	_matrix3d.getMatrixCMO(m);
	glMultMatrixf(m);
	
	if((_drawBB)||(_drawAABB)){
	  drawBoundingBoxGL();
	}
	
       GLfloat color[4];
       glGetFloatv(GL_CURRENT_COLOR,color);
       glColor3f(1,1,1);
       
       glEnable(GL_TEXTURE_2D); 
      
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
       glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _img->width, _img->height,0, GL_BGR, GL_UNSIGNED_BYTE, _img->imageData); 

       glBegin(GL_POLYGON);
       glTexCoord2i(0, 0); 
       glVertex3f(-_xframe/2.,_yframe/2.,0); // top left
       glTexCoord2i(0, 1); 
       glVertex3f(-_xframe/2.,-_yframe/2.,0); // bottom left
       glTexCoord2i(1, 1); 
       glVertex3f(_xframe/2.,-_yframe/2.,0);  // bottom right	 
       glTexCoord2i(1, 0); 
       glVertex3f(_xframe/2.,_yframe/2.,0); // top right
       glEnd();
       
       glDisable(GL_TEXTURE_2D);
       glColor4fv(color);
       
       glPopMatrix();
    }
    /**
     */
    void Image3D::set3DFrame(double width, double height) throw(VException){
      if((width<0)||(height<0))
	throw VException("virtua::objects::Image3D::set3DFrame(): the width and the height of the 3D frame must be greater or equal to zero.");
      _xframe=width;
      _yframe=height;
       _d.x=_xframe;
      _d.y=_yframe;
      _bmin.xyzh[0]=-_xframe/2.;
      _bmin.xyzh[1]=-_yframe/2.;
      _bmin.xyzh[2]=-0.0001;
      _bmax.xyzh[0]=_xframe/2.;
      _bmax.xyzh[1]=_yframe/2.;
      _bmax.xyzh[2]=0.0001;
      initBB();
    }
   
  }
  
}