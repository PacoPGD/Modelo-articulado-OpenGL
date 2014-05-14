#include "3ds.h"

namespace virtua{
  
  namespace objects{
    
    namespace formats{

      /**
       */
      DS3::DS3(){
	_loaded=false;
	_3dmodel=NULL;
      }
      /**
       */
      DS3::~DS3(){
	if(_loaded)
	  lib3ds_file_free(_3dmodel);
      }
      /** Loads the object from the specified file.
      */
      void DS3::load(string file) throw(VException)
      {
	Lib3dsVector bmin, bmax;
	
	if(_loaded)
	  lib3ds_file_free(_3dmodel);
	_3dmodel=lib3ds_file_load(file.c_str());
	if(_3dmodel==NULL)
	  throw VException("virtua::objects::formats::DS3::load(): can't open data file.");
	lib3ds_file_eval(_3dmodel, 0.0f);
	lib3ds_file_bounding_box_of_objects(_3dmodel, LIB3DS_TRUE, 
                                    LIB3DS_FALSE, LIB3DS_FALSE, 
                                    bmin, bmax);
	_d.x = bmax[0] - bmin[0];
	_d.y = bmax[1] - bmin[1];
	_d.z = bmax[2] - bmin[2];
	_d.t=0.0;
	_bmin.xyzh[0]=bmin[0];
	_bmin.xyzh[1]=bmin[1];
	_bmin.xyzh[2]=bmin[2];
	_bmax.xyzh[0]=bmax[0];
	_bmax.xyzh[1]=bmax[1];
	_bmax.xyzh[2]=bmax[2];
	initBB();
	_nframes=_3dmodel->frames;
	_currentframe=0;
	_loaded=true;
      }
       /**
      */
      void DS3::save(string file){
	if(_loaded)
	  lib3ds_file_save(_3dmodel,file.c_str());
      }
       /**
      */
      void DS3::draw(){
	updateBB();
	glPushMatrix();
	float m[16];
	_matrix3d.getMatrixCMO(m);
	glMultMatrixf(m);
	if((_drawBB)||(_drawAABB)){
	  drawBoundingBoxGL();
	}
	
	lib3ds_file_eval(_3dmodel, _currentframe);
	_currentframe=(_currentframe+1)%_nframes;
	
	display((char*)".",_3dmodel,_3DS_COLOR);
	
	glPopMatrix();
      }
}

}

}