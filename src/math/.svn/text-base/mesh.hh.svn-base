

#ifndef _MATH_MESH_HH
#define _MATH_MESH_HH

#include "vertex.hh"
#include "matrix.hh"
#include <vector>

namespace virtua{

  namespace math {

    //! A math::Mesh is a collection of triangles
    class Mesh {
    public:
      //! Each triangle is described using 3 indices into a vertex array.
      struct Face {
	Face(unsigned int i1, unsigned i2, unsigned int i3)
	{
	  idxs[0] = i1;
	  idxs[1] = i2;
	  idxs[2] = i3;
	}

	unsigned int idxs[3];
      };

      Mesh();
      
      //! Set the indices in each face to use the lowest index.
      /*! Useful in the case where several vertices have the same coordinates.
	Some algorithms rely on the uniqueness of vertices.

	\note
	The vertices that are no longer used are not removed from the mesh.
       */
      void canonizeFaces();

      inline const std::vector<Vector>* getVertices() const { return &vertices; }
      inline const std::vector<Face>* getFaces() const { return &faces; }

      //! Add a vertex
      void addVertex(Vector);
      
      //! Add a face described by three vertex indices into the vertex array
      void addFace(unsigned int idx1, unsigned int idx2, unsigned int idx3);

      //! Add two faces described by four indexes
      void addFace(unsigned int idx1, unsigned int idx2, unsigned int idx3, unsigned int idx4);
      
      //! Specify the vertex array
      void setVertices(const std::vector<Vector>&);
      void setVertices(unsigned int n_vertices, Vector vertices[]);

      //! Note: verts must have 3*n_vertices items
      void setVertices(unsigned int n_vertices, double verts[]);
      void setVertices(unsigned int n_vertices, float verts[]);

      //! Useful for openGL vertex arrays
      /*! The array must have 3*m_vertices items */
      void getVertexArray(unsigned int size, float array[]);
      
      //! Apply a transformation to all vertices
      void transform(const Matrix4&);

      //! Return the "near-lower-left" corner of the bounding box
      inline Vector getBoundMin() const { return bound_min; }

      //! Return the "far-upper-right" corner of the bounding box
      inline Vector getBoundMax() const { return bound_max; }

    private:
      inline void updateMinMax(const Vector&);
 
    private:
      std::vector<Vector> vertices;
      std::vector<Face> faces;
      Vector bound_min;
      Vector bound_max;
    };
    
  }
  
}


#endif
