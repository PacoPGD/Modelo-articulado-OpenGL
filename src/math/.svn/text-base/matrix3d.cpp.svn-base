#include "matrix3d.h"
#include <cstring>
#include "gualloc.h"
 #include <pmmintrin.h>
/*#ifdef NDEBUG
 #define SSE3
 #endif*/
using namespace std;
namespace virtua {

namespace math {
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D::Matrix3D()
{
    _leftHanded=false;
//     M=(float*)gu_alloc(16*sizeof(float));
    setIdentity();
   
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D::Matrix3D(const Matrix3D &Ma)
{
//     M=(float*)gu_alloc(16*sizeof(float));
    *this=Ma;
    _sx=Ma._sx;
    _sy=Ma._sy;
    _sz=Ma._sz;
    _tx=Ma._tx;
    _ty=Ma._ty;
    _tz=Ma._tz;
    
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D::Matrix3D(Transform3D T)
{
//     M=(float*)gu_alloc(16*sizeof(float));
    setIdentity();
    addXRotation(T.rx);
    addYRotation(T.ry);
    addZRotation(T.rz);
    M[3]=T.tx;
    M[7]=T.ty;
    M[11]=T.tz;
    _sx=_sy=_sz=1.0;
    _tx=T.tx;
    _ty=T.ty;
    _tz=T.tz;
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D::~Matrix3D()
{
//   gu_free(M);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::getScaleX(){
  return _sx;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::getScaleY(){
  return _sy;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::getScaleZ(){
  return _sz;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Point3D<float> Matrix3D::operator*(  Point3D<float>  v)
{
    Point3D<float> res;
    res[0]= M[0]*v[0] + M[1]*v[1] + M[2]*v[2] +M[3]*v[3];
    res[1]= M[4]*v[0] + M[5]*v[1] + M[6]*v[2] +M[7]*v[3];
    res[2]= M[8]*v[0] + M[9]*v[1] + M[10]*v[2] +M[11]*v[3];
    return res;
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D& Matrix3D::operator=(const Matrix3D &Ma)
{
    _leftHanded=Ma._leftHanded;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            M[i*4+j]=Ma.M[i*4+j];
    _sx=Ma._sx;
    _sy=Ma._sy;
    _sz=Ma._sz;
    _sx=Ma._tx;
    _sy=Ma._ty;
    _sz=Ma._tz;
    
    return *this;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
Matrix3D Matrix3D::operator*(const Matrix3D &b)
{
    Matrix3D aux;


    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            aux.M[i*4+j]=0;
            for (int k=0;k<4;k++) {
                aux.M[i*4+j]+=M[i*4+k]*b.M[k*4+j];
            }
        }
    }
    aux._sx=_sx*b._sx;
    aux._sy=_sy*b._sy;
    aux._sz=_sz*b._sz;
    aux._tx=_tx+b._tx;
    aux._ty=_ty+b._ty;
    aux._tz=_tz+b._tz;
    return aux;
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::print()
{
    cout<<"-------------------"<<endl;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++)
            cout<<M[i*4+j]<<" ";
        cout<<endl;
    }
    cout<<"-------------------"<<endl;
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::reset()
{
    setIdentity();
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform(float &X,float &Y,float &Z)
{
    auxX= M[0]*X + M[1]*Y + M[2]*Z +M[3];
    auxY= M[4]*X + M[5]*Y + M[6]*Z +M[7];
    auxZ= M[8]*X + M[9]*Y + M[10]*Z +M[11];
    X=auxX;
    Y=auxY;
    Z=auxZ;
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform(float *XYZ,int nPoints)
{
    for (int i=0;i<nPoints;i++,XYZ+=3) {
        auxX= M[0]*XYZ[0] + M[1]*XYZ[1] + M[2]*XYZ[2] +M[3];
        auxY= M[4]*XYZ[0] + M[5]*XYZ[1] + M[6]*XYZ[2] +M[7];
        auxZ= M[8]*XYZ[0] + M[9]*XYZ[1] + M[10]*XYZ[2] +M[11];
        XYZ[0]=auxX;
        XYZ[1]=auxY;
        XYZ[2]=auxZ;
    }
}

/**Transform the array passed. The array elements are 3D points in homogeneous coordinates
*/
void Matrix3D::transform4(float *XYZ,int nPoints)
{
//Do not improve
// #ifdef SSE3
//   //if data is aligned do it
//   assert(gu_isaligned(XYZ));
//   assert(gu_isaligned(this));
//   assert(gu_isaligned(M));
//   __m128 l1,l2,l3,l4; //lines of the matrix
//   l1=_mm_load_ps(M); //load line1
//   l2=_mm_load_ps(M+4); //load  line2
//   l3=_mm_load_ps(M+8); //load  line3
//   l4=_mm_load_ps(M+12); //load  line4
//
//   __m128 in_out,a,b,c,d;
//
//   for(int i=0;i<nPoints;i++,XYZ+4){
//       in_out=_mm_load_ps(XYZ); //load point
//       //multiply by matrix
//       a=_mm_mul_ps(l1,in_out);
//       b=_mm_mul_ps(l2,in_out);
//       c=_mm_mul_ps(l3,in_out);
//       d=_mm_mul_ps(l4,in_out);
//       a=_mm_hadd_ps(a,b);
//       b=_mm_hadd_ps(c,d);
//       in_out=_mm_hadd_ps(a,b);
//       _mm_store_ps(XYZ,in_out);
//   }
// #else
    for (int i=0;i<nPoints;i++,XYZ+=4) {
        auxX= M[0]*XYZ[0] + M[1]*XYZ[1] + M[2]*XYZ[2] +M[3];
        auxY= M[4]*XYZ[0] + M[5]*XYZ[1] + M[6]*XYZ[2] +M[7];
        auxZ= M[8]*XYZ[0] + M[9]*XYZ[1] + M[10]*XYZ[2] +M[11];
        XYZ[0]=auxX;
        XYZ[1]=auxY;
        XYZ[2]=auxZ;
    }
// #endif
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform(Point3D<float>  *points,int nPoints)
{
    for (int i=0;i<nPoints;i++,points++) {
        auxX= M[0]* points->xyzh[0] + M[1]*  points->xyzh[1] + M[2]*  points->xyzh[2] +M[3];
        auxY= M[4]*  points->xyzh[0] + M[5]*  points->xyzh[1] + M[6]*  points->xyzh[2] +M[7];
        auxZ= M[8]*  points->xyzh[0] + M[9]*  points->xyzh[1] + M[10]*  points->xyzh[2] +M[11];
        points->xyzh[0]=auxX;
        points->xyzh[1]=auxY;
        points->xyzh[2]=auxZ;
    }
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform(Point3D<float>  *points,int nPoints, Point3D<float> *points_o)
{
    Point3D<float>* points_output=points_o;
    for (int i=0;i<nPoints;i++,points++,points_output++) {
        points_output->xyzh[0]= M[0]* points->xyzh[0] + M[1]*  points->xyzh[1] + M[2]*  points->xyzh[2] +M[3];
        points_output->xyzh[1]= M[4]*  points->xyzh[0] + M[5]*  points->xyzh[1] + M[6]*  points->xyzh[2] +M[7];
        points_output->xyzh[2]= M[8]*  points->xyzh[0] + M[9]*  points->xyzh[1] + M[10]*  points->xyzh[2] +M[11];
    }
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transformSSE(Point3D<float> *in,int nPoints,Point3D<float> *out)
{
   
//in release mode, the speed up is around 1.3 compared to the version below
//in debug mode, the performance is much worse

// #ifdef SSE3
// cout<<"SSE3"<<endl;
  //if data is aligned do it
  assert(gu_isaligned(in));
  assert(gu_isaligned(out));

 
  float alig_M[16] __attribute__((aligned(16)));
  for(int i=0;i<16;i++)alig_M[i]=M[i];
  
  
  __m128 l1,l2,l3; //lines of the matrix
  l1=_mm_load_ps(alig_M); //load line1
  l2=_mm_load_ps(alig_M+4); //load  line2
  l3=_mm_load_ps(alig_M+8); //load  line3


  __m128 in_out,a,b,c,d;
  d= _mm_set_ps (1, 0, 0, 0);
   for(int i=0;i<nPoints;i++,in++,out++){
      in_out=_mm_load_ps((float*)in); //load point
      //multiply by matrix
      a=_mm_mul_ps(l1,in_out);
      b=_mm_mul_ps(l2,in_out);
      c=_mm_mul_ps(l3,in_out);
      a=_mm_hadd_ps(a,b);
      b=_mm_hadd_ps(c,d);
      in_out=_mm_hadd_ps(a,b);
      
       _mm_store_ps((float*)out,in_out);

  }
   
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform_onlyrot(Point3D<float> *in,int nPoints,Point3D<float> *out)
{
  
    assert(gu_isaligned(in));
  assert(gu_isaligned(out));

 
  float alig_M[16] __attribute__((aligned(16)));
  for(int i=0;i<16;i++)alig_M[i]=M[i];
  alig_M[3]=alig_M[7]=alig_M[11]=0;
  
  
  __m128 l1,l2,l3; //lines of the matrix
  l1=_mm_load_ps(alig_M); //load line1
  l2=_mm_load_ps(alig_M+4); //load  line2
  l3=_mm_load_ps(alig_M+8); //load  line3


  __m128 in_out,a,b,c,d;
  d= _mm_set_ps (1, 0, 0, 0);
   for(int i=0;i<nPoints;i++,in++,out++){
      in_out=_mm_load_ps((float*)in); //load point
      //multiply by matrix
      a=_mm_mul_ps(l1,in_out);
      b=_mm_mul_ps(l2,in_out);
      c=_mm_mul_ps(l3,in_out);
      a=_mm_hadd_ps(a,b);
      b=_mm_hadd_ps(c,d);
      in_out=_mm_hadd_ps(a,b);
      
       _mm_store_ps((float*)out,in_out);

  }
//     for (int i=0;i<nPoints;i++,in++,out++) {
//         out->xyzh[0]= M[0]* in->xyzh[0] + M[1]*  in->xyzh[1] + M[2]*  in->xyzh[2]  ;
//         out->xyzh[1]= M[4]*  in->xyzh[0] + M[5]*  in->xyzh[1] + M[6]*  in->xyzh[2] ;
//         out->xyzh[2]= M[8]*  in->xyzh[0] + M[9]*  in->xyzh[1] + M[10]*  in->xyzh[2];
//     } 
  
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::transform(const Point3D<float> &in,Point3D<float> &out)
{
    out[0]= M[0]* in[0] + M[1]*  in[1] + M[2]*  in[2] +M[3];
    out[1]= M[4]* in[0] + M[5]*  in[1] + M[6]*  in[2] +M[7];
    out[2]= M[8]* in[0] + M[9]*  in[1] + M[10]* in[2] +M[11];
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::setMatrix(float MT[16])
{
    memcpy(M,MT,sizeof(float)*16);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::setMatrixCMO(float MT[16])
{
  for(unsigned int i=0;i<4;i++)
    for(unsigned int j=0;j<4;j++)
        M[i+4*j]=MT[4*i+j];
}
void Matrix3D::setMatrixCMO(double MT[16])
{
  for(unsigned int i=0;i<4;i++)
    for(unsigned int j=0;j<4;j++)
        M[i+4*j]=(float)MT[4*i+j];
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::getMatrixCMO(float MT[16])
{
  for(unsigned int i=0;i<4;i++)
    for(unsigned int j=0;j<4;j++)
      MT[4*i+j]=M[i+4*j];
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::getMatrix(float MT[16])
{
  memcpy(MT,M,sizeof(float)*16);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addXRotation(float angleRad)
{
    float Maux[4][4];
    if (!_leftHanded) {
        Maux[0][0]=1;
        Maux[0][1]=0;
        Maux[0][2]=0;
        Maux[0][3]=0;
        Maux[1][0]=0;
        Maux[1][1]=cos(angleRad);
        Maux[1][2]=-sin(angleRad);
        Maux[1][3]=0;
        Maux[2][0]=0;
        Maux[2][1]=sin(angleRad);
        Maux[2][2]=cos(angleRad);
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    else {
        Maux[0][0]=1;
        Maux[0][1]=0;
        Maux[0][2]=0;
        Maux[0][3]=0;
        Maux[1][0]=0;
        Maux[1][1]=cos(angleRad);
        Maux[1][2]=sin(angleRad);
        Maux[1][3]=0;
        Maux[2][0]=0;
        Maux[2][1]=-sin(angleRad);
        Maux[2][2]=cos(angleRad);
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    float Maux2[4][4];


    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            float sum=0;
            for (int k=0;k<4;k++) {
                sum+=Maux[i][k]*M[k*4+j];
            }
            Maux2[i][j]=sum;
        }
    }


    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++)
            M[i*4+j]=Maux2[i][j];
    }
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addYRotation(float angleRad)
{
    float Maux[4][4];

    if (!_leftHanded) {
        Maux[0][0]=cos(angleRad);
        Maux[0][1]=0;
        Maux[0][2]=sin(angleRad);
        Maux[0][3]=0;
        Maux[1][0]=0;
        Maux[1][1]=1;
        Maux[1][2]=0;
        Maux[1][3]=0;
        Maux[2][0]=-sin(angleRad);
        Maux[2][1]=0;
        Maux[2][2]=cos(angleRad);
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    else {
        Maux[0][0]=cos(angleRad);
        Maux[0][1]=0;
        Maux[0][2]=-sin(angleRad);
        Maux[0][3]=0;
        Maux[1][0]=0;
        Maux[1][1]=1;
        Maux[1][2]=0;
        Maux[1][3]=0;
        Maux[2][0]=sin(angleRad);
        Maux[2][1]=0;
        Maux[2][2]=cos(angleRad);
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    float Maux2[4][4];


    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            float sum=0;
            for (int k=0;k<4;k++) {
                sum+=Maux[i][k]*M[k*4+j];
            }
            Maux2[i][j]=sum;
        }
    }

    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++)
            M[i*4+j]=Maux2[i][j];
    }
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addZRotation(float angleRad)
{
    float Maux[4][4];
    if (!_leftHanded) {
        Maux[0][0]=cos(angleRad);
        Maux[0][1]=-sin(angleRad);
        Maux[0][2]= 0;
        Maux[0][3]=0;
        Maux[1][0]=sin(angleRad);
        Maux[1][1]=cos(angleRad);
        Maux[1][2]=0;
        Maux[1][3]=0;
        Maux[2][0]=0;
        Maux[2][1]=0;
        Maux[2][2]=1;
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    else {
        Maux[0][0]=cos(angleRad);
        Maux[0][1]=sin(angleRad);
        Maux[0][2]= 0;
        Maux[0][3]=0;
        Maux[1][0]=-sin(angleRad);
        Maux[1][1]=cos(angleRad);
        Maux[1][2]=0;
        Maux[1][3]=0;
        Maux[2][0]=0;
        Maux[2][1]=0;
        Maux[2][2]=1;
        Maux[2][3]=0;
        Maux[3][0]=0;
        Maux[3][1]=0;
        Maux[3][2]=0;
        Maux[3][3]=1;
    }
    float Maux2[4][4];


    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            float sum=0;
            for (int k=0;k<4;k++) {
                sum+=Maux[i][k]*M[k*4+j];
            }
            Maux2[i][j]=sum;
        }
    }



    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++)
            M[i*4+j]=Maux2[i][j];
    }
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////

void Matrix3D::copyTranslation(const Matrix3D& m){
  _tx+=m._tx;
  _ty+=m._ty;
  _tz+=m._tz;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addXSelfRotation(float angleRad)
{
  float tx=_tx,ty=_ty,tz=_tz;
  addTranslation(-_tx,-_ty,-_tz);
  addXRotation(angleRad);
  addTranslation(tx,ty,tz);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addYSelfRotation(float angleRad)
{
  float tx=_tx,ty=_ty,tz=_tz;
  addTranslation(-_tx,-_ty,-_tz);
  addYRotation(angleRad);
  addTranslation(tx,ty,tz);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addZSelfRotation(float angleRad)
{
  float tx=_tx,ty=_ty,tz=_tz;
  addTranslation(-_tx,-_ty,-_tz);
  addZRotation(angleRad);
  addTranslation(tx,ty,tz);
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::RadtoDeg(float angle){
    return (angle*180)/PI;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::DegtoRad(float angle){
    return (angle*PI)/180.;
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void  Matrix3D::addXRotationDeg(float angle){
    addXRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void  Matrix3D::addYRotationDeg(float angle){
      addYRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void  Matrix3D::addZRotationDeg(float angle){
      addZRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void  Matrix3D::addXSelfRotationDeg(float angle){
    addXSelfRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void  Matrix3D::addYSelfRotationDeg(float angle){
      addYSelfRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////    
void  Matrix3D::addZSelfRotationDeg(float angle){
      addZSelfRotation(DegtoRad(angle));
}
//////////////////////////////////////////////
//
//
//////////////////////////////////////////////    
void  Matrix3D::addTranslation(float tx,float ty,float tz)
{

    M[3]+=tx;
    M[7]+=ty;
    M[11]+=tz;
    _tx+=tx;
    _ty+=ty;
    _tz+=tz;

}

void  Matrix3D::setTranslation(float tx,float ty,float tz)
{
    M[3]=tx;
    M[7]=ty;
    M[11]=tz;
    _tx=tx;
    _ty=ty;
    _tz=tz;
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::addScale(float sx,float sy,float sz)
{
  M[0]*=sx;
  M[1]*=sx;
  M[2]*=sx;
  M[3]*=sx;

  M[4]*=sy;
  M[5]*=sy;
  M[6]*=sy;
  M[7]*=sy;
  
  M[8]*=sz;
  M[9]*=sz;
  M[10]*=sz;
  M[11]*=sz;
  
  _sx*=sx;
  _sy*=sy;
  _sz*=sz;
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::set(int r,int c,float val)
{
    M[r*4+c]=val;
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float Matrix3D::get(int r,int c)
{
    return M[r*4+c];
}

//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
void Matrix3D::setIdentity()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            M[i*4+j]=0;
    for (int i=0;i<4;i++)
        M[i*4+i]=1;
     _sx=_sy=_sz=1.0;
    _tx=_ty=_tz=0.0;
}


//////////////////////////////////////////////
//
//
//////////////////////////////////////////////
float& Matrix3D::operator()(int r,int c)
{
    return M[r*4+c];
}

    //this code is not completely tested.
    //Information is extracted from (http://en.wikipedia.org/wiki/Rotation_matrix#Finding_the_rotation_matrix)
    // and http://en.wikipedia.org/wiki/Axis_angle#Exponential_map_from_so.283.29_to_SO.283.29
void Matrix3D::getAxisOfRotation(float &angle,Point3Df &axis) {
    double Trace=0;
    for (int f=0;f<4;f++)
        Trace+=(*this)(f,f);
    angle=acos((Trace-1.)/2.);
    float sin2=2.*sin(angle);
    axis[0]=((*this)(2,1)-(*this)(1,2))/(sin2);
    axis[1]=((*this)(0,2)-(*this)(2,0))/(sin2);
    axis[2]=((*this)(1,0)-(*this)(0,1))/(sin2);
    //alternative for the angle, more exact but with sign problems
    /*
    double x=Map(2,1)-Map(1,2);
    double y=Map(0,2)-Map(2,0);
    double z=Map(1,0)-Map(0,1);
    double hipyz=sqrt(y*y + z*z);
    double r=sqrt ( x*x + hipyz*hipyz);
       double Rangle2=atan2(r,Trace-1);
       */
}

void Matrix3D::invert()
{
  float auxM[16]; 
  
  //transpose rotation info
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++) 
	    auxM [j*4+i]=M[i*4+j];
	
	//copy
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++) 
	    M[i*4+j]=auxM [i*4+j];
	    
        //invert translation
	float Tx= -M[3];	
	float Ty= -M[4+3];	
	float Tz= -M[8+3];	
	float invTx=Tx*M[0]+Ty*M[1]+Tz*M[2];
	float invTy=Tx*M[4+0]+Ty*M[4+1]+Tz*M[4+2];
	float invTz=Tx*M[8+0]+Ty*M[8+1]+Tz*M[8+2];
	M[3]=invTx;
	M[4+3]=invTy;
	M[8+3]=invTz;
	
 
}
};

}
