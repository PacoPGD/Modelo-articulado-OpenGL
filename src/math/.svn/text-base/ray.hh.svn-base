

#ifndef _MATHRAY_HH
#define _MATHRAY_HH

#include "vertex.hh"
#include "matrix.hh"
#include <cassert>

namespace virtua{

  namespace math {

    class Ray {
    public:
      Ray();
      
      inline bool isFinite() const { return length >= 0.0; }
      inline void setInfinite() { length = -1.0; }
      inline void setLength(double l) { assert(l>=0); length = l; }
      inline double getLength() const { return length; }
      inline Vector getOrigin() const { return origin; }
      inline Vector getDirection() const { return dir; }
      inline void setOrigin(Vector o) { origin = o; }
      inline void setDirection(Vector d) { double s = d.size(); assert(s>=SMALL_VECTOR); dir = d/s; }
    
      void transform(const Matrix4& M);
      
    private:
      Vector origin;
      Vector dir;
      double length;
    };

    double computeDist(const Ray&, const Vector&);
  }
  
}


#endif
