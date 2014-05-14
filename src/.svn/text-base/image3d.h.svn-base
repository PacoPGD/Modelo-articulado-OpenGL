#ifndef _VIRTUA_3DIMAGE_
#define _VIRTUA_3DIMAGE_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/gl.h>

#include "vobject.h"

namespace virtua{
  
  namespace objects{

/**\brief This class represents an image in a three-dimensional world.
*/
class Image3D: public VObject{
public:
   /**
    */
   Image3D();
   /** Releases the memory.
    */
   ~Image3D();
   /** Loads the object from the specified file.
    */
   void load(string file) throw (VException);
   /** Saves the object to the specified file.
    */
   void save(string file);
   /** Draws the object.
   */
   void draw();
   /** Sets a frame to draw the image.
   */
   void set3DFrame(double width, double height) throw (VException);
   
   
protected:
  IplImage* _img;
  bool _loaded;
  double _xframe, _yframe;
};

  }
  
}

#endif