#ifndef _VIRTUA_TRANSFORM3D_
#define _VIRTUA_TRANSFORM3D_
namespace virtua{
  namespace math{
/**\brief A 3d transform
*/
struct Transform3D
{
  /**Constructor
  */
  Transform3D(){rx=ry=rz=tx=ty=tz=0;}
  /**Constructor
  */
 
  Transform3D(float Tx,float Ty,float Tz,float Rx=0,float Ry=0,float Rz=0)
  {
    tx=Tx;ty=Ty;tz=Tz;
    rx=Rx;ry=Ry;rz=Rz;
  }

  float rx,ry,rz;
  float tx,ty,tz;
};
 }
}
#endif

