
#include "vertex.hh"
#include "vec2d.hh"

namespace virtua{

  namespace math{
  
bool cross(Vector p1, Vector d1, Vector p2, Vector d2)
{
  
  Vec2D pp1(p1.x, p1.z);
  Vec2D dd1(d1.x, d1.z);
  Vec2D pp2(p2.x, p2.z);
  Vec2D dd2(d2.x, d2.z);
  
  return segment_intersection(pp1, dd1, pp2, dd2);
}

  }
  
}