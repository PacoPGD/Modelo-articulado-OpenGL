

#ifndef _MATH_INTERSECT_HH
#define _MATH_INTERSECT_HH

#include "plane.hh"
#include "box.hh"
#include "triangle.hh"
#include "mesh.hh"
#include "ray.hh"

namespace virtua{

  namespace math {
    bool intersect(Box, Box);
    bool intersect(AxisAlignedBox, AxisAlignedBox);
    bool intersect(AxisAlignedBox, Box, bool try_other=true);
    inline bool intersect(Box b, AxisAlignedBox bb) { return intersect(bb, b); }

    bool intersect(Plane, Box);
    inline bool intersect(Box b, Plane p) { return intersect(p, b); }

    bool intersect(Triangle, Box);
    inline bool intersect(Box b, Triangle t) { return intersect(t, b); }

    bool intersect(Plane, AxisAlignedBox);
    inline bool intersect(AxisAlignedBox b, Plane p) { return intersect(p, b); }

    bool intersect(Triangle, AxisAlignedBox);
    inline bool intersect(AxisAlignedBox b, Triangle t) { return intersect(t, b); }

    bool intersect(Mesh, AxisAlignedBox);
    inline bool intersect(AxisAlignedBox b, Mesh m) { return intersect(m,b); }
    
    bool intersect(Mesh, Box);
    inline bool intersect(Box b, Mesh m) { return intersect(m,b); }
    
    bool intersect(Triangle, Ray);
    inline bool intersect(Ray r, Triangle t) { return intersect(t,r); }
  
    /*!
      \param dist if non-null, contains upon return the distance of the intersection point with the origin of the ray
    */
    bool intersect(Mesh, Ray, double* dist=0);
    inline bool intersect(Ray r, Mesh m, double* dist=0) { return intersect(r,m,dist); }
    
    bool intersect(Plane, Ray);
    inline bool intersect(Ray r, Plane p) { return intersect(p, r); }
    
  }
  
}


#endif
