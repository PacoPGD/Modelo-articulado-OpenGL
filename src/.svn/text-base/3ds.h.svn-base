#ifndef _VIRTUA_3DS_3DOBJECT_
#define _VIRTUA_3DS_3DOBJECT_

#include "object3d.h"

extern "C" {
#include "3dsplay.h"
#include "file.h"
}

namespace virtua{
  
  namespace objects{

    namespace formats{

      /**\brief This class represents a 3DS three-dimensional virtual object.
      */
      class DS3: public Object3D{
	public:
	  /**
	  */
	  DS3();
	  /** Releases the memory.
	  */
	  ~DS3();
	  /** Loads the object from the specified file.
	  */
	  void load(string file) throw (VException);
	   /** Saves the object to the specified file.
	  */
	  void save(string file);
	  /** Draws the object.
	  */
	  void draw();
	protected:
	  Lib3dsFile* _3dmodel;
	  bool _loaded;
	  unsigned int _nframes, _currentframe;
      };
      
}

}

}

#endif