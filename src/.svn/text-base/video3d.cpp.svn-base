#include "video3d.h"

namespace virtua{
  
  namespace objects{
    /**
     */
    Video3D::Video3D(){
      _img=NULL;
      _loaded=false;
      _vid=NULL;
      _xframe=1.0;
      _yframe=1.0;
      _nframes=0;
      _fps=0;
      _file="";
    }
    /**
     */
    Video3D::~Video3D(){
      if(_loaded){
	cvReleaseCapture(&_vid);
      }
    }
    /**
     */
    void Video3D::load(string file) throw (VException){
      if(_loaded)
	cvReleaseCapture(&_vid);
      _vid=cvCaptureFromFile(file.c_str());
      if(_vid==NULL)
	  throw VException("virtua::objects::Video3D::load(): can't open data file.");
      _d.x=_xframe;
      _d.y=_yframe;
      _d.z=0.0;
      _bmin.xyzh[0]=-_xframe/2.;
      _bmin.xyzh[1]=-_yframe/2.;
      _bmin.xyzh[2]=-0.0001;
      _bmax.xyzh[0]=_xframe/2.;
      _bmax.xyzh[1]=_yframe/2.;
      _bmax.xyzh[2]=0.0001;
      initBB();
      _nframes=cvGetCaptureProperty(_vid,CV_CAP_PROP_FRAME_COUNT);
      _fps=cvGetCaptureProperty(_vid,CV_CAP_PROP_FPS);
      _d.t=(double)_nframes/(double)_fps;    
      _frametime=(unsigned int)floor((1./(double)_fps)*1000);
      _tm.init();
      _startframetime=0;
      _endframetime=0;
      _loaded=true;
      _file=file;
    }
    /**
     */
    void Video3D::save(string file){
      if(_img!=NULL)
	cvSaveImage(file.c_str(),_img);
    }
    /**
     */
    void Video3D::next(){
      if(!cvGrabFrame(_vid)){
	cvReleaseCapture(&_vid);
	_vid = cvCaptureFromFile(_file.c_str());
	if(_vid!=NULL)
	  cvGrabFrame(_vid);
	_tm.init();
	_startframetime=0;
	_endframetime=0;
      }
      _img=cvRetrieveFrame(_vid);
    }
     /**
     */
    void Video3D::draw(){
   
      _startframetime=_tm.end();
      if(_startframetime>=_endframetime){
	next();
	_endframetime=_startframetime+_frametime;
      }
      
      drawGL();
    }
    /**
     */
    void Video3D::drawFrame(){
      next();
      drawGL();
    }
    /**
     */
    void Video3D::drawGL(){
      updateBB();
      if(_img!=NULL){
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
    }
    /**
     */
    void Video3D::set3DFrame(double width, double height) throw(VException){
      if((width<0)||(height<0))
	throw VException("virtua::objects::Video3D::set3DFrame(): the width and the height of the 3D frame must be greater or equal to zero.");
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
    /**
     */
    double Video3D::getFrameTime(){
      return _frametime;
    }
   
  }
  
}