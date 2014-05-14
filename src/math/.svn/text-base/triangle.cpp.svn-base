#include "triangle.hh"
#include "plane.hh"

namespace virtua{
  
  namespace math{

void Triangle::translate(Vector v)
{
  for (int i=0; i<3; ++i) p[i] += v;
}

void Triangle::rotate(const Matrix3& M)
{
  for (int i=0; i<3; ++i) p[i] = M*p[i];
}

bool Triangle::intersectRay(Vector origin, Vector direction, Vector& _I, double& _d) const
{
  Plane pl(p[0], p[1], p[2]);

  Vector I;
  double d;
  if (!math::intersectRay(pl, origin, direction, I, d)) return false;

  Vector N = (p[1]-p[0])^(I-p[0]);
  Vector N2 = (p[2]-p[1])^(I-p[1]);
  if (N*N2 < 0) return false;
  N2 = (p[0]-p[2])^(I-p[2]);
  if (N*N2 < 0) return false;

  _I = I;
  _d = d;
  return true;
}

  }
  
}