#ifndef __VIRTUAL_OBJECT_DIMENSION__
#define __VIRTUAL_OBJECT_DIMENSION__

#include "vexception.h"


using namespace std;



namespace virtua{  
  
namespace objects{

/**\brief This class represents the dimension of a virtual object.
*/
class Dimension{
  public:
    double x, y, z, t;
    Dimension();
    Dimension(double dx, double dy, double dz, double dt) throw (VException);
    Dimension(double dx, double dy, double dz) throw (VException);
    Dimension(double dx, double dy) throw (VException);
    ~Dimension();
    void applyScaleFactor(float sx, float sy, float sz);
};

}

}


#endif