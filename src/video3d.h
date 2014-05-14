#ifndef _VIRTUA_3DVIDEO_
#define _VIRTUA_3DVIDEO_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/gl.h>

//#include <ctime>
#include "timemark.h"

#include "vobject.h"

namespace virtua{
  
  namespace objects{

/**\brief This class represents an image in a three-dimensional world.
*/
class Video3D: public VObject{
public:
   /**
    */
   Video3D();
   /** Releases the memory.
    */
   ~Video3D();
   /** Loads the object from the specified file.
    */
   void load(string file) throw (VException);
   /** Saves the actual frame to the specified file.
    */
   void save(string file);
   /** Draws the current frame of the object if the time per frame has passed since the last frame was drawn.
   */
   void draw();
   /** Draws the current frame of the object.
   */
   void drawFrame();
   /** Advances to the next frame of the object.
   */
   void next();
   /** Sets a 3D frame to draw the image.
   */
   void set3DFrame(double width, double height) throw(VException);
   /** Returns the time per frame in miliseconds.
   */
   double getFrameTime();
   
protected:
  
  /** Draws the current frame of the object.
   */
  void drawGL();
   
  string _file;
  CvCapture* _vid;
  IplImage* _img;
  unsigned int _nframes;
  unsigned int _fps;
//  double _frametime;
//  time_t _frametimecps;
//  time_t _startframetime,_endframetime;
  bool _loaded;
  double _xframe, _yframe;
  TimeMark _tm;
  unsigned int _frametime;
  unsigned int _startframetime,_endframetime;
};

  }
  
}

#endif