#ifndef _VIRTUA_POINT3D_
#define _VIRTUA_POINT3D_
#include <iostream> 
using namespace std;
namespace virtua{
/**\brief 3d vector in homogeneous coordinates
*/
namespace math{
template<typename T>
struct Point3D
{ 
  //
  Point3D(){xyzh[0]=xyzh[1]=xyzh[2]=0;xyzh[3]=1;}
  //
  Point3D(const T & x,const T & y,const T & z,const T & h=1){
    xyzh[0]=x;xyzh[1]=y;xyzh[2]=z;xyzh[3]=h;
  }
  //
  Point3D(const Point3D &V){ xyzh[0]=V.xyzh[0];xyzh[1]=V.xyzh[1];xyzh[2]=V.xyzh[2];xyzh[3]=V.xyzh[3]; }
  //
  T& operator[](int i){return xyzh[i];}
  //
  T operator[](int i)const{return xyzh[i];}
  //
  Point3D& operator=(const T& val){xyzh[0]=xyzh[1]=xyzh[2]=val;xyzh[3]=1;return *this;}
  //
  bool operator==(const Point3D&p)const{return (p.xyzh[0]==xyzh[0] && p.xyzh[1]==xyzh[1] && p.xyzh[2]==xyzh[2] && p.xyzh[3]==xyzh[3]); }
  //
  Point3D operator*(const T& val)const{return Point3D(xyzh[0]*val,xyzh[1]*val,xyzh[2]*val);}
  //
  Point3D operator+(const Point3D &V)const{return Point3D(xyzh[0] +V.xyzh[0],xyzh[1]+V.xyzh[1],xyzh[2] +V.xyzh[2]);}
  //
  Point3D operator-(const Point3D &V)const{return Point3D(xyzh[0] -V.xyzh[0],xyzh[1]-V.xyzh[1],xyzh[2] -V.xyzh[2]);}
  //
  Point3D& operator+=(const Point3D &V){ xyzh[0]+=V.xyzh[0];xyzh[1]+= V.xyzh[1];xyzh[2]+=V.xyzh[2]; return *this;}
  //
  Point3D& operator/=(const T &v){ xyzh[0]/=v;xyzh[1]/=v;xyzh[2]/=v;return *this;}
  //
  Point3D& operator*=(const T &v){ xyzh[0]*=v;xyzh[1]*=v;xyzh[2]*=v;return *this;}

  Point3D operator/(const T &v){ Point3D res;res.xyzh[0]=xyzh[0]/v;res.xyzh[1]=xyzh[1]/v;res.xyzh[2]=xyzh[2]/v;return res;}

//returns a  normalized version of this
  Point3D normalize(){
	Point3D v;
	T mod=sqrt(xyzh[0]*xyzh[0] + xyzh[1]*xyzh[1]+xyzh[2]*xyzh[2]);
	v.xyzh[0]=xyzh[0]/mod;
	v.xyzh[1]=xyzh[1]/mod;
	v.xyzh[2]=xyzh[2]/mod;
	return v;
   }
  /**Returtns the vector modulus
  */
  T mod()const{return sqrt(xyzh[0]*xyzh[0] + xyzh[1]*xyzh[1]+xyzh[2]*xyzh[2]);}
  /**Returtns the  vector modulus pow 2
  */
  T mod_pow2()const{return xyzh[0]*xyzh[0] + xyzh[1]*xyzh[1]+xyzh[2]*xyzh[2];}

  /**Returns the distance of this point to the one passed
  */
  float distance(const Point3D &V){return sqrt( (xyzh[0]-V.xyzh[0])*(xyzh[0]-V.xyzh[0])+(xyzh[1]-V.xyzh[1])*(xyzh[1]-V.xyzh[1])+(xyzh[2]-V.xyzh[2])*(xyzh[2]-V.xyzh[2]));}

  //
  friend ostream & operator<<(ostream &str,const Point3D &V){
      str<<V.xyzh[0]<<" "<<V.xyzh[1]<<" "<<V.xyzh[2]<<" "<<V.xyzh[3];
      return str;
  }
  //
  friend istream & operator>>(istream &str, Point3D &V){
      str>>V.xyzh[0]>>V.xyzh[1]>>V.xyzh[2]>>V.xyzh[3];
      return str;
  }
  
 //dot product
 T dot(Point3D<T> b){
    return xyzh[0]*b.xyzh[0]+xyzh[1]*b.xyzh[1]+xyzh[2]*b.xyzh[2];
 }

 
 Point3D<T> cross(Point3D<float> b){
  return Point3D<T>( (xyzh[1]*b.xyzh[2]- xyzh[2]*b.xyzh[1]),
		     (xyzh[2]*b.xyzh[0]- xyzh[0]*b.xyzh[2]),
		     (xyzh[0]*b.xyzh[1]- xyzh[1]*b.xyzh[0]));
  
	
/*x^^(u_yv_z-u_zv_y)+y^^(u_zv_x-u_xv_z)+z^^(u_xv_y-u_yv_x),*/
	/*  a2b3 − a3b2) i + (a3b1 − a1b3) j + (a1b2 − a2b1) */
 }
 
 /** 3D Distance from a point to a segment
    * Returns t=0 if distance of p1 to its corresponding perpendicular point in (s1,s2) is computed.
    * Returns t=1 if distance of p1 to s1 is computed.
    * Returns t=2 if distance of p1 to s2 is computed.
    */
    float distancePointSegment(Point3D<T>& s1, Point3D<T>& s2, int& t){
      Point3D<T> v=s2-s1;
      Point3D<T> w=(*this)-s1;
      
      T c1=w.dot(v);
      if(c1<=0){
	  t=1;
	  return this->distance(s1);
      }
      T c2=v.dot(v);
      if(c2<=c1){
	  t=2;
	  return this->distance(s2);
      }
      t=0;
      float b=(float)c1/c2;
      Point3D<float> pb=s1+v*b;
      return this->distance(pb);
    }
    
    /** 3D Distance from a point to a segment
    * Returns t=0 if distance of p1 to its corresponding perpendicular point in (s1,s2) is computed.
    * Returns t=1 if distance of p1 to s1 is computed.
    * Returns t=2 if distance of p1 to s2 is computed.
    * Avoids computing the distance if t=1 or t=2.
    */
    float distancePerpendicularPointSegment(Point3D<T>& s1, Point3D<T>& s2, int& t){
      Point3D<T> v=s2-s1;
      Point3D<T> w=(*this)-s1;
      
      T c1=w.dot(v);
      if(c1<=0){
	  t=1;
	  return 0.0;
      }
      T c2=v.dot(v);
      if(c2<=c1){
	  t=2;
	  return 0.0;
      }
      t=0;
      float b=(float)c1/c2;
      Point3D<float> pb=s1+v*b;
      return this->distance(pb);
    }
 
  //vector
  T xyzh[4];
};


typedef Point3D<float> Point3Df;


};
};
#endif
