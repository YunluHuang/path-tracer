#pragma once

#include "Object.h"
#include "MeshObject.h"
#include "AABBox.h"

class AABBTree: public Object {
private:
  AABBox* root;

public:
  AABBTree();
  ~AABBTree();

  virtual bool intersect(const Ray& ray, Intersection& hit);
  void construct(MeshObject& mesh);
};
