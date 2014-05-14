
#include "ray.hh"

#include <limits>

namespace virtua{

namespace math {

Ray::Ray():
  origin(0,0,0), dir(1,0,0), length(-1.0)
{
}

void Ray::transform(const Matrix4& M)
{
  origin = M*origin;
  dir = M*dir;
  double s = dir.size();
  assert(s>=SMALL_VECTOR);
  dir /= s;
  if (isFinite()) {
    length = length * s;
  }
}

double computeDist(const Ray& ray, const Vector& v)
{
  double ret = std::numeric_limits<double>::max();

  Vector v2 = v - ray.getOrigin();
  double proj = v2*ray.getDirection();

  if (proj < 0)
    return ret;

  if (ray.isFinite() && proj > ray.getLength())
    return ret;

  return (v2 - proj * ray.getDirection()).size();
}

}

}
