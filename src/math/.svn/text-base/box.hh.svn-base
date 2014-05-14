

#ifndef _MATH_BOX_HH
#define _MATH_BOX_HH

#include "vertex.hh"
#include "matrix.hh"

namespace virtua{

namespace math {
    class AxisAlignedBox {
    public:
      //! Unit box centerer in (0,0,0)
      AxisAlignedBox();

      //! Box with half-sizes
      AxisAlignedBox(Vector center, double s0, double s1, double s2);
      AxisAlignedBox(const Vector&, const Vector&);

      void getVertices(Vector out[8]) const;
      void getHalfEdges(Vector out[3]) const;
      void getEdgeSizes(double out[3]) const;
      inline Vector getCenter() const { return center; }

      inline void translate(Vector v) { center += v; }

      inline bool isInside(Vector p) const {
        Vector d = p-center;
        return (fabs(d.x) < s[0]) && (fabs(d.y) < s[1]) && (fabs(d.z) < s[2]);
      }
      
    private:
      Vector center;
      //! Size of each edge
      double s[3];      
    };

    class Box {
    public:
      //! Default box: center in (0,0,0), edges of length 1
      Box();
      //! Box with center and half-edges
      Box(Vector center, Vector e0, Vector e1, Vector e2);

      void getVertices(Vector out[8]) const;
      void getHalfEdges(Vector out[3]) const;
      void getEdgeSizes(double out[3]) const;
      inline Vector getCenter() const { return center; }

      //! Return an orthonormal matrix of the orientation of the box
      OrthoNorm3 getOrient() const;

      void translate(Vector v) { center += v; }
      //! Matrix must be orthonormal
      void rotate(const Matrix3&);

      bool isInside(Vector p) const;

    private:
      Vector center;
      //! Half edges
      Vector e[3];
      //! Size of each edge
      double s[3];
    };
  }
  
}

#endif
