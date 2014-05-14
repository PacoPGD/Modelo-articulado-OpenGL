
#include <iostream>
#include <cmath>
#include <cassert>
#include "matrix.hh"

using namespace std;

namespace virtua{
  
  namespace math{

Matrix3::Matrix3(const Vector e[3])
{
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      v[i][j] = e[j][i];
    }
  }
}

Matrix3::Matrix3(const Vector& e0, const Vector& e1, const Vector& e2)
{
  for (int i=0; i<3; ++i) {
    (*this)(i,0) = e0[i];
  }
  for (int i=0; i<3; ++i) {
    (*this)(i,1) = e1[i];
  }
  for (int i=0; i<3; ++i) {
    (*this)(i,2) = e2[i];
  }
}

Vector Matrix3::operator*(const Vector& x) const
{
  Vector y;
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      y[i] += x[j]*v[i][j];
    }
  }
  return y;
}

Vector operator*(Vector x, const Matrix3& M)
{
  Vector y;
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      y[i] += x[j]*M(j,i);
    }
  }
  return y;
}

double Matrix3::det() const
{
  return
    v[0][0]*v[1][1]*v[2][2] -
    v[0][0]*v[2][1]*v[1][2] +
    v[1][0]*v[2][1]*v[0][2] -
    v[1][0]*v[0][1]*v[2][2] +
    v[2][0]*v[0][1]*v[1][2] -
    v[2][0]*v[1][1]*v[0][2];
}

Matrix3 inverse(const Matrix3& M)
{
  double d = M.det();
  if (d == 0) abort();
  
  double vals[3][3] = {
    {M(1,1)*M(2,2)-M(1,2)*M(2,1), -(M(0,1)*M(2,2)-M(0,2)*M(2,1)), M(0,1)*M(1,2)-M(0,2)*M(1,1)},
    {-(M(1,0)*M(2,2)-M(1,2)*M(2,0)), M(0,0)*M(2,2)-M(0,2)*M(2,0), -(M(0,0)*M(1,2)-M(0,2)*M(1,0))},
    {M(1,0)*M(2,1)-M(1,1)*M(2,0), -(M(0,0)*M(2,1)-M(0,1)*M(2,0)), M(0,0)*M(1,1)-M(0,1)*M(1,0)}
  };
  Matrix3 N(vals);
  return N/d;
}

Matrix4::Matrix4(const Matrix3& M)
{
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      v[i][j] = M(i,j);
    }
  }

  for (int i=0; i<3; ++i) {
    v[i][3] = v[3][i] = 0.0;
  }

  v[3][3] = 1.0;
}

Matrix4::Matrix4(const Vector& e0, const Vector& e1, const Vector& e2)
{
  for (int i=0; i<3; ++i) {
    (*this)(i,0) = e0[i];
  }
  for (int i=0; i<3; ++i) {
    (*this)(i,1) = e1[i];
  }
  for (int i=0; i<3; ++i) {
    (*this)(i,2) = e2[i];
  }
  for (int i=0; i<3; ++i) {
    (*this)(i,3) = 0;
    (*this)(3,i) = 0;
  }
  (*this)(3,3) = 1;
}

void Matrix4::toGL(double o[4][4]) const
{
  for (int j=0; j<4; ++j) {
    for (int i=0; i<4; ++i) {
      o[j][i] = v[i][j];
    }
  }  
}

void Matrix4::fromGL(double m[16])
{
  for (int j=0; j<4; ++j) {
    for (int i=0; i<4; ++i) {
      v[i][j]=m[j*4+i];
    }
  }  
}

void Matrix4::toGL(double m[16])
{
  for (int j=0; j<4; ++j) {
    for (int i=0; i<4; ++i) {
      m[j*4+i]=v[i][j];
    }
  }  
}

Vector Matrix4::operator*(const Vector& x) const
{
  double xx[4] = {x[0], x[1], x[2], 1.0};
  double yy[4] = {0, 0, 0, 0};

  for (int i=0; i<4; ++i) {
    for (int j=0; j<4; ++j) {
      yy[i] += xx[j]*v[i][j];
    }
  }

  //assert (fabs(yy[3]-1.0) < 0.001);

  return Vector(yy[0], yy[1], yy[2]);
}

Vector Matrix4::getColumn(int j) const
{
  Vector ret;
  for (int i=0; i<3; ++i) ret[i] = v[i][j];
  return ret;
}

Translation4::Translation4(const Vector& t):
  Identity4()
{
  for (int i=0; i<3; ++i)
    v[i][3] = t[i];
}

Translation4::Translation4(double x, double y, double z):
  Identity4()
{
  v[0][3] = x;
  v[1][3] = y;
  v[2][3] = z;
}

Rotation3::Rotation3(double a, const Vector& v):
  Matrix3()
{
  double size_v = v.size();
  if (size_v < SMALL_VECTOR) {
    Matrix3::operator=(Identity3());
    return;
  }
  Vector u(v);
  u/=size_v;

  double s[3][3] = {
    {0.0, -u.z, u.y},
    {u.z, 0.0, -u.x},
    {-u.y, u.x, 0.0}
  };

  Matrix3 S(s);
  Matrix3 UU = transTime(u);
  Matrix3 M = UU + cos(a)*(Identity3() - UU) + sin(a)*S;
  Matrix3::operator=(M);
}

Scaling3::Scaling3(double x, double y, double z)
{
  v[0][0] = x;
  v[1][1] = y;
  v[2][2] = z;
}

Identity3::Identity3():
  Matrix3()
{
  v[0][0] = v[1][1] = v[2][2] = 1;
}

Identity4::Identity4():
  Matrix4()
{
  v[0][0] = v[1][1] = v[2][2] = v[3][3] = 1;
}

OrthoNorm3::OrthoNorm3():
  Matrix3()
{
  v[0][0] = v[1][1] = v[2][2] = 1;
}

OrthoNorm3::OrthoNorm3(const Matrix3& M):
  Matrix3(M)
{
}

void OrthoNorm3::correct()
{
  Vector u[3];
  for (int j=0; j<3; ++j) {
    u[j] = Vector(v[0][j], v[1][j], v[2][j]);
  }
  double u0_size = u[0].size();
  if (u0_size < SMALL_VECTOR) cerr<<"OrthoNorm3::correct: small u0"<<endl;
  u[0] /= u0_size;

  u[1] = (u[1] - (u[1] * u[0]) * u[0]);
  double u1_size = u[1].size();
  if (u1_size < SMALL_VECTOR) cerr<<"OrthoNorm3::correct: small u1"<<endl;
  u[1] /= u1_size;

  u[2] = u[0] ^ u[1];
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      v[i][j] = u[j][i];
    }
  }
}

Matrix3 transTime(const Vector& v)
{
  Matrix3 m;
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      m(i, j) = v[j] * v[i];
    }
  }
  return m;
}

Matrix4 inverse(const Matrix4& M)
{
  Matrix3 N;
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      N(i,j) = M(i,j);
    }
  };
  
    N = inverse(N);
  
  Translation4 T(-M(0, 3), -M(1,3), -M(2,3));
  return Matrix4(N)*T;
}

void updateOrient(math::Matrix3& orient, const math::Vector& rotation)
{
  math::Vector ws = orient*rotation;
  double Nd[3][3] = {
    {0.0, -ws.z, ws.y},
    {ws.z, 0.0, -ws.x},
    {-ws.y, ws.x, 0.0}
  };
  math::Matrix3 N(Nd);

  orient = orient + N*orient;
}


  }
  
}