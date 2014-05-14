

#include "plane.hh"

namespace virtua{
  
  namespace math{
    
Plane::Plane(Vector p1, Vector p2, Vector p3)
{
  normal = ((p2-p1)^(p3-p1));
  double size = normal.size();
  if (size < SMALL_VECTOR) std::cerr<<"Plane::Plane: small triangle p1 p2 p3"<<std::endl;
  normal/=size;
  d = p1*normal;
}

Plane::Plane(Vector p, Vector n)
{
  normal = n;
  d = p*n;
}

void Plane::translate(Vector v)
{
  d += v*normal;
}

void Plane::rotate(const Matrix3& M)
{
  normal = M*normal;
}

bool intersect(const Plane& plane, const Vector& A, const Vector& B, Vector& result)
{
  Vector IA, IB;
  Vector n = plane.normal;
  Vector I = n * plane.d;
  IA = A-I;
  IB = B-I;
  Vector AB = B-A;

  double nIA = n*IA;
  // Check if intersection
  if ((nIA)*(n*IB) > 0) return false;

  // Compute intersection
  double t = -nIA/(AB*n);

  result = A + t*AB;
  return true;
}

bool intersectRay(const Plane& plane, const Vector& A, const Vector& V, Vector& result, double& d)
{
  double vn = V*plane.normal;
  if (fabs(vn) < SMALL_VECTOR) return false;

  double t = (plane.d - A*plane.normal)/vn;
  if (t<0) return false;

  result = A+t*V;
  d = t;
  return true;
}

Vector project(const Plane& plane, const Vector& v)
{
  Vector p;
  Vector v2;
  const Vector& n = plane.normal;

  v2 = v - (n * plane.d);
  p = v2 - (v2*n)*n;
  return p + (n * plane.d);
}

Vector projectV(const Plane& plane, const Vector& v)
{
  const Vector& n = plane.normal;
  return v - (v*n)*n;
}

  }
}