#ifndef _VIRTUA_OBJ_3DOBJECT_
#define _VIRTUA_OBJ_3DOBJECT_

#include "object3d.h"
extern "C" {
#include "glm.h"
}

namespace virtua{
  
  namespace objects{

    namespace formats{

/**\brief This class represents an OBJ three-dimensional virtual object.
*/
class OBJ: public Object3D{
public:
   /**
    */
   OBJ();
   /** Releases the memory.
    */
   ~OBJ();
   /** Loads the object from the specified file.
    */
   void load(string file) throw (VException);
    /** Saves the object to the specified file.
    */
   void save(string file);
   /** Draws the object.
   */
   void draw();
   /** Ignores or not the .OBJ materials when drawing the object.
   */
   void enableMaterials(bool im);
   /** Enables or not the predefined color of the object.
    */
   void enableColor(bool color);
   /** Disables or not the MTL (material and color) file.
    */
   void disableMTL(bool mtl);
   
   
protected:
  
  
  
  GLMmodel* _3dmodel;
  bool _loaded;
  bool _mat;
  bool _mtl;
  bool _col;
  bool _first;
  GLuint _list;
  
};

  }
  
}

}

#endif