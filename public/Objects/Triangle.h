#pragma once

#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include "Object.h"

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

class Triangle: public Object {
private:
  Vertex* vertices[3];
  Material* material;

public:
  Triangle();

  Vertex* getVertice(int idx);
  void init(Vertex* v0, Vertex* v1, Vertex* v2, Material *m);
  vec3 computeCenter();

  virtual bool intersect(const Ray& ray, Intersection& hit);
};
