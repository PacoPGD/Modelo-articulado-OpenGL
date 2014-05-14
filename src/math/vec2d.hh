

#ifndef _MATH_VEC2D_HH
#define _MATH_VEC2D_HH

#include <iostream>

#ifndef SMALL_VECTOR
#define SMALL_VECTOR (1e-4)
#endif

namespace virtua{
  namespace math {

    //! Represents a 2d vector
    class Vec2D {
    public:
      double x;
      double y;

    public:
      Vec2D(double _x=0, double _y=0): x(_x), y(_y) {};

      Vec2D& operator+=(const Vec2D&);
      Vec2D& operator-=(const Vec2D&);

      Vec2D& operator/=(double);
      Vec2D& operator*=(double);

      //! Returns the opposite vector
      Vec2D operator- ();

      //! square size
      double size2() const;

      double size() const;

      inline Vec2D rotate90() const {return Vec2D(-y, x);}
    };
  }
}


namespace virtua{
  namespace math{

//! Dot product.  
double operator*(const math::Vec2D&, const math::Vec2D&);

//! Cross product.  
double operator^(const math::Vec2D&, const math::Vec2D&);

//! Addition of two vectors
inline math::Vec2D operator+ (const math::Vec2D& a,
				     const math::Vec2D& b)
{
  math::Vec2D ret = a;
  return ret+=b;
}

//! Subtraction of two vectors
inline math::Vec2D operator- (const math::Vec2D& a,
				     const math::Vec2D& b)
{
  math::Vec2D ret = a;
  return ret-=b;
}

//! Multiplication by a scalar
math::Vec2D operator*(double, math::Vec2D);
    
//! Multiplication by a scalar
inline math::Vec2D operator*(const math::Vec2D& a, double b)
{
  return b*a;
}

//! Division by a scalar
math::Vec2D operator/(math::Vec2D, double);

//! Human readable output
inline std::ostream& operator<<(std::ostream& out, const math::Vec2D& v)
{
  return out<<v.x<<" "<<v.y;
}

bool operator==(const math::Vec2D&, const math::Vec2D&);
inline bool operator!=(const math::Vec2D& A, const math::Vec2D& B) { return !(A==B); }

//! Check intersection of two 2d segments
bool segment_intersection(const math::Vec2D& pt1,
			  const math::Vec2D& dir1,
			  const math::Vec2D& pt2,
			  const math::Vec2D& dir2);

  }
}

#endif
