

#ifndef _MATRIX_HH
#define _MATRIX_HH

#include "vertex.hh"

namespace virtua {

  namespace math {
        
    template<int n>
    class Matrix
    {
    public:
      /// Matrix with 0's everywhere
      Matrix();

      /// Init using a 2-dim array
      Matrix(const double array[n][n]);
      
      Matrix(const float array[n][n]);

      /// Multiplication by a scalar
      Matrix<n>& operator*=(double);
      Matrix<n>& operator/=(double);
    
      /// Multiplication by a matrix
      Matrix<n>& operator*=(const Matrix<n>&);
    
      /// Addition with another matrix
      Matrix<n>& operator+=(const Matrix<n>&);
      Matrix<n>& operator-=(const Matrix<n>&);
    
      /// Copy
      Matrix<n>& operator=(const Matrix<n>&);

      //! Equality testing
      bool operator==(const Matrix<n>&) const;
      inline bool operator!=(const Matrix<n>& M) const { return !operator==(M); }
      
      /// Return the transposed version of this matrix
      Matrix<n> transpose() const;

      /// Access
      inline double& operator()(int i, int j) {return v[i][j];}
      inline double operator()(int i, int j) const {return v[i][j];}

    protected:
      double v[n][n];
    };
  
    template<int n>
    std::ostream& operator<<(std::ostream& out, const Matrix<n>& M) {
      for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
          out<<M(i,j)<<" ";
        }
        out<<std::endl;
      }
      return out;
    }
        
    class Matrix3: public Matrix<3> {
    public:
      /// Copy a Matrix<3>
      Matrix3(Matrix<3> M): Matrix<3>(M) {}

      /// 0 Matrix
      Matrix3(): Matrix<3>() {}

      /// From a 2d array
      Matrix3(double array[3][3]): Matrix<3>(array) {}
      Matrix3(float array[3][3]): Matrix<3>(array) {}

      /// Init using 3 column-vectors
      Matrix3(const Vector e[3]);
      Matrix3(const Vector& e0, const Vector& e1, const Vector& e2);

      /// Multiplication by a vector
      Vector operator*(const Vector&) const;

      double det() const;
    };

    Vector operator*(Vector, const Matrix3&);

    Matrix3 inverse(const Matrix3&);

    //! Update an orientation matrix knowing its derivative
    /*!
      \param orient Reference to matrix to update.
      \param rotation Derivative of the rotation multiplied by the timestep.
    */
    void updateOrient(Matrix3& orient, const Vector& rotation);

    class Matrix4: public Matrix<4> {
    public:
      /// Copy a Matrix<4>
      Matrix4(Matrix<4> M): Matrix<4>(M) {}
      Matrix4(const Vector& e0, const Vector& e1, const Vector& e2);
      
      /// 0 Matrix
      Matrix4(): Matrix<4>() {}

      /// From a 2d array
      Matrix4(double array[4][4]): Matrix<4>(array) {}
      Matrix4(float array[4][4]): Matrix<4>(array) {}
      
      /// From a Matrix3
      Matrix4(const Matrix3& M);

      /// Multiplication by a vector
      Vector operator*(const Vector&) const;

      /// Return the three first elements in a column
      Vector getColumn(int) const;

      /// To an openGL matrix
      void fromGL(double m[16]);
      void toGL(double m[16]);
      void toGL(double v[4][4]) const;
      inline void toGL(double v[16]) const { toGL((double (*)[4])v); }
    };

    /*! \throw NonInvertible<4> The matrix cannot be inverted */
    Matrix4 inverse(const Matrix4&);

    template<int n>
    Matrix<n> operator*(double, const Matrix<n>&);

    template<int n>
    inline Matrix<n> operator*(const Matrix<n>& m, double x) {return x*m;}

    template<int n>
    Matrix<n> operator/(const Matrix<n>& m, double x);

    template<int n>
    Matrix<n> operator*(const Matrix<n>&, const Matrix<n>&);

    template<int n>
    Matrix<n> operator+(const Matrix<n>&, const Matrix<n>&);

    template<int n>
    Matrix<n> operator-(const Matrix<n>&, const Matrix<n>&);

    class Rotation3: public Matrix3
    {
    public:
      Rotation3(double angle, const Vector& axis);
    };

    class Scaling3: public Matrix3
    {
    public:
      Scaling3(double x, double y, double z);
    };
    
    class Identity3: public Matrix3
    {
    public:
      Identity3();
    };

    class Identity4: public Matrix4
    {
    public:
      Identity4();
    };

    class Translation4: public Identity4
    {
    public:
      Translation4(const Vector&);
      Translation4(double x, double y, double z);
    };

    class OrthoNorm3: public Matrix3
    {
    public:
      OrthoNorm3();
      OrthoNorm3(const Matrix3&);

      void correct();

      inline OrthoNorm3& operator=(const Matrix<3>& M) {
	Matrix<3>::operator=(M);
	return *this;
      }

    };

    /// u * transpose(u)
    Matrix3 transTime(const Vector&);
    

  }

}

#include <iostream>
#include <sstream>
#include <cmath>

namespace virtua{
  
  namespace math{

template<int n>
virtua::math::Matrix<n>::Matrix()
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] = 0.0;
    }
  }
}

template<int n>
virtua::math::Matrix<n>::Matrix(const double p[n][n])
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] = p[i][j];
    }
  }
}

template<int n>
virtua::math::Matrix<n>::Matrix(const float p[n][n])
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] = p[i][j];
    }
  }
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator*=(double x)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] *= x;
    }
  }
  return *this;
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator/=(double x)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] /= x;
    }
  }
  return *this;
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator*=(const virtua::math::Matrix<n>& m)
{
  *this = *this * m;
  return *this;
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator+=(const virtua::math::Matrix<n>& m)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] += m(i, j);
    }
  }
  return *this;
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator-=(const virtua::math::Matrix<n>& m)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] -= m(i, j);
    }
  }
  return *this;
}

template<int n>
virtua::math::Matrix<n>& virtua::math::Matrix<n>::operator=(const virtua::math::Matrix<n>& m)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      v[i][j] = m(i, j);
    }
  }
  return *this;
}

template<int n>
bool virtua::math::Matrix<n>::operator==(const virtua::math::Matrix<n>& m) const
{
  for(int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      if (v[i][j] != m.v[i][j]) return false;
    }
  }
  return true;    
}

template<int n>
Matrix<n> operator*(double x, const Matrix<n>& m)
{
  virtua::math::Matrix<n> N(m);
  return N *= x;
}

template<int n>
Matrix<n> operator/(const Matrix<n>& m, double x)
{
  virtua::math::Matrix<n> N(m);
  return N /= x;
}

template<int n>
Matrix<n> operator+(const Matrix<n>& m, const Matrix<n>& N)
{
  Matrix<n> p(m);
  return p+=N;
}

template<int n>
Matrix<n> operator-(const Matrix<n>& m, const Matrix<n>& N)
{
  Matrix<n> p(m);
  return p-=N;
}

template<int n>
Matrix<n> operator*(const Matrix<n>& m, const Matrix<n>& N)
{
  Matrix<n> p;
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      for (int k=0; k<n; ++k) {
	p(i, j) += m(i, k)*N(k, j);
      }
    }
  }
  return p;
}

template<int n>
Matrix<n> Matrix<n>::transpose() const
{
  Matrix<n> ret;
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      ret(i,j) = operator()(j,i);
    }
  }

  return ret;
}

/*
template<int n>
std::ostream& operator<<(std::ostream& out, const Matrix<n>& M)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      out<<" "<<M(i,j);
    }
    out<<std::endl;
  }
  return out;
}
*/
template<int n>
std::istream& operator>>(std::istream& in, virtua::math::Matrix<n>& M)
{
  for (int i=0; i<n; ++i) {
    for (int j=0; j<n; ++j) {
      in>>M(i,j);
    }
  }
  return in;
}

  }
  
}

#endif
