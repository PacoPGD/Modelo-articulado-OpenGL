#ifndef _MATH_TRIANGLE_HH
#define _MATH_TRIANGLE_HH

#include "vertex.hh"
#include "matrix.hh"

namespace virtua{
  namespace math {
    struct Triangle
    {
      Vector p[3];

      //! Uninitialized triangle.
      Triangle() {};

      Triangle(Vector p0, Vector p1, Vector p2) {
	p[0] = p0;
	p[1] = p1;
	p[2] = p2;
      }

      void translate(Vector);
      void rotate(const Matrix3&);

      //! Check for intersection with a ray
      bool intersectRay(Vector origin, Vector direction, Vector& I, double& d) const;
    };
  }
}

#endif
