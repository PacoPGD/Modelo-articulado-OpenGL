#ifndef __VIRTUAL_OBJECT__
#define __VIRTUAL_OBJECT__

#include <iostream>
#include <typeinfo>
#include "matrix3d.h"
#include "point3d.h"
#include "vexception.h"
#include "dimension.h"

#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;

namespace virtua{  
  
  using namespace virtua::math;
  
namespace objects{
  
/**\brief This class represents a generic virtual object.
*/
class VObject
{ 
public:
  /**
    */
  VObject();
  /** Releases the memory.
    */
  ~VObject();
  /** Sets the specified name to the object.
    */
  void setName(string name);
  /** Applies the specified transform matrix to the object.
    */
  void applyTransformMatrix(Matrix3D MT);
  /** Gets the transform matrix applied to the object.
   */
  Matrix3D getTransformMatrix();
  /** Loads the object from the specified file.
    */
  virtual void load(string file) throw (VException)=0;
  /** Saves the object to the specified file.
    */
  virtual void save(string file)=0;
  /** Draws the object.
   */
  virtual void draw()=0;
  /** Returns the object name
   */
  string getName();
  /** Returns the object dimension
   */
  Dimension getDimension();
  /** Returns the name of the class in typeid format
    */
 string getClassName();
 /** Returns the axis-aligned bounding box minimum vertex */
 Point3D<float> getBBMin();
 /** Returns the axis-aligned bounding box minimum vertex */
 Point3D<float> getBBMax();
 /** Returns the bounding-box vertices */
 Point3D<float>* getBB();
 /** Enables or disables the object bounding box to be drawn */
 void enableBoundingBox();
 void disableBoundingBox();
 void enableAxisAlignedBoundingBox();
 void disableAxisAlignedBoundingBox();
 /** Draws the virtual object bounding box */
 void drawBoundingBoxGL();
 /** Gets the axis-aligned bounding box min corner */
 Point3D<float> getAABBMin();
 /** Gets the axis-aligned bounding box max corner */
 Point3D<float> getAABBMax();

 void buildAxisAlignedBB(Point3D<float> bmin, Point3D<float> bmax, Point3D<float>* bb);
 void drawBox(Point3D<float>* box);
 
protected:
  
  void initBB();
  void updateBB();
 
  
  string _name;			// Name
  Dimension _d;			// Dimension
  Matrix3D _matrix3d;		// Matrix 3D for geometric transformations
  Point3D<float>  _bmin;		// Axis-aligned Bounding box min vertex
  Point3D<float>  _bmax;		// Axis-aligned Bounding box max vertex
  Point3D<float>  _bb[8];		// Bounding box vertices
  Point3D<float>  _drawn_bb[8];
  bool _drawBB;
  bool _drawAABB;
					//	
					//	  4_____5
					//	 /     /|
					//	/7____6 |
					//	| |   | |
					//	| 0___|_1
					//	|3____|2
};

}

}

#endif