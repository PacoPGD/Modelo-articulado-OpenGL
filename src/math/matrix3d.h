#ifndef _VIRTUA_MATRIX3D_
#define _VIRTUA_MATRIX3D_
#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include "transform3d.h"
#include "point3d.h"

using namespace std;

namespace virtua {
namespace math {
  
#define PI 3.14159265358979
  
/**\brief Represents a 4x4 matrix for 3D transformations
*/
class  Matrix3D
{
public:
    /**
    */
    Matrix3D();

    /**
    */
    ~Matrix3D();

    /**
    */
    Matrix3D(const Matrix3D &M);
    /**
    */
    Matrix3D(Transform3D T);
    /**
    */
    Matrix3D& operator=(const Matrix3D &M);

    /** Resets the amtrix
    */
    void reset();
    /** Returns the scale factor of the matrix.
     */ 
    float getScaleX();
    float getScaleY();
    float getScaleZ();
    /**Sets the transformation matrix from the one passed
    */
    void setMatrix(float M[16]);
    /**Sets the transformation matrix from the one passed in column-major order
    */
    void setMatrixCMO(float M[16]);
    void setMatrixCMO(double M[16]);
    /**Gets the transformation matrix in row-major order
    */
    void getMatrix(float MT[16]);
    /**Gets the transformation matrix in column-major order
    */
    void getMatrixCMO(float MT[16]);
    /**Transform the point passed
    */
    void transform(float &X,float &Y,float &Z);

    /**Transform the array passed
    */
    void transform(float *XYZ,int nPoints);

    /**Transform the array passed. The array elements are 3D points in homogeneous coordinates
    */
    void transform4(float *XYZH,int nPoints);


    /**Transform the array passed. The array elements are 3D points in homogeneous coordinates
    */
    void transform(Point3D<float> *points,int nPoints);
    void transform(Point3D<float> *in,int nPoints,Point3D<float> *out);
    /**Transform the array passed. The array elements are 3D points in homogeneous coordinates
    */
    void transformSSE(Point3D<float> *in,int nPoints,Point3D<float> *out);
    /**Transform ony the rotation tothe array passed. The array elements are 3D points in homogeneous coordinates
    */
    void transform_onlyrot(Point3D<float> *in,int nPoints,Point3D<float> *out);

    /**Transform the array passed. The array elements are 3D points in homogeneous coordinates
    */
    void transform(const Point3D<float> &in,Point3D<float> &out);

    /**Makes this the identity matrix
    */
    void setIdentity();
    /** Copies the translation of the matrix passed for the self-rotation
     */
    void copyTranslation(const Matrix3D& m);
    /**Adds a rotation in the X axis to the current matrix
    */
    void  addXRotationDeg(float angle);
    /**Adds a rotation in the Y axis to the current matrix
    */
    void  addYRotationDeg(float angle);
    /**Adds a rotation in the Z axis to the current matrix
    */
    void  addZRotationDeg(float angle);
    /**Adds a self-rotation in the X axis to the current matrix
    */
    void  addXSelfRotationDeg(float angle);
    /**Adds a self-rotation in the Y axis to the current matrix
    */
    void  addYSelfRotationDeg(float angle);
    /**Adds a self-rotation in the Z axis to the current matrix
    */
    void  addZSelfRotationDeg(float angle);

    /**Adds a rotation in the X axis to the current matrix
    */
    void  addXRotation(float angleRad);
    /**Adds a rotation in the Y axis to the current matrix
    */
    void  addYRotation(float angleRad);
    /**Adds a rotation in the Z axis to the current matrix
    */
    void  addZRotation(float angleRad);
    /**Adds a self-rotation in the X axis to the current matrix
    */
    void  addXSelfRotation(float angleRad);
    /**Adds a self-rotation in the Y axis to the current matrix
    */
    void  addYSelfRotation(float angleRad);
    /**Adds a self-rotation in the Z axis to the current matrix
    */
    void  addZSelfRotation(float angleRad);

    /**Extracts the axis (vx,vy,vz) and angle of rotation from the rotation matrix
    */
    void getAxisOfRotation(float &angle,Point3Df &axis);

    /**Adds a translation
    */
    void  addTranslation(float tx,float ty,float tz);

    /**set a translation values
    */
    void  setTranslation(float tx,float ty,float tz);
    /**Adds a scale factor
     */
    void addScale(float sx,float sy,float sz);
    /**Multiplication by a 3d point
    */
    Point3D<float> operator*(  Point3D<float>  v);
    /**
      */
    friend Point3D<float> operator*(  Point3D<float> &p1,   Matrix3D &M)
    {
        Point3D<float> ret;
        ret[0]= p1[0]*M(0,0) +p1[1] *M(1,0) +p1[2] *M(2,0);
        ret[1]= p1[0]*M(0,1) +p1[1] *M(1,1) +p1[2] *M(2,1);
        ret[2]= p1[0]*M(0,2) +p1[1] *M(1,2) +p1[2] *M(2,2);
        return ret;
    }

    /** Ostream operator
    */
    friend ostream& operator<<(ostream&str,Matrix3D &M)
    {
        str.write((char*)&M._leftHanded,sizeof(M._leftHanded));
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
                str.write((char*)&M.M[i*4+j],sizeof(float));
        return str;
    }
    /** Operator
    */
    Matrix3D operator*(const Matrix3D &);

    /** Istream operator
    */
    friend istream& operator>>(istream&str,Matrix3D &M)
    {
        str.read((char*)&M._leftHanded,sizeof(M._leftHanded));
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
                str.read((char*)&M.M[i*4+j],sizeof(float));
        return str;
    }


    string str()
    {
        stringstream str;
        for (int i=0;i<4;i++)
            for (int j=0;j<4;j++)
                str<<  M[i*4+j]<<" ";
        str<<endl;
        return str.str();

    }

    /**Prints this matrix
    */
    void print();
    /** sets the indicated position with the value specified
    */
    void set(int r,int c,float val);
    /** sets the indicated position with the value specified
    */
    float get(int r,int c);
    /**Access operator
    */
    float& operator()(int r,int c);

    /**
    */
    void setLeftHanded() {
        _leftHanded=true;
    }
    /**
    */
    void setRightHanded() {
        _leftHanded=false;
    }
    /**Inverts this matrix by transposing it
    */
    void invert();
private:
  float RadtoDeg(float angle);
  float DegtoRad(float angle);
/*    float *M;// __attribute__((aligned(16)));*/
  float M[16] ;//__attribute__((aligned(16)));
  float auxX,auxY,auxZ;
  bool _leftHanded;//indicates if the matrix is left handed, otherwise is righthanded
  float _sx;
  float _sy;
  float _sz;
  float _tx;
  float _ty;
  float _tz;
};// __attribute__((aligned(16)));
}
}
#endif
