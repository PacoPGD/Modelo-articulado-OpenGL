#include "ray.hh"
#include "plane.hh"
#include "intersections.hh"

#include <iostream>

using namespace virtua::math;
using namespace std;

int main(){
 
  Vector o(0.0,-5.0,0.0);
  Vector d(0.0,2.0,0.0);
  
  Ray r;
  r.setOrigin(o);
  r.setDirection(d);
  
  cout << r.getDirection().x << " " << r.getDirection().y << " " << r.getDirection().z << endl;
  
  Plane p(Vector(1.0,0.0,1.0),Vector(-2.0,0.0,-3.0),Vector(5.0,0.0,8.0));
  
  Vector result;
  double dist;
  
  if(intersectRay(p,o,d,result,dist)){
    cout << dist << endl;
    cout << result.x << " " << result.y << " " << result.z << endl;
  }
  
  return EXIT_SUCCESS;
}