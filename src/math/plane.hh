

#ifndef _PLANE_H
#define _PLANE_H

#include "vertex.hh"
#include "matrix.hh"

namespace virtua{

  namespace math {

    class Plane
    {
    public:
      /**
	 Default plane: the ground (horizontal, altitude 0)
      */
      Plane(): normal(0, 1, 0), d(0) {}
      
      /**
      */
      Plane(const Plane &P){
	normal=P.normal;
	d=P.d;
      }

      /**
	 Plane defined by three points
      */
      Plane(Vector p1, Vector p2, Vector p3);

      /**
	 Plane defined by a point and a normal vector.
	 normal.size() must be 1 !!!
      */
      Plane(Vector p, Vector normal);

      Plane(Vector _normal, double _d): normal(_normal), d(_d) {}

      void translate(Vector);
      void rotate(const Matrix3&);

      //! Plane below vertex.
      inline bool isBelow(Vector p) const { return p*normal >= d; }


      //FIXME:
      //    private:

      /// Normal to the plane. Must have length = 1
      Vector normal;
  
      /// Distance from the center
      double d;
    };

    /**
       Compute intersection between a segment and a plane.
       \param plane The plane
       \param A First end point of the segment
       \param B Second end point of the segment
       \param result Intersection point, if any
  
       \return True if intersection, else false
    */
    bool intersect(const Plane& plane, const Vector& A, const Vector& B, Vector& result);

    /**
       Compute intersection between a ray and a plane.
       \param plane The plane
       \param A end point of the segment
       \param V direction of the ray
       \param result Intersection point, if any
       \param distance from A to the intersection point, if any

       \return True if intersection, else false
    */
    bool intersectRay(const Plane& plane, const Vector& A, const Vector& V, Vector& result, double& d);

    /**
       Project a vertex on a plane.
       The resulting vertex belongs to the plane
    */
    Vector project(const Plane& plane, const Vector& v);

    /**
       Project a vector on a plane
    */
    Vector projectV(const Plane& plane, const Vector& v);

  }
  
}


#endif
