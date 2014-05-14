#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
#include <cmath>
#include <stdlib.h>

#ifndef SMALL_VECTOR
#define SMALL_VECTOR (1e-4)
#endif

namespace virtua{

  namespace math {

    /**
       Represents the position of a point in a 3d-space.
    */
    class Vector
    {
    public:
      double x;
      double y;
      double z;

    public:
      Vector(): x(0), y(0), z(0)
      {
      }
      Vector(double X, double Y, double Z): x(X), y(Y), z(Z)
      {
      }
      Vector(const Vector& other): x(other.x), y(other.y), z(other.z)
      {
      }
      Vector(double t[3])
      {
	x = t[0];
	y = t[1];
	z = t[2];
      }
      Vector(float t[3])
      {
	x = t[0];
	y = t[1];
	z = t[2];
      }

      // Add
      inline Vector operator+(const Vector& v) const {
	return Vector(x+v.x, y+v.y, z+v.z);
      }

      // Subtract
      inline Vector operator-(const Vector& v) const {
	return Vector(x-v.x, y-v.y, z-v.z);
      }

      // Dot product
      inline double operator*(const Vector& v) const { return x*v.x + y*v.y + z*v.z; }

      // Multiply by scalar
      inline Vector operator*(double k) const { return Vector(x*k, y*k, z*k); }

      // Divide by scalar
      inline Vector operator/(double k) const { return Vector(x/k, y/k, z/k); }
      inline Vector& operator/=(double k) { x/=k; y/=k; z/=k; return *this; }

      // Opposite
      inline Vector operator-() const { return Vector(-x, -y, -z); }

      // Increase
      inline Vector& operator+=(const Vector& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }

      inline Vector& operator-=(const Vector& v) { x-=v.x; y-=v.y; z-=v.z; return *this; }

      // Assignment
      inline Vector& operator=(const Vector& v) { x=v.x; y=v.y; z=v.z; return *this; }

      // Equality
      inline bool operator==(const Vector& v) const { return x==v.x && y==v.y && z==v.z; }
      inline bool operator!=(const Vector& v) const { return !operator==(v); }

      // Length of vector
      inline double size() const { return sqrt((*this)*(*this)); }

      // Square Length
      inline double size2() const { return (*this)*(*this); }

      inline double& operator[](int i) {
		switch(i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: abort(); return x;
		};
	}
      inline double operator[](int i) const {
		switch(i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: abort(); return 0.0;
		};
	}

    };

    class VectorLexOrder {
    public:
      inline bool operator()(const Vector& p1, const Vector& p2) const {
        for (int i=0; i<2; ++i) if (p1[i] != p2[i]) return p1[i] < p2[i];
        return p1[2] < p2[2];
      }
    };
    
    class Vector2DLexOrder {
    public:
      inline bool operator()(const Vector& p1, const Vector& p2) const {
        if (p1[0] != p2[0]) return p1[0] < p2[0];
        return p1[2] < p2[2];
      }
    };
      
    // Output to a stream
    inline std::ostream& operator<<(std::ostream& out, const Vector& v)
    {
      return out<<v.x<<" "<<v.y<<" "<<v.z;
    }

    inline std::istream& operator>>(std::istream& in, Vector& v)
    {
      return in>>v.x>>v.y>>v.z;
    }

    // Product by a scalar 
    inline Vector operator*(double x, const Vector& v)
    {
      return v*x;
    }

    // Cross product
    inline Vector operator^(const Vector& a, const Vector& b)
    {
      return Vector(a.y*b.z - a.z*b.y,
		    a.z*b.x - a.x*b.z,
		    a.x*b.y - a.y*b.x);
    }

    /// 'Coordinate by coordinate' product
    inline Vector operator |(const Vector& a, const Vector& b)
    {
      return Vector(a.x*b.x, a.y*b.y, a.z*b.z);
    }

    /// Compute mirror of a Vector A relatively to another vector I
    inline Vector mirror(const Vector& A, const Vector& I)
    {
      return ((A * I)*I*2 - A);
    }

    //! Return true if the projections of two segments on (XZ) intersect
    /*!
      \param p1 An endpoint of the first segment
      \param d1 Difference vector to the second endpoint
      */
    bool cross(Vector p1, Vector d1, Vector p2, Vector d2);
  }
}


#endif
