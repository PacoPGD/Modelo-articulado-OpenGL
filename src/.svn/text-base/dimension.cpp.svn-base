#include "dimension.h"

namespace virtua{  
  
namespace objects{

Dimension::Dimension(){
  x=0.0;y=0.0;z=0.0;t=0.0; 
}
/**
 *
 *
 */    
Dimension::Dimension(double dx, double dy, double dz, double dt) throw (VException)
    {
      if((dx<0)||(dy<0)||(dz<0)||(dt<0))
	throw VException("virtua::objects::Dimension: Dimensions must be greater or equal to 0.");
      x=dx;y=dy;z=dz;t=dt;
    }
/**
 *
 *
 */    
Dimension::Dimension(double dx, double dy, double dz) throw (VException){
      if((dx<0)||(dy<0)||(dz<0))
	throw VException("virtua::objects::Dimension: Dimensions must be greater or equal to 0.");
      x=dx;y=dy;z=dz;t=0.0;
    }
/**
 * 
 * 
 */
Dimension::Dimension(double dx, double dy) throw (VException){
      if((dx<0)||(dy<0))
	throw VException("virtua::objects::Dimension: Dimensions must be greater or equal to 0.");
      x=dx;y=dy;z=0.0;t=0.0;
    }
/**
 * 
 * 
 * 
 */
Dimension::~Dimension(){
  
}
/**
 * 
 * 
 */
void Dimension::applyScaleFactor(float sx, float sy, float sz){
      x=x*sx;
      y=y*sy;
      z=z*sz;
}

}

}