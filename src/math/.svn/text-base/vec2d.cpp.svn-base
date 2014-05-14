
#include "vec2d.hh"

#include <cmath>

namespace virtua{
  
  namespace math{
    
    
Vec2D& Vec2D::operator+=(const Vec2D& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vec2D& Vec2D::operator/=(double c)
{
  x /= c;
  y /= c;
  return *this;
}

Vec2D& Vec2D::operator*=(double c)
{
  x *= c;
  y *= c;
  return *this;
}

Vec2D Vec2D::operator- ()
{
  return Vec2D(-x, -y);
}

double Vec2D::size2() const
{
  return x*x + y*y;
}

double Vec2D::size() const
{
  return sqrt( size2() );
}

double operator*(const Vec2D& a, const Vec2D& b)
{
  return a.x*b.x + a.y*b.y;
}

double operator^(const Vec2D& a, const Vec2D& b)
{
  return a.x*b.y - b.x*a.y;
}

Vec2D operator*(double d, Vec2D v)
{
  v*=d;
  return v;
}

Vec2D operator/(Vec2D v, double d)
{
  v/=d;
  return v;
}

bool segment_intersection(const Vec2D& pt1, const Vec2D& dir1,
                          const Vec2D& pt2, const Vec2D& dir2)
{
  Vec2D d1 = pt2 - pt1;
  Vec2D d2 = pt2 + dir2 - pt1;
  if ((d1^dir1) * (d2^dir1) > 0) return false;
  
  //d1 = -d1;
  d2 = pt1 + dir1 - pt2;
  if ((d1^dir2) * (d2^dir2) < 0) return false;
  
  return true;
}

bool operator==(const Vec2D& A, const Vec2D& B)
{
  return A.x == B.x && A.y == B.y;
}


  }
  
}