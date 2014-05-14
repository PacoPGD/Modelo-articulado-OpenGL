
#include "mesh.hh"
#include <cassert>
#include <map>

namespace virtua{
  
  namespace math{

Mesh::Mesh():
  bound_min(1e12, 1e12, 1e12),
  bound_max(-1e12, -1e12, -1e12)
{
}

void Mesh::updateMinMax(const Vector& v)
{
#define UPDATE_MIN(attr) if (v.attr < bound_min.attr) bound_min.attr = v.attr
  UPDATE_MIN(x);
  UPDATE_MIN(y);
  UPDATE_MIN(z);
#undef UPDATE_MIN

#define UPDATE_MAX(attr) if (v.attr > bound_max.attr) bound_max.attr = v.attr
  UPDATE_MAX(x);
  UPDATE_MAX(y);
  UPDATE_MAX(z);
#undef UPDATE_MAX
}

void Mesh::addVertex(Vector v)
{
  vertices.push_back(v);
  updateMinMax(v);
}

void Mesh::addFace(unsigned int idx1, unsigned int idx2, unsigned int idx3)
{
  assert(idx1 < vertices.size());
  assert(idx2 < vertices.size());
  assert(idx3 < vertices.size());
  
  Face f(idx1, idx2, idx3);
  faces.push_back(f);
}

void Mesh::addFace(unsigned int idx1, unsigned int idx2, unsigned int idx3, unsigned int idx4)
{
  assert(idx1 < vertices.size());
  assert(idx2 < vertices.size());
  assert(idx3 < vertices.size());
  assert(idx4 < vertices.size());
  
  Face f1(idx1, idx2, idx3);
  Face f2(idx3, idx4, idx2);
  
  faces.push_back(f1);
  faces.push_back(f2);
}

void Mesh::setVertices(const std::vector<Vector>& vs)
{
  assert(vertices.empty());
  vertices = vs;
  for (std::vector<Vector>::const_iterator it = vs.begin(); it != vs.end(); ++it)
    updateMinMax(*it);
}

void Mesh::setVertices(unsigned int n_vertices, Vector vs[])
{
  assert(vertices.empty());
  vertices.reserve(n_vertices);
  for (unsigned int i=0; i<n_vertices; ++i)
    addVertex(vs[i]);
}

void Mesh::setVertices(unsigned int n_vertices, double vs[])
{
  assert(vertices.empty());
  vertices.reserve(n_vertices);
  double *p = vs;
  for (unsigned int i=0; i<n_vertices; ++i, p+=3) 
    addVertex(Vector(p[0], p[1], p[2]));
}

void Mesh::setVertices(unsigned int n_vertices, float vs[])
{
  assert(vertices.empty());
  vertices.reserve(n_vertices);
  float *p = vs;
  for (unsigned int i=0; i<n_vertices; ++i, p+=3)
    addVertex(Vector(p[0], p[1], p[2]));
}

void Mesh::transform(const math::Matrix4& M)
{
  // Reset bound_min and bound_max
  const Mesh tmp;
  bound_min = tmp.bound_min;
  bound_max = tmp.bound_max;

  for (std::vector<Vector>::iterator v_it = vertices.begin(); v_it != vertices.end(); ++v_it) {
    *v_it = M * (*v_it);
    updateMinMax(*v_it);
  }
}

void Mesh::getVertexArray(unsigned int size, float array[])
{
  unsigned int i=0;
  for (std::vector<Face>::const_iterator face_it = faces.begin(); face_it != faces.end() && size>0; ++face_it) {
    assert(i<size);
    for (int j=0; j<3; ++j)
      for (int c=0; c<3; ++c)
      array[i++] = vertices[face_it->idxs[j]][c];
  }
}

namespace
{
  typedef VectorLexOrder Order;
  typedef std::map<Vector, unsigned int, Order > VectorToIdx;

  //! Retrieve or insert an entry from a VectorToIdx
  /*!
    \return idx if v was not found, the index of v in m otherwise.
  */
  unsigned int getIdx(VectorToIdx* m, const Vector& v, unsigned int idx)
  {
    unsigned int ret;
    VectorToIdx::iterator find_it = m->lower_bound(v);
    Order lt;

    if (find_it == m->end() || lt(find_it->first, v) || lt(v, find_it->first))
    {
      m->insert(find_it, std::make_pair(v, idx));
      ret = idx;
    }
    else
      ret = find_it->second;

    return ret;
  }
}

void Mesh::canonizeFaces()
{
  VectorToIdx vec_to_idx;

  // For each vertex v, map v to its lowest index in this->vertices
  for (std::vector<Vector>::const_iterator it = vertices.begin();
       it != vertices.end();
       ++it)
  {
    getIdx(&vec_to_idx, *it, it - vertices.begin());
  }

  // For each face f, replace the indices by those mapped in vec_to_idx.
  for (std::vector<Face>::iterator it = faces.begin();
       it != faces.end();
       ++it)
  {
    for (int i=0; i<3; ++i)
    {
      it->idxs[i] = vec_to_idx.find(vertices.at(it->idxs[i]))->second;
    }
  }
}

  }
  
}