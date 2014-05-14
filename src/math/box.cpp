

#include "box.hh"

namespace virtua{
  
  namespace math{

AxisAlignedBox::AxisAlignedBox(): center(0,0,0)
{
  s[0] = s[1] = s[2] = 1.0;
}

AxisAlignedBox::AxisAlignedBox(Vector _center, double s0, double s1, double s2):
  center(_center)
{
  s[0] = 2*s0;
  s[1] = 2*s1;
  s[2] = 2*s2;
}

AxisAlignedBox::AxisAlignedBox(const Vector& v1, const Vector& v2)
{
  center = 0.5*(v1 + v2);
  for (int i=0; i<3; ++i)
    s[i] = v2[i] - v1[i];
}

void AxisAlignedBox::getVertices(Vector out[8]) const
{
  Vector e[3];
  getHalfEdges(e);

  for (int i=0; i<8; ++i) {
    out[i] = center;
    for (int j=0; j<3; ++j) {
      if (i&(1<<j)) out[i] += e[j];
      else out[i] -= e[j];
    }
  }
}

void AxisAlignedBox::getHalfEdges(Vector out[3]) const
{
  out[0] = Vector(s[0]/2.0, 0, 0);
  out[1] = Vector(0, s[1]/2.0, 0);
  out[2] = Vector(0, 0, s[2]/2.0);
}

void AxisAlignedBox::getEdgeSizes(double out[3]) const
{
  for (int i=0; i<3; ++i) out[i] = s[i];  
}

/* ************************************** Box ************************************************************* */
Box::Box(): center(0,0,0)
{
  e[0] = Vector(0.5, 0, 0);
  e[1] = Vector(0, 0.5, 0);
  e[2] = Vector(0, 0, 0.5);
  s[0] = s[1] = s[2] = 1.0;
}

Box::Box(Vector _center, Vector e0, Vector e1, Vector e2):
  center(_center)
{
  e[0] = e0;
  e[1] = e1;
  e[2] = e2;
  for (int i=0; i<3; ++i) {
    s[i] = 2.0*e[i].size();
  }
}

void Box::getVertices(Vector out[8]) const
{
  for (int i=0; i<8; ++i) {
    out[i] = center;
    for (int j=0; j<3; ++j) {
      if (i&(1<<j)) out[i] += e[j];
      else out[i] -= e[j];
    }
  }
}

void Box::getHalfEdges(Vector out[3]) const
{
  for (int i=0; i<3; ++i) out[i] = e[i];
}

void Box::getEdgeSizes(double out[3]) const
{
  for (int i=0; i<3; ++i) out[i] = s[i];
}

OrthoNorm3 Box::getOrient() const
{
  Vector v[3];
  for (int i=0; i<3; ++i) v[i] = 2.0*e[i]/s[i];
  Matrix3 M(v);

  return M;
}

void Box::rotate(const Matrix3& M)
{
  center = M*center;
  for (int i=0; i<3; ++i) e[i] = M*e[i];
}

bool Box::isInside(Vector v) const
{
  v -= center;
  for (int i=0; i<3; ++i)
    if (4.0*v*e[i]/s[i] > s[i])
      return false;

  return true;
}

  }
  
}