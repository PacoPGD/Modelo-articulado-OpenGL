
#include "intersections.hh"


#include <math.h>
#include <stdio.h>

#define X 0
#define Y 1
#define Z 2

#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2];

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

namespace virtua{
  
  namespace math{

  
int planeBoxOverlap(double normal[3],double d, double maxbox[3])
{
  int q;
  double vmin[3],vmax[3];
  for(q=X;q<=Z;q++)
  {
    if(normal[q]>0.0f)
    {
      vmin[q]=-maxbox[q];
      vmax[q]=maxbox[q];
    }
    else
    {
      vmin[q]=maxbox[q];
      vmax[q]=-maxbox[q];
    }
  }
  if(DOT(normal,vmin)+d>0.0f) return 0;
  if(DOT(normal,vmax)+d>=0.0f) return 1;

  return 0;
}


/*======================== X-tests ========================*/
#define AXISTEST_X01(a, b, fa, fb)             \
    p0 = a*v0[Y] - b*v0[Z];                    \
    p2 = a*v2[Y] - b*v2[Z];                    \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_X2(a, b, fa, fb)              \
    p0 = a*v0[Y] - b*v0[Z];                    \
    p1 = a*v1[Y] - b*v1[Z];                    \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
#define AXISTEST_Y02(a, b, fa, fb)             \
    p0 = -a*v0[X] + b*v0[Z];                   \
    p2 = -a*v2[X] + b*v2[Z];                       \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Y1(a, b, fa, fb)              \
    p0 = -a*v0[X] + b*v0[Z];                   \
    p1 = -a*v1[X] + b*v1[Z];                       \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
    if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/

#define AXISTEST_Z12(a, b, fa, fb)             \
    p1 = a*v1[X] - b*v1[Y];                    \
    p2 = a*v2[X] - b*v2[Y];                    \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
    if(min>rad || max<-rad) return 0;

#define AXISTEST_Z0(a, b, fa, fb)              \
    p0 = a*v0[X] - b*v0[Y];                \
    p1 = a*v1[X] - b*v1[Y];                    \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
    if(min>rad || max<-rad) return 0;

int triBoxOverlap(double boxcenter[3],double boxhalfsize[3],double triverts[3][3])
{

  /*    use separating axis theorem to test overlap between triangle and box */
  /*    need to test for overlap in these directions: */
  /*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
  /*       we do not even need to test these) */
  /*    2) normal of the triangle */
  /*    3) crossproduct(edge from tri, {x,y,z}-directin) */
  /*       this gives 3x3=9 more tests */
   double v0[3],v1[3],v2[3];
   double min,max,d,p0,p1,p2,rad,fex,fey,fez;
   double normal[3],e0[3],e1[3],e2[3];

   /* This is the fastest branch on Sun */
   /* move everything so that the boxcenter is in (0,0,0) */
   SUB(v0,triverts[0],boxcenter);
   SUB(v1,triverts[1],boxcenter);
   SUB(v2,triverts[2],boxcenter);

   /* compute triangle edges */
   SUB(e0,v1,v0);      /* tri edge 0 */
   SUB(e1,v2,v1);      /* tri edge 1 */
   SUB(e2,v0,v2);      /* tri edge 2 */

   /* Bullet 3:  */
   /*  test the 9 tests first (this was faster) */
   fex = fabs(e0[X]);
   fey = fabs(e0[Y]);
   fez = fabs(e0[Z]);
   AXISTEST_X01(e0[Z], e0[Y], fez, fey);
   AXISTEST_Y02(e0[Z], e0[X], fez, fex);
   AXISTEST_Z12(e0[Y], e0[X], fey, fex);

   fex = fabs(e1[X]);
   fey = fabs(e1[Y]);
   fez = fabs(e1[Z]);
   AXISTEST_X01(e1[Z], e1[Y], fez, fey);
   AXISTEST_Y02(e1[Z], e1[X], fez, fex);
   AXISTEST_Z0(e1[Y], e1[X], fey, fex);

   fex = fabs(e2[X]);
   fey = fabs(e2[Y]);
   fez = fabs(e2[Z]);
   AXISTEST_X2(e2[Z], e2[Y], fez, fey);
   AXISTEST_Y1(e2[Z], e2[X], fez, fex);
   AXISTEST_Z12(e2[Y], e2[X], fey, fex);

   /* Bullet 1: */
   /*  first test overlap in the {x,y,z}-directions */
   /*  find min, max of the triangle each direction, and test for overlap in */
   /*  that direction -- this is equivalent to testing a minimal AABB around */
   /*  the triangle against the AABB */

   /* test in X-direction */
   FINDMINMAX(v0[X],v1[X],v2[X],min,max);
   if(min>boxhalfsize[X] || max<-boxhalfsize[X]) return 0;

   /* test in Y-direction */
   FINDMINMAX(v0[Y],v1[Y],v2[Y],min,max);
   if(min>boxhalfsize[Y] || max<-boxhalfsize[Y]) return 0;

   /* test in Z-direction */
   FINDMINMAX(v0[Z],v1[Z],v2[Z],min,max);
   if(min>boxhalfsize[Z] || max<-boxhalfsize[Z]) return 0;

   /* Bullet 2: */
   /*  test if the box intersects the plane of the triangle */
   /*  compute plane equation of triangle: normal*x+d=0 */
   CROSS(normal,e0,e1);
   d=-DOT(normal,v0);  /* plane eq: normal.x+d=0 */
   if(!planeBoxOverlap(normal,d,boxhalfsize)) return 0;

   return 1;   /* box and triangle overlaps */
}

bool intersect(AxisAlignedBox b1, AxisAlignedBox b2)
{
  Vector d = b1.getCenter()-b2.getCenter();
  double s1[3];
  double s2[3];
  b1.getEdgeSizes(s1);
  b2.getEdgeSizes(s2);

  for (int i=0; i<3; ++i) {
    if (fabs(d[i]) < 0.5*(s1[i] + s2[i])) return true;
  }
  return false;
}

//FIXME: this algorithm is not correct :(
bool intersect(AxisAlignedBox aabox, Box box, bool try_other)
{
  // Check if box is one side of one of aabox's planes
  double sizes[3];
  aabox.getEdgeSizes(sizes);
  int planes = 63;   // Bitfield keeping track of the planes separating the two boxes
  Vector center = aabox.getCenter();
  double x1 = center.x - sizes[0]/2.0;
  double x2 = center.x + sizes[0]/2.0;
  double y1 = center.y - sizes[1]/2.0;
  double y2 = center.y + sizes[1]/2.0;
  double z1 = center.z - sizes[2]/2.0;
  double z2 = center.z + sizes[2]/2.0;

  Vector vertices[8];
  box.getVertices(vertices);

  for (int i=0; planes && i<8; ++i) {
    const Vector& v(vertices[i]);
    bool inside = true;
    if (v.x >= x1) planes &= ~1; else inside = false;
    if (v.x <= x2) planes &= ~2; else inside = false;
    if (v.y >= y1) planes &= ~4; else inside = false;
    if (v.y <= y2) planes &= ~8; else inside = false;
    if (v.z >= z1) planes &= ~16; else inside = false;
    if (v.z <= z2) planes &= ~32; else inside = false;

    // v is inside aabox
    if (inside) return true;
  }
  // There is a plane separating the two boxes, hence they do not intersect
  if (planes) return false;
  // We tried all possible planes, could not find one, hence boxes intersect
  if (!try_other) return true;
  
  // Try once more when swaping boxes.
  Matrix3 M = box.getOrient().transpose();
  Box box2(aabox.getCenter(), M*Vector(sizes[0]/2.0,0,0), M*Vector(0,sizes[1]/2.0,0), M*Vector(0,0,sizes[2]/2.0));
  box.getEdgeSizes(sizes);
  AxisAlignedBox aabox2(box.getCenter(), sizes[0]/2.0, sizes[1]/2.0, sizes[2]/2.0);
  return intersect(aabox2, box2, false);
}

bool intersect(Plane plane, AxisAlignedBox box)
{
  double normal[3];
  const Vector& N(plane.normal);
  normal[0] = N.x;
  normal[1] = N.y;
  normal[2] = N.z;

  double maxbox[3];
  double sizes[3];
  box.getEdgeSizes(sizes);
  for (int i=0; i<3; ++i) maxbox[i] = sizes[i]/2.0;

  return planeBoxOverlap(normal, plane.d, maxbox) != 0;
}

bool intersect(Triangle triangle, AxisAlignedBox box)
{
  double triverts[3][3];
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      triverts[i][j] = triangle.p[i][j];
    }
  }

  double boxcenter[3];
  for (int i=0; i<3; ++i) {
    boxcenter[i] = box.getCenter()[i];
  }

  double boxhalfsize[3];
  double sizes[3];
  box.getEdgeSizes(sizes);
  for (int i=0; i<3; ++i) {
    boxhalfsize[i] = sizes[i]/2.0;
  }

  return triBoxOverlap(boxcenter, boxhalfsize, triverts) != 0;
}

bool intersect(Plane plane, Box box)
{
  Matrix3 M = box.getOrient().transpose();
  plane.translate(-box.getCenter());
  plane.rotate(M);
  double normal[3];
  for (int i=0; i<3; ++i) normal[i] = plane.normal[i];

  double maxbox[3];
  double sizes[3];
  box.getEdgeSizes(sizes);
  for (int i=0; i<3; ++i) maxbox[i] = sizes[i]/2.0;

  return planeBoxOverlap(normal, plane.d, maxbox) != 0;
}

bool intersect(Triangle triangle, Box box)
{
  Matrix3 M = box.getOrient().transpose();
  triangle.translate(-box.getCenter());
  triangle.rotate(M);

  double triverts[3][3];
  for (int i=0; i<3; ++i) {
    for (int j=0; j<3; ++j) {
      triverts[i][j] = triangle.p[i][j];
    }
  }

  double boxcenter[3];
  for (int i=0; i<3; ++i) boxcenter[i] = 0.0;

  double boxhalfsize[3];
  double sizes[3];
  box.getEdgeSizes(sizes);
  for (int i=0; i<3; ++i) {
    boxhalfsize[i] = sizes[i]/2.0;
  }

  return triBoxOverlap(boxcenter, boxhalfsize, triverts) != 0;
}

bool intersect(Mesh mesh, AxisAlignedBox box)
{
  const std::vector<Mesh::Face>* faces = mesh.getFaces();
  const std::vector<Vector>* vertices = mesh.getVertices();
  
  //TODO: use an octree to partition faces of the mesh
  for (std::vector<Mesh::Face>::const_iterator face_it = faces->begin(); face_it != faces->end(); ++face_it) {
    Triangle t(vertices->at(face_it->idxs[0]), vertices->at(face_it->idxs[1]), vertices->at(face_it->idxs[2]));
    if (intersect(t, box)) return true;
  }
  return false;
}

bool intersect(Mesh mesh, Box box)
{
  const std::vector<Mesh::Face>* faces = mesh.getFaces();
  const std::vector<Vector>* vertices = mesh.getVertices();
  
  //TODO: use an octree to partition faces of the mesh
  for (std::vector<Mesh::Face>::const_iterator face_it = faces->begin(); face_it != faces->end(); ++face_it) {
    Triangle t(vertices->at(face_it->idxs[0]), vertices->at(face_it->idxs[1]), vertices->at(face_it->idxs[2]));
    if (intersect(t, box)) return true;
  }
  return false;
}

bool intersect(Plane p, Ray r)
{
  if (r.isFinite()) {
    Vector res;
    return intersect(p, r.getOrigin(), r.getOrigin() + r.getLength()*r.getDirection(), res);
  }
  else {
    Vector res;
    double d;
    return intersectRay(p, r.getOrigin(), r.getDirection(), res, d);
  }  
}

bool intersect(Triangle t, Ray r)
{
  Vector v;
  double d;
  bool res = t.intersectRay(r.getOrigin(), r.getDirection(), v, d);
  if (!res) return false;
  if (d < 0.0) return false;
  if (r.isFinite() && d > r.getLength()) return false;
  return true;
}

bool intersect(Mesh m, Ray r, double* dist)
{
  const std::vector<Vector>* vertices = m.getVertices();
  const std::vector<Mesh::Face>* faces = m.getFaces();
  bool found = false;
  for (std::vector<Mesh::Face>::const_iterator face_it = faces->begin(); face_it != faces->end(); ++face_it) {
    Triangle tri(vertices->at(face_it->idxs[0]), vertices->at(face_it->idxs[1]), vertices->at(face_it->idxs[2]));
    Vector v;
    double d;
    if (tri.intersectRay(r.getOrigin(), r.getDirection(), v, d)) {
      if (dist == 0) return true;
      if (*dist > d && d >= 0.0) *dist = d;
      found = true;
    }
  } 
  return found;
}

  }
  
}